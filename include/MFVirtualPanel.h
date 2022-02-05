#ifndef MFVirtualPanel_h
#define MFVirtualPanel_h

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#include <Adafruit_ILI9341.h>

extern "C"
{
  // callback functions always follow the signature: void cmd(void);
  typedef void (*tftEvent) (byte, const char *);
};

// More color codes: https://gist.github.com/Kongduino/36d152c81bbb1214a2128a2712ecdd18
#define TFT_ACTIVE_COLOR 0x3666
#define TFT_KNOB_COLOR 0xAD55

enum
{
  tftOnPress,
  tftOnRelease,
};

enum TFTRenderableType {
  BASE,
  TOUCH_BUTTON,
  TOUCH_KNOB
};

class TFTRenderable
{
  protected:
    TFTRenderable(TFTRenderableType type, int posX, int posY, int width, int height, uint8_t virtualOutPin = 0);
    TFTRenderableType _type;
    int _posX;
    int _posY;
    int _width;
    int _height;
    uint8_t _virtualOutPin;

  public:
    virtual void render(Adafruit_ILI9341* tft, bool pressed);
    virtual void handleTouch(Adafruit_ILI9341* tft, tftEvent handler, bool pressed);
    TFTRenderableType type();
    bool isTouchInBoundry(int touchX, int touchY);
    uint8_t getVirtualOutputPin();
    int32_t virtualOutputValue;
};

class TouchButton : public TFTRenderable
{
  private:
    const char* _name;
    const char* _text;
 
  public:
    TouchButton(const char* name, int posX, int posY, int width, int height, const char* text, uint8_t virtualOutPin = 0);
    const char* getName();
    void render(Adafruit_ILI9341* tft, bool pressed);
    void handleTouch(Adafruit_ILI9341* tft, tftEvent handler, bool pressed);
};

class TouchKnob : public TFTRenderable
{
  private:
   const char* _text;

  public:
    TouchKnob(int posX, int posY, int width, int height, const char* text, uint8_t virtualOutPin = 0);
    void render(Adafruit_ILI9341* tft, bool pressed);
};

class MFVirtualPanel
{
  private:
    const char* _name;
    int _renderablesCount;
    TFTRenderable** _renderables;

   public:
     MFVirtualPanel(const char* name, int touchButtonsCount, TFTRenderable* renderables[]);
     void render(Adafruit_ILI9341* tft);
     const char* getName();
     TFTRenderable** getRenderables();
     int getRenderablesCount();
};

#endif // MFVirtualPanel_h