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
  // callback functions always follow the signature: void cmd(void);
  typedef void (*tftEvent) (byte, uint8_t, const char *);
};

enum
{
  tftOnPress,
  tftOnRelease,
};

/////////////////////////////////////////////////////////////////////
/// \class MFTFTDisplay MFTFTDisplay.h <MFTFTDisplay.h>
class MFTFTDisplay
{
public:
    MFTFTDisplay(int16_t panelCount = 0, MFVirtualPanel* panels = {});
    static void attachHandler(tftEvent newHandler);
    void attach();
    void detach();
    void loop();
    void renderPanel(int16_t panelId);

private:
    static tftEvent _handler;
    Adafruit_ILI9341 *_tft;
    XPT2046_Touchscreen *_ts;
    bool _initialized;
    int16_t _lastTouchX;
    int16_t _lastTouchY;
    int16_t _activePanel;
    int16_t _panelCount;
    MFVirtualPanel *_panels;
    void _handleTouchButtonPress(int16_t x, int16_t y, bool pressed);
};
#endif
