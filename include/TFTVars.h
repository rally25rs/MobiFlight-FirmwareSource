/*
 * 2.8 TFT SPI 240x320 V1.2
 * Driver: ILI9341 & XPT2046
 * 
 * https://www.pjrc.com/store/display_ili9341_touch.html
 * https://github.com/PaulStoffregen/XPT2046_Touchscreen
 * 
 * Pins (top to bottom):
 * 
 * VCC <-- breadboard 50
 * GND
 * CS
 * RESET
 * DC
 * SDI(MOSI) <-- breadboard 55
 * SCK
 * LED
 * SDO(MISO)
 * T_CLK
 * T_CS <-- breadboard 60
 * T_DIN
 * T_DO
 * T_IRQ
 */

#ifndef TFTVars_h
#define TFTVars_h

// Screen size
#define TFT_HEIGHT 320
#define TFT_WIDTH 240
#define TFT_ROTATION 0

// TFT pins
#define TFT_DC 9
#define TFT_CS 10
#define BTN_PREV_SCREEN 0
#define BTN_NEXT_SCREEN 1

// Touchscreen pins
#define TS_CS 8
#define TS_TIRQ 2

#define TS_X_MIN 310 // the value the touchscreen reports at right edge
#define TS_X_MAX 3800 // the value the touchscreen reports at left edge
#define TS_Y_MIN 315 // the value the touchscreen reports at screen bottom edge
#define TS_Y_MAX 3820 // the value the touchscreen reports at screen top edge

#endif // TFTVars_h