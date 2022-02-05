// #include <Adafruit_ILI9341.h>
// #include <XPT2046_Touchscreen.h>

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#include <Adafruit_BusIO_Register.h>
#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>

#include "MFTFTDisplay.h"

tftEvent MFTFTDisplay::_handler = NULL;

MFTFTDisplay::MFTFTDisplay(int16_t panelCount, MFVirtualPanel* panels)
{
  _panelCount = panelCount;
  _panels = panels;
  _initialized = false;
  _lastTouchX = -1;
  _lastTouchY = -1;
}

void MFTFTDisplay::attach()
{
  _tft = new Adafruit_ILI9341(TFT_CS, TFT_DC);
  _ts = new XPT2046_Touchscreen(TS_CS, TS_TIRQ);

  _tft->begin();
  _tft->setRotation(TFT_ROTATION);
  _tft->fillScreen(ILI9341_BLACK);

  if (!_ts->begin()) {
    _tft->setCursor(5, 5);
    _tft->setTextColor(ILI9341_WHITE);  _tft->setTextSize(1);
    _tft->println("Couldn't start touchscreen controller");
  }
  _ts->setRotation(TFT_ROTATION);

  _initialized = true;
}

void MFTFTDisplay::detach()
{
  if (!_initialized)
    return;
  delete _ts;
  delete _tft;
  _initialized = false;
}

void MFTFTDisplay::renderPanel(int16_t panelId)
{
  _activePanel = panelId;
  _panels[_activePanel].render(_tft);
}

void MFTFTDisplay::loop()
{
  if(_ts->touched()) {
    if(_lastTouchX == -1) {
      TS_Point t = _ts->getPoint();
      _lastTouchX = map(t.x, TS_X_MIN, TS_X_MAX, TFT_WIDTH, 0);
      _lastTouchY = map(t.y, TS_Y_MIN, TS_Y_MAX, TFT_HEIGHT, 0);
      _handleTouchButtonPress(_lastTouchX, _lastTouchY, true);
    }
  } else if(_lastTouchX > -1) {
    _handleTouchButtonPress(_lastTouchX, _lastTouchY, false);
    _lastTouchX = -1;
    _lastTouchY = -1;
  }
}

void MFTFTDisplay::_handleTouchButtonPress(int16_t x, int16_t y, bool pressed)
{
  int renderablesCount = _panels[_activePanel].getRenderablesCount();
  TFTRenderable** renderables = _panels[_activePanel].getRenderables();

  for(int i = 0; i < renderablesCount; i++) {
    TFTRenderable* renderable = renderables[i];
    if(_handler && renderable->isTouchInBoundry(x, y)) {
      renderable->handleTouch(_tft, _handler, pressed);
    }
  }
}

void MFTFTDisplay::attachHandler(tftEvent newHandler)
{
  _handler = newHandler;
}

void MFTFTDisplay::updateOutputs(uint8_t pin, int32_t state)
{
  for (int panelIdx = 0; panelIdx < _panelCount; panelIdx++) {
    MFVirtualPanel panel = _panels[panelIdx];
    TFTRenderable** renderables = panel.getRenderables();
    for (int renderableIdx = 0; renderableIdx < panel.getRenderablesCount(); renderableIdx++)
    {
      TFTRenderable* renderable = renderables[renderableIdx];
      if(renderable->getVirtualOutputPin() == pin)
      {
        renderable->virtualOutputValue = state;
        if(panelIdx == _activePanel)
        {
          renderable->render(_tft, false);
        }
      }
    }
  }
}