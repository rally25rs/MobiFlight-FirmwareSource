#include "MFVirtualPanel.h"

TFTRenderable::TFTRenderable(TFTRenderableType type, int posX, int posY, int width, int height, uint8_t virtualOutPin)
{
  _type = type;
  _posX = posX;
  _posY = posY;
  _width = width;
  _height = height;
  _virtualOutPin = virtualOutPin;
  virtualOutputValue = 0;
}

bool TFTRenderable::isTouchInBoundry(int touchX, int touchY)
{
  return touchX >= _posX
    && touchX <= _posX + _width
    && touchY >= _posY
    && touchY <= _posY + _height;
}

void TFTRenderable::render(Adafruit_ILI9341* tft, bool pressed) {
  tft->fillRect(20, 20, 20, 20, ILI9341_ORANGE);
}

TFTRenderableType TFTRenderable::type()
{
  return _type;
}

uint8_t TFTRenderable::getVirtualOutputPin()
{
  return _virtualOutPin;
}

void TFTRenderable::handleTouch(Adafruit_ILI9341* tft, tftEvent handler, bool pressed) {}


TouchButton::TouchButton(const char* name, int posX, int posY, int width, int height, const char* text, uint8_t virtualOutPin): TFTRenderable(TOUCH_BUTTON, posX, posY, width, height, virtualOutPin)
{
  _name = name;
  _text = text;
}

const char* TouchButton::getName()
{
  return _name;
}

void TouchButton::render(Adafruit_ILI9341* tft, bool pressed)
{
  const bool outputActive = _virtualOutPin > 0 && virtualOutputValue > 0;

  tft->fillRect(_posX, _posY, _width, _height, pressed ? 0x05FF : ILI9341_BLACK);
  tft->drawRect(_posX, _posY, _width, _height, ILI9341_WHITE);
  tft->setCursor(_posX + 5, _posY + 15);
  tft->setTextColor(outputActive ? TFT_ACTIVE_COLOR : ILI9341_WHITE);
  tft->setTextSize(3);
  tft->println(_text);

  if(outputActive)
  {
    tft->drawRect(_posX + 6, _posY + _height - 7, _width - 12, 3, TFT_ACTIVE_COLOR);
  }
}

void TouchButton::handleTouch(Adafruit_ILI9341* tft, tftEvent handler, bool pressed) {
  render(tft, pressed);

  if(pressed) {
    (*handler)(tftOnPress, _name);
  } else {
    (*handler)(tftOnRelease, _name);
  }
}

TouchKnob::TouchKnob(int posX, int posY, int width, int height, const char* text, uint8_t virtualOutPin): TFTRenderable(TOUCH_KNOB, posX, posY, width, height, virtualOutPin)
{
  _text = text;
}

void TouchKnob::render(Adafruit_ILI9341* tft, bool pressed)
{
  const bool outputActive = _virtualOutPin > 0 && virtualOutputValue > 0;
  const int halfWidth = _width / 2;

  int16_t x, y;
  uint16_t w, h;

  tft->fillRect(_posX, _posY, _width, _height, ILI9341_BLACK);
  tft->drawCircle(_posX + halfWidth, _posY + halfWidth, halfWidth - 6, TFT_KNOB_COLOR);
  tft->setCursor(_posX + 5, _posY + _height - 20);
  tft->setTextColor(ILI9341_LIGHTGREY);
  tft->setTextSize(2);
  tft->println(_text);

  if (outputActive) {
    tft->setTextColor(ILI9341_BLACK);
    tft->getTextBounds(virtualOutputValue, _posX + 5, _posY + halfWidth, &x, &y, &w, &h);
    tft->setTextColor(TFT_ACTIVE_COLOR);
    tft->setCursor(_posX + halfWidth - w / 2, _posY + halfWidth - h / 2);
    tft->print(virtualOutputValue);
  }
}

MFVirtualPanel::MFVirtualPanel(const char* name, int renderablesCount, TFTRenderable* renderables[]):
  _name(name),
  _renderablesCount(renderablesCount),
  _renderables(renderables)
{}

void MFVirtualPanel::render(Adafruit_ILI9341* tft)
{
  tft->fillRect(0, 0, tft->width(), tft->height(), ILI9341_BLACK);
  tft->fillRect(0, 0, tft->width(), 20, ILI9341_DARKGREY);
  tft->setCursor(2, 2);
  tft->setTextColor(ILI9341_NAVY);
  tft->setTextSize(2);
  tft->println(_name);

  for(int i = 0; i < _renderablesCount; i++)
  {
    TFTRenderable* renderable = _renderables[i];
    renderable->render(tft, false);
  }
}

const char* MFVirtualPanel::getName()
{
  return _name;
}

int MFVirtualPanel::getRenderablesCount()
{
  return _renderablesCount;
}

TFTRenderable** MFVirtualPanel::getRenderables()
{
  return _renderables;
}