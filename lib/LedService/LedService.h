#ifndef LedService_H
#define LedService_H

#include <Arduino.h>

#include "CommunicationData.h"

class LedService
{
private:
    uint16_t mode;
    uint16_t ledStep; 
    CommunicationData *_communicationData;
    Configuration *_configuration;

    void _updateMode();
    void _modeAllOff();
    void _modeBlink();
    void _setColor(uint8_t r, uint8_t g, uint8_t b);
    void _setLockLed();

public:

    LedService(/* args */);
    ~LedService();

    int setup(CommunicationData *communicationData);
    int task();
};

#endif
