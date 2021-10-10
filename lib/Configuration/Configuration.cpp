#include "Configuration.h"
#include "KeyboardScanCode.h"

// page index
#define ConfigurationDataIndex  0
#define ReservedDataIndex       1
#define FirstKeyLayoutIndex     2

// configuration index
#define ModelNumberIndex        12
#define DeviceNameIndex         16
#define ColumnPinMapsIndex      40 
#define RowPinMapsIndex         72
#define SetupKeyPinIndex        80 
#define SetupKeyColumnIndex     81 
#define SetupKeyRowIndex        82
#define DebounceTimeIndex       83
#define MaxKeyLayerIndex        84
#define KeyScanRateIndex        85

const uint8_t data[12][255] = {
    {
        0X00, 0XFF, 0XAA, 0X55, 0XFF, 0X11, 0XFF, 0X00, // [0:8 bytes] signature for flash memory look up.
        0X00, 0X01, 0X00, 0X00,                         // [8:4 bytes] F/W version. x.x.x.x
        0X00, 0X00, 0X00, 0X00,                         // [12:4 bytes] model number
        'T', 'r', 'u', 'e', 'C', 'u', 's', 't', 'o', 'm', 0X00, 0x00,
        0X00, 0x00, 0X00, 0X00, 0X00, 0x00, 0X00, 0x00, 0X00, 0x00, 0X00, 0x00, // [16:24 bytes] device name
        PB4, PB5, PB6, PB7, 0XFF, 0XFF, 0XFF, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
        0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, // [40:32 bytes] column pin maps
        PA0, PA1, PA2, PA3, PA8, PB2, 0XFF, 0XFF,       // [72:8 bytes] row pin maps
        PB1,                                            // [80:1 bytes] setup key pin map
        0X00,                                           // [81:1 bytes] setup key column
        0X05,                                           // [82:1 bytes] setup key row
        0X09,                                           // [83:1 bytes] debounce in ms
        0x05,                                           // [84:1 bytes] max key layers
        0x0A,                                           // [85:1 bytes] Key Scan Rate in miliseconds
    },
    {}, // Reserved
    {
        KEY_A,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,      // KP1
        KEY_F,    // KP2
        KEY_G,    // KP3
        KEY_H,
        KEY_KP1, //8  -> KP4
        KEY_KP2, // 9 -> KP5
        KEY_KP3, // 10-> KP6
        KEY_L, // 11
        KEY_M, // 12 -> KP7
        KEY_N, // 13 -> KP8
        KEY_O, // 14 -> KP9
        KEY_P, // 15
        KEY_NUMLOCK, // 16 -> NUMLOCK
        KEY_R, // 17
        KEY_S, // 18
        KEY_T, // 19
        CUSTOM_LED_OFF, //20
        CUSTOM_LED_OFF,// 21
        CUSTOM_LED_5,// 22
        CUSTOM_LED_2, //23
    },
     {
        KEY_KP0,
        KEY_KP0,
        KEY_KPDOT,
        KEY_LEFTSHIFT,
        KEY_B,      // KP1
        KEY_KP2,    // KP2
        KEY_KP3,    // KP3
        KEY_LEFTSHIFT,
        CUSTOM_LAYER_2, //8  -> KP4
        CUSTOM_LAYER_1, // 9 -> KP5
        CUSTOM_LAYER_6, // 10-> KP6
        KEY_KPPLUS, // 11
        CUSTOM_TEMP_LAYER_2, // 12 -> KP7
        CUSTOM_TEMP_LAYER_1, // 13 -> KP8
        CUSTOM_TEMP_LAYER_6, // 14 -> KP9
        KEY_KPPLUS, // 15
        KEY_NUMLOCK, // 16
        KEY_KPSLASH, // 17
        KEY_KPASTERISK, // 18
        KEY_KPMINUS, // 19
        KEY_ESC, //20
        KEY_Y,// 21
        CUSTOM_LAYER_1,// 22
        CUSTOM_LAYER_2, //23
    },
     {
        KEY_KP0,
        KEY_KP0,
        KEY_KPDOT,
        KEY_LEFTSHIFT,
        KEY_C,      // KP1
        KEY_KP2,    // KP2
        KEY_KP3,    // KP3
        KEY_LEFTSHIFT,
        CUSTOM_LAYER_2, //8  -> KP4
        CUSTOM_LAYER_1, // 9 -> KP5
        CUSTOM_LAYER_6, // 10-> KP6
        KEY_KPPLUS, // 11
        CUSTOM_TEMP_LAYER_2, // 12 -> KP7
        CUSTOM_TEMP_LAYER_1, // 13 -> KP8
        CUSTOM_TEMP_LAYER_6, // 14 -> KP9
        KEY_KPPLUS, // 15
        KEY_NUMLOCK, // 16
        KEY_KPSLASH, // 17
        KEY_KPASTERISK, // 18
        KEY_KPMINUS, // 19
        KEY_ESC, //20
        KEY_Y,// 21
        KEY_X,// 22
        CUSTOM_LED_OFF, //22
    },
     {
        KEY_KP0,
        KEY_KP0,
        KEY_KPDOT,
        KEY_LEFTSHIFT,
        KEY_D,      // KP1
        KEY_KP2,    // KP2
        KEY_KP3,    // KP3
        KEY_LEFTSHIFT,
        CUSTOM_LAYER_2, //8  -> KP4
        CUSTOM_LAYER_1, // 9 -> KP5
        CUSTOM_LAYER_6, // 10-> KP6
        KEY_KPPLUS, // 11
        CUSTOM_TEMP_LAYER_2, // 12 -> KP7
        CUSTOM_TEMP_LAYER_1, // 13 -> KP8
        CUSTOM_TEMP_LAYER_6, // 14 -> KP9
        KEY_KPPLUS, // 15
        KEY_NUMLOCK, // 16
        KEY_KPSLASH, // 17
        KEY_KPASTERISK, // 18
        KEY_KPMINUS, // 19
        KEY_ESC, //20
        KEY_Y,// 21
        KEY_X,// 22
        CUSTOM_LED_OFF, //22
    },
     {
        KEY_KP0,
        KEY_KP0,
        KEY_KPDOT,
        KEY_LEFTSHIFT,
        KEY_E,      // KP1
        KEY_KP2,    // KP2
        KEY_KP3,    // KP3
        KEY_LEFTSHIFT,
        CUSTOM_LAYER_2, //8  -> KP4
        CUSTOM_LAYER_1, // 9 -> KP5
        CUSTOM_LAYER_6, // 10-> KP6
        KEY_KPPLUS, // 11
        CUSTOM_TEMP_LAYER_2, // 12 -> KP7
        CUSTOM_TEMP_LAYER_1, // 13 -> KP8
        CUSTOM_TEMP_LAYER_6, // 14 -> KP9
        KEY_KPPLUS, // 15
        KEY_NUMLOCK, // 16
        KEY_KPSLASH, // 17
        KEY_KPASTERISK, // 18
        KEY_KPMINUS, // 19
        KEY_ESC, //20
        KEY_Y,// 21
        KEY_X,// 22
        CUSTOM_LED_OFF, //22
    },
     {
        KEY_KP0,
        KEY_KP0,
        KEY_KPDOT,
        KEY_LEFTSHIFT,
        KEY_F,      // KP1
        KEY_KP2,    // KP2
        KEY_KP3,    // KP3
        KEY_LEFTSHIFT,
        CUSTOM_LAYER_2, //8  -> KP4
        CUSTOM_LAYER_1, // 9 -> KP5
        CUSTOM_LAYER_6, // 10-> KP6
        KEY_KPPLUS, // 11
        CUSTOM_TEMP_LAYER_2, // 12 -> KP7
        CUSTOM_TEMP_LAYER_1, // 13 -> KP8
        CUSTOM_TEMP_LAYER_6, // 14 -> KP9
        KEY_KPPLUS, // 15
        KEY_NUMLOCK, // 16
        KEY_KPSLASH, // 17
        KEY_KPASTERISK, // 18
        KEY_KPMINUS, // 19
        KEY_ESC, //20
        KEY_Y,// 21
        KEY_X,// 22
        CUSTOM_LED_OFF, //22
    },
};

