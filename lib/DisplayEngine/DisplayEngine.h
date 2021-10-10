#ifndef DisplayEngine_H 
#define DisplayEngine_H 

#include <Wire.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <WString.h>

#include "CommunicationData.h"

class DisplayEngine
{
public:
    Adafruit_ST7735 *setup(Configuration *, CommunicationData *);
    int task();
    void print(const String &s);

    private:
    CommunicationData *_communicationData;
    Configuration *_configuration;
};


#endif