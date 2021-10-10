#include <string.h>

#include "LedService.h"
#include "KeyboardScanCode.h"

extern "C"
{
#include "stm32f103_fastNP_Arduino/ws2812_led.h"
}

struct pixel
{
  uint8_t g;
  uint8_t r;
  uint8_t b;
};

#define FRAMEBUFFER_SIZE 17

struct pixel channel_framebuffers[WS2812_NUM_CHANNELS][FRAMEBUFFER_SIZE];
struct led_channel_info led_channels[WS2812_NUM_CHANNELS];

LedService::LedService(/* args */)
{
  mode = 1;
  ledStep = 0;
}

LedService::~LedService()
{
}

int LedService::setup(CommunicationData *communicationData)
{
  _communicationData = communicationData;

  pinMode(PB0, OUTPUT);

  for (int i = 0; i < WS2812_NUM_CHANNELS; i++)
  {
    led_channels[i].framebuffer = (uint8_t *)channel_framebuffers[i];
    led_channels[i].length = FRAMEBUFFER_SIZE * sizeof(struct pixel);
  }

  for (int i = 0; i < FRAMEBUFFER_SIZE; i++)
  {
    channel_framebuffers[0][i].r = 255;
    channel_framebuffers[0][i].g = 0;
    channel_framebuffers[0][i].b = 0;
  }

  ws2812_init();

  __disable_irq();
  ws2812_refresh(led_channels, GPIOB);
  __enable_irq();

  return 0;
}

int LedService::task()
{
  _updateMode();

  switch (mode)
  {
  case 0:
    _modeAllOff();
    break;

  case 1:
    _setColor(255, 255, 255);
    break;

  case 2:
    _setColor(255, 0, 0);
    break;

  case 3:
    _setColor(0, 255, 0);
    break;

  case 4:
    _setColor(0, 0, 255);
    break;

  case 5:
    _modeBlink();
    break;

  default:
    mode = 0;
    return 0;
  }

  _setLockLed();

  __disable_irq();
  ws2812_refresh(led_channels, GPIOB);
  __enable_irq();

  return 0;
}

void LedService::_updateMode()
{
  if (_communicationData->customKey == 0)
  {
    return;
  }

  mode = _communicationData->customKey - CUSTOM_LED_MIN;
  ledStep = 0;
  delay(300);
  _communicationData->customKey = 0;
}

void LedService::_modeAllOff()
{
  this->_setColor(0, 0, 0);
}

void LedService::_setColor(uint8_t r, uint8_t g, uint8_t b)
{
  for (int i = 1; i < FRAMEBUFFER_SIZE; i++)
  {
    channel_framebuffers[0][i].r = r;
    channel_framebuffers[0][i].g = g;
    channel_framebuffers[0][i].b = b;
  }
}

void LedService::_modeBlink()
{
  const uint16_t maxLedStep = 255;
  static bool direction = true;

  if (direction)
  {
    if (ledStep == maxLedStep)
    {
      direction = false;
    }
    else
    {
      ledStep++;
    }
  }
  else
  {
    if (ledStep == 0)
    {
      direction = true;
    }
    else
    {
      ledStep--;
    }
  }

  uint8_t color = ledStep;
  _setColor(color, color, color);
}

void LedService::_setLockLed()
{
  channel_framebuffers[0][0].g = ((_communicationData->lockLedStatus & 0x01) > 0) ? 255 : 0;
  channel_framebuffers[0][0].r = ((_communicationData->lockLedStatus & 0x02) > 0) ? 255 : 0;
  channel_framebuffers[0][0].b = ((_communicationData->lockLedStatus & 0x04) > 0) ? 255 : 0;
}