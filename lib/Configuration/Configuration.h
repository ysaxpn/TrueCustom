#ifndef Configuration_H
#define Configuration_H

#include "Arduino.h"

#define MaxColumn 32
#define MaxRow 8
#define KeyMapEndMarker 255
#define MaxKeyInput 6 // TODO: Change name to MaxUSBKeyOutput

class Configuration
{
public:
	Configuration();
	~Configuration();

	uint8_t getScanCode(uint8_t row, uint8_t column, uint8_t layerIndex);
	bool getSetupKeyStatus();
	bool isSetupKey(uint8_t row, uint8_t column);
	uint8_t getColumnNum();
	uint8_t getRowNum();
	uint8_t getColumnPin(int);
	uint8_t getRowPin(int);
	uint8_t getDebounceTime();
	uint8_t getMaxKeyLayer();
	uint8_t getKeyScanRateInMiliSeconds();

private:
    void _loadKeyScanData();
};

#endif
