#ifndef MFVirtualPanel_h
#define MFVirtualPanel_h

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#include <Adafruit_ILI9341.h>

class TouchButton
{
  private:
    const char* _name;
    int _joystickButtonNum;
    int _posX;
    int _posY;
    int _width;
    int _height;
    const char* _text;
 
  public:
    TouchButton(const char* name, int joystickButtonNum, int posX, int posY, int width, int height, const char* text);
    int getJoystickButtonNum();
    const char* getName();
    bool isTouchInBoundry(int touchX, int touchY);
    void render(Adafruit_ILI9341* tft, bool pressed);
};

class MFVirtualPanel
{
  private:
    const char* _name;
    int _touchButtonsCount;
    TouchButton* _touchButtons;

   public:
     MFVirtualPanel(const char* name, int touchButtonsCount, TouchButton* touchButtons);
     void render(Adafruit_ILI9341* tft);
     const char* getName();
     TouchButton* getTouchButtons();
     int getTouchButtonsCount();
};

#endif // MFVirtualPanel_h