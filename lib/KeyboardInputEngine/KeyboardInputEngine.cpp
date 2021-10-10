#include <Arduino.h>

#include "KeyboardInputEngine.h"

int KeyboardInputEngine::setup(Configuration *configuration, CommunicationData *communicationData)
{
    _configuration = configuration;
    _communicationData = communicationData;

    _lastMillis = millis();

    // TODO: Move display code

    return 0;
}
int KeyboardInputEngine::task()
{
    _readKeyGrids();
    _readNewPressedKeys();
    _updateKeyScanBuffer();

    return 0;
}

void KeyboardInputEngine::_readKeyGrids()
{
    uint32_t now = millis();
    uint32_t duration = now - _lastMillis;

    if (duration < _configuration->getKeyScanRateInMiliSeconds())
    {
        return;
    }

    _lastMillis = now;

    int keyTimeCountIndex = 0;

    for (int column = 0; column < _configuration->getColumnNum(); column++)
    {
        digitalWrite(_configuration->getColumnPin(column), 1);

        for (int row = 0; row < _configuration->getRowNum(); row++)
        {
            bool keyStatus = false;

            if (_configuration->isSetupKey(row, column))
            {
                keyStatus = _configuration->getSetupKeyStatus();
            }
            else
            {
                keyStatus = digitalRead(_configuration->getRowPin(row));
            }

            if (keyStatus)
            {
                if (_scanBuffer[row][column] + duration > 255)
                {
                    _scanBuffer[row][column] = 255;
                }
                else
                {
                    _scanBuffer[row][column] += duration;
                }
            }
            else
            {
                _scanBuffer[row][column] = 0;
            }
        }
        digitalWrite(_configuration->getColumnPin(column), 0);
    }
}

void KeyboardInputEngine::_resetPressedKeyBuffer()
{
    for (uint8_t index = 0; index < MaxPressedKeys; index++)
    {
        _pressedKeys[index].row = MaxRow;
        _pressedKeys[index].column = MaxColumn;
    }
}

bool KeyboardInputEngine::_isCustomKey(uint8_t keyCode)
{
    if (keyCode >= CUSTOM_MIN_NUMBER && keyCode <= CUSTOM_MAX_NUMBER)
    {
        return true;
    }

    return false;
}

bool KeyboardInputEngine::_isPermenantLayerKey(uint8_t keyCode)
{
    if (keyCode >= CUSTOM_MIN_LAYER && keyCode <= CUSTOM_MAX_LAYER)
    {
        return true;
    }

    return false;
}

bool KeyboardInputEngine::_isTempLayerKey(uint8_t keyCode)
{
    if (keyCode >= CUSTOM_TEMP_MIN_LAYER && keyCode <= CUSTOM_TEMP_MAX_LAYER)
    {
        return true;
    }
    return false;
}

bool KeyboardInputEngine::_isModifierKeyCode(uint8_t keyCode)
{
    if (keyCode >= KEY_MODIFIER_MIN && keyCode <= KEY_MODIFIER_MAX)
    {
        return true;
    }
    return false;
}

void KeyboardInputEngine::_readNewPressedKeys()
{
    uint8_t keyIndex = 0;
    uint8_t ignoredKeys = 0;

    _resetPressedKeyBuffer();

    for (uint8_t row = 0; row < _configuration->getRowNum(); row++)
    {
        for (uint8_t column = 0; column < _configuration->getColumnNum(); column++)
        {
            if (_scanBuffer[row][column] >= _configuration->getDebounceTime())
            {
                if (keyIndex < MaxPressedKeys)
                {
                    _pressedKeys[keyIndex].row = row;
                    _pressedKeys[keyIndex].column = column;
                    keyIndex++;
                }
                else
                {
                    ignoredKeys++;
                }
            }
        }
    }
}

bool KeyboardInputEngine::_isValidKey(KeyLocation location)
{
    if (location.row < MaxRow && location.column < MaxColumn)
    {
        return true;
    }
    return false;
}

uint8_t KeyboardInputEngine::_getSelectedLayoutIndex()
{
    for (uint8_t pressedKeyIndex = 0; pressedKeyIndex < MaxPressedKeys; pressedKeyIndex++)
    {
        if (_isValidKey(_pressedKeys[pressedKeyIndex]))
        {
            uint8_t keyCode = _configuration->getScanCode(_pressedKeys[pressedKeyIndex].row, _pressedKeys[pressedKeyIndex].column, _currentKeyLayerIndex);

            if (_isTempLayerKey(keyCode))
            {
                return keyCode - CUSTOM_TEMP_MIN_LAYER;
            }
        }
        else
        {
            return _currentKeyLayerIndex;
        }
    }

    return _currentKeyLayerIndex;
}

void KeyboardInputEngine::_storeModifierKeyCode(uint8_t keyCode)
{
    switch (keyCode)
    {
    case KEY_LEFTCTRL:
        _communicationData->keyModifiers |= 0X01;
        break;

    case KEY_LEFTSHIFT:
        _communicationData->keyModifiers |= 0X02;
        break;

    case KEY_LEFTALT:
        _communicationData->keyModifiers |= 0X04;
        break;

    case KEY_LEFTMETA:
        _communicationData->keyModifiers |= 0X08;
        break;

    case KEY_RIGHTCTRL:
        _communicationData->keyModifiers |= 0X10;
        break;

    case KEY_RIGHTSHIFT:
        _communicationData->keyModifiers |= 0X20;
        break;

    case KEY_RIGHTALT:
        _communicationData->keyModifiers |= 0X40;
        break;

    case KEY_RIGHTMETA:
        _communicationData->keyModifiers |= 0X80;
        break;
    }
}

void KeyboardInputEngine::_storeKeyCode(uint8_t keyCode)
{

    if (_isModifierKeyCode(keyCode))
    {
        _storeModifierKeyCode(keyCode);
        return;
    }

    if (_keyCodeIndex < MaxKeyInput)
    {
        _communicationData->keyCodes[_keyCodeIndex] = keyCode;
        _keyCodeIndex++;
    }
    else
    {
        _keyCodeIgnored++;
    }
}

void KeyboardInputEngine::_storeCustomKeyCode(uint8_t keyCode)
{

    if (_isPermenantLayerKey(keyCode))
    {
        _currentKeyLayerIndex = keyCode - CUSTOM_LAYER_1;
        return;
    }

    // TODO:
    _communicationData->customKey = keyCode;
}

void KeyboardInputEngine::_updateKeyScanBuffer()
{
    _keyCodeIndex = 0;
    _keyCodeIgnored = 0;

    _communicationData->resetPressedKeyBuffers();
    const uint8_t selectedKeyLayer = _getSelectedLayoutIndex();

    for (uint8_t pressedKeyIndex = 0; pressedKeyIndex < MaxPressedKeys; pressedKeyIndex++)
    {

        const KeyLocation keyLocation = _pressedKeys[pressedKeyIndex];

        if (!_isValidKey(keyLocation))
        {
            return;
        }

        uint8_t keyCode = _configuration->getScanCode(keyLocation.row, keyLocation.column, selectedKeyLayer);

        if (_isCustomKey(keyCode))
        {
            _storeCustomKeyCode(keyCode);
        }
        else
        {
            _storeKeyCode(keyCode);
        }
    }
}