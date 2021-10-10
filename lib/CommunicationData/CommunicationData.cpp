#include <Arduino.h>

#include "CommunicationData.h"
#include "KeyboardScanCode.h"

void CommunicationData::resetPressedKeyBuffers()
{
    keyModifiers = 0;

    for (uint8_t index = 0; index < MaxKeyInput; index++)
    {
        keyCodes[index] = KEY_NONE;
    }
}
