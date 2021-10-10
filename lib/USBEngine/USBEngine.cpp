#include "USBEngine.h"
#include "KeyboardScanCode.h"

#include "usbd_hid_composite_if.h"

#define MaxSendIgnoredInMilliSeconds 500 


USBEngine::USBEngine()
{
    HID_Composite_Init(HID_KEYBOARD);
}

USBEngine::~USBEngine()
{
    HID_Composite_DeInit(HID_KEYBOARD);
}

void USBEngine::setup(Configuration *configuration, CommunicationData *communicationData)
{
    _configuration = configuration;
    _communicationData = communicationData;
    _lastMillis = millis();
}

void USBEngine::task()
{
    uint32_t now = millis();
    uint32_t duration = now - _lastMillis;

    if (!_copyPressedKeys() || duration > MaxSendIgnoredInMilliSeconds)
    {
        _sendScanCodes();
        _lastMillis = now;
    }

#ifdef __TRUECUSTOM_STATUS_LED_SUPPORT
    _communicationData->lockLedStatus = HID_Composite_keyboard_GetLedStatus();
#endif
}

void USBEngine::_sendScanCodes()
{
    uint8_t buf[8] = {
        _keyModifiers,
        0,
        _normalKeyCodes[0],
        _normalKeyCodes[1],
        _normalKeyCodes[2],
        _normalKeyCodes[3],
        _normalKeyCodes[4],
        _normalKeyCodes[5]};

    HID_Composite_keyboard_sendReport(buf, 8);
    delay(20);
}

bool USBEngine::_copyPressedKeys()
{
    bool isAllSame = true;

    for (uint8_t index = 0; index < MaxKeyInput; index++)
    {
        if (_normalKeyCodes[index] != _communicationData->keyCodes[index])
        {
            _normalKeyCodes[index] = _communicationData->keyCodes[index];
            isAllSame = false;
        }
    }

    if (_keyModifiers != _communicationData->keyModifiers)
    {
        _keyModifiers = _communicationData->keyModifiers;
        isAllSame = false;
    }

    return isAllSame;
}
