#include "DisplayEngine.h"

#if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
  #define TFT_CS         14
  #define TFT_RST        15
  #define TFT_DC         32

#elif defined(ESP8266)
  #define TFT_CS         4
  #define TFT_RST        16                                            
  #define TFT_DC         5

#else
  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS         PA15 
  #define TFT_RST        PB3 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         PA14 
#endif

// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// SCLK = pin 13. This is the fastest mode of operation and is required if
// using the breakout board's microSD card.

// For 1.44" and 1.8" TFT with ST7735 use:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


Adafruit_ST7735 *DisplayEngine::setup(Configuration *configuration, CommunicationData *communicationData)
{
    _communicationData = communicationData;
    _configuration = configuration;

    Serial.begin(9600);

    tft.initR(INITR_BLACKTAB); // initialize a ST7735S chip, black tab
    tft.fillScreen(ST7735_BLACK);
    tft.setRotation(3);
    tft.print("Test Start");

    return &tft;
}

int DisplayEngine::task()
{
    if (_communicationData->error != NULL)
    {
        tft.println(_communicationData->error);
    }

    return 1;
}


void DisplayEngine::print(const String &str)
{
    tft.print(str);
}
