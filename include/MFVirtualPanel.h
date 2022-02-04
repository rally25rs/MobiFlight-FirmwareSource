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
    int _posX;
    int _posY;
    int _width;
    int _height;
    const char* _text;
    uint8_t _virtualOutPin;
 
  public:
    TouchButton(const char* name, int posX, int posY, int width, int height, const char* text, uint8_t virtualOutPin = 0);
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