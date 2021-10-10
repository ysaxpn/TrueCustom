#ifndef USBEngine_H
#define USBEngine_H

#include <Arduino.h>
#include <Keyboard.h>

#include "CommunicationData.h"
#include "Configuration.h"

class USBEngine
{
private:
    CommunicationData *_communicationData;
    Configuration *_configuration;
    uint8_t _normalKeyCodes[MaxKeyInput] = {};
    uint8_t _keyModifiers = 0;
	uint8_t _lastMillis;

private:
    bool _copyPressedKeys();
    void _sendScanCodes();

public:
    USBEngine(/* args */);
    ~USBEngine();
    void setup(Configuration *, CommunicationData *);
    void task();
};

#endif