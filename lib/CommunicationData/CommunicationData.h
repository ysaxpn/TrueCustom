#ifndef CommunicationData_H
#define CommunicationData_H

#include <Arduino.h>
#include <Configuration.h>

class CommunicationData
{
public:
    char* error = NULL;
    uint8_t customKey = 0;
    uint8_t keyCodes[MaxKeyInput] = {};
    uint8_t keyModifiers = 0;
    uint8_t lockLedStatus = 0;

private:

public:
    void resetPressedKeyBuffers();

};

#endif