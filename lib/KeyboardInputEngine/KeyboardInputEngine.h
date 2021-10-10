#ifndef KeyboardInputEngine_H
#define KeyboardInputEngine_H

#include "Adafruit_ST7735.h"
#include "Configuration.h"
#include "CommunicationData.h"
#include "KeyboardScanCode.h"

#define MaxPressedKeys 12

struct KeyLocation
{
	uint8_t row;
	uint8_t column;
};


class KeyboardInputEngine
{
public:
	int setup(Configuration *, CommunicationData *);
	int task();

// Member Variables
private:
	Adafruit_ST7735 *_tft;
	Configuration *_configuration;
	CommunicationData *_communicationData;

	uint8_t _lastMillis;
    uint8_t _setupKeyColumn;
	uint8_t _setupKeyRow;
	KeyLocation _pressedKeys[MaxPressedKeys];
	uint8_t _scanBuffer[MaxRow][MaxColumn] = {
		0,
	};
    uint8_t _currentKeyLayerIndex = 0;
	uint8_t _keyCodeIndex = 0;
	uint8_t _keyCodeIgnored = 0;

// Member Functions 
private:
	void _readKeyGrids();
    void _resetPressedKeyBuffer();
    void _readNewPressedKeys();
	void _updateKeyScanBuffer();
	uint8_t _getSelectedLayoutIndex();
	bool _isCustomKey(uint8_t keyCode);
	bool _isPermenantLayerKey(uint8_t keyCode);
	bool _isTempLayerKey(uint8_t keyCode);
	void _storeKeyCode(uint8_t keyCode);
	void _storeCustomKeyCode(uint8_t keyCode);
	void _storeModifierKeyCode(uint8_t keyCode);
	bool _isModifierKeyCode(uint8_t keyCode);
	bool _isValidKey(KeyLocation location);
};

#endif