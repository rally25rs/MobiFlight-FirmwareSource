#ifndef MFTFTDisplay_h
#define MFTFTDisplay_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif

#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>

#include "TFTVars.h"
#include "MFVirtualPanel.h"

extern "C"
{
  // callback functions
  typedef void (*tftScreenEvent) (int, const char *);
};

/////////////////////////////////////////////////////////////////////
/// \class MFTFTDisplay MFTFTDisplay.h <MFTFTDisplay.h>
class MFTFTDisplay
{
public:
    MFTFTDisplay(int16_t panelCount = 0, MFVirtualPanel* panels = {});
    static void attachHandler(tftEvent newHandler);
    static void attachScreenHandler(tftScreenEvent newHandler);
    void attach();
    void detach();
    void loop();
    void renderPanel(int16_t panelId);
    void updateOutputs(uint8_t pin, int32_t state);

private:
    static tftEvent _handler;
    static tftScreenEvent _screenHandler;
    Adafruit_ILI9341 *_tft;
    XPT2046_Touchscreen *_ts;
    bool _initialized;
    bool _allowScreenChange;
    int16_t _lastTouchX;
    int16_t _lastTouchY;
    int16_t _activePanel;
    int16_t _panelCount;
    MFVirtualPanel *_panels;
    void _handleTouchButtonPress(int16_t x, int16_t y, bool pressed);
};
#endif
