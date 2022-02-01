#include "MFVirtualPanel.h"

TouchButton::TouchButton(const char* name, int joystickButtonNum, int posX, int posY, int width, int height, const char* text):
  _name(name),
  _joystickButtonNum(joystickButtonNum),
  _posX(posX),
  _posY(posY),
  _width(width),
  _height(height),
  _text(text)
{}

int TouchButton::getJoystickButtonNum()
{
  return _joystickButtonNum;
}

const char* TouchButton::getName()
{
  return _name;
}

bool TouchButton::isTouchInBoundry(int touchX, int touchY)
{
  return touchX >= _posX
    && touchX <= _posX + _width
    && touchY >= _posY
    && touchY <= _posY + _height;
}

void TouchButton::render(Adafruit_ILI9341* tft, bool pressed)
{
  tft->fillRect(_posX, _posY, _width, _height, pressed ? ILI9341_BLUE : ILI9341_BLACK);
  tft->drawRect(_posX, _posY, _width, _height, ILI9341_WHITE);
  tft->setCursor(_posX + 5, _posY + 5);
  tft->setTextColor(ILI9341_WHITE);  tft->setTextSize(2);
  tft->println(_text);
}

MFVirtualPanel::MFVirtualPanel(const char* name, int touchButtonsCount, TouchButton* touchButtons):
  _name(name),
  _touchButtonsCount(touchButtonsCount),
  _touchButtons(touchButtons)
{}

void MFVirtualPanel::render(Adafruit_ILI9341* tft)
{
  for(int i = 0; i < _touchButtonsCount; i++)
  {
    _touchButtons[i].render(tft, false);
  }
}

const char* MFVirtualPanel::getName()
{
  return _name;
}

int MFVirtualPanel::getTouchButtonsCount()
{
  return _touchButtonsCount;
}

TouchButton* MFVirtualPanel::getTouchButtons()
{
  return _touchButtons;
}