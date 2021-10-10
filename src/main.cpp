#include <KeyboardInputEngine.h>
#include <DisplayEngine.h>
#include <USBEngine.h>
#include <LedService.h>

Configuration configuration;
// DisplayEngine display;
KeyboardInputEngine keyboardInput;
CommunicationData communicationData;
USBEngine usbEngine;
LedService ledService;

void setup()
{
  // Adafruit_ST7735 *tft = display.setup(&configuration, &communicationData);
  keyboardInput.setup(&configuration, &communicationData);
  usbEngine.setup(&configuration, &communicationData);
  ledService.setup(&communicationData);
}

void loop()
{
  keyboardInput.task();
  // display.task();
  usbEngine.task();
  ledService.task();
}