const uint8_t *configurationData = data[ConfigurationDataIndex];
const uint8_t setupKeyPin = configurationData[SetupKeyPinIndex];
const uint8_t setupKeyColumn = configurationData[SetupKeyColumnIndex];
const uint8_t setupKeyRow = configurationData[SetupKeyRowIndex];
const uint8_t debounceTime = configurationData[DebounceTimeIndex];
const uint8_t maxkeyLayer = configurationData[MaxKeyLayerIndex];
const uint8_t keyScanRate = configurationData[KeyScanRateIndex];

uint8_t columnNum;
uint8_t rowNum;
uint8_t columnPin[MaxColumn];
uint8_t rowPin[MaxRow];

Configuration::Configuration(/* args */)
{
    _loadKeyScanData();
}

Configuration::~Configuration()
{
}

uint8_t Configuration::getColumnNum()
{
    return columnNum;
}

uint8_t Configuration::getRowNum()
{
    return rowNum;
}

uint8_t Configuration::getColumnPin(int index)
{
    return columnPin[index];
}

uint8_t Configuration::getRowPin(int index)
{
    return rowPin[index];
}

uint8_t Configuration::getDebounceTime()
{
    return debounceTime;
}

uint8_t Configuration::getMaxKeyLayer()
{
    return maxkeyLayer;
}

uint8_t Configuration::getKeyScanRateInMiliSeconds()
{
    return keyScanRate;
}

void Configuration::_loadKeyScanData()
{
    pinMode(setupKeyPin, INPUT);

    const uint8_t *columnPinMap = &(configurationData[ColumnPinMapsIndex]);

    for (columnNum = 0; columnNum < MaxColumn && columnPinMap[columnNum] != KeyMapEndMarker; columnNum++)
    {
        columnPin[columnNum] = columnPinMap[columnNum];
        pinMode(columnPin[columnNum], OUTPUT);
        digitalWrite(columnPin[columnNum], 0);
    }

    const uint8_t *rowPinMap = &(configurationData[RowPinMapsIndex]);

    for (rowNum = 0; rowNum < MaxRow && rowPinMap[rowNum] != KeyMapEndMarker; rowNum++)
    {
        rowPin[rowNum] = rowPinMap[rowNum];
        pinMode(rowPin[rowNum], INPUT);
    }
}

uint8_t Configuration::getScanCode(uint8_t row, uint8_t column, uint8_t layerIndex)
{
    // TODO: check row and column boundary
    const uint8_t layoutIndex = FirstKeyLayoutIndex + layerIndex; 
    const uint8_t *keyMapData = data[layoutIndex];
    return keyMapData[row * columnNum + column];
}

bool Configuration::getSetupKeyStatus() {

    if (digitalRead(setupKeyPin)) {
        return true;
    }
    return false;
}

bool Configuration::isSetupKey(uint8_t row, uint8_t column)
{
    if (row == setupKeyRow && column == setupKeyColumn)
    {
        return true;
    }
    return false;
}
