#ifndef MFBoardTeensy41_h
#define MFBoardTeensy41_h

#ifndef MF_SEGMENT_SUPPORT
#define MF_SEGMENT_SUPPORT 1
#endif
#ifndef MF_LCD_SUPPORT
#define MF_LCD_SUPPORT 1
#endif
#ifndef MF_STEPPER_SUPPORT
#define MF_STEPPER_SUPPORT 1
#endif
#ifndef MF_SERVO_SUPPORT
#define MF_SERVO_SUPPORT 0
#endif
#ifndef MF_ANALOG_SUPPORT
#define MF_ANALOG_SUPPORT 1
#endif
#ifndef MF_OUTPUT_SHIFTER_SUPPORT
#define MF_OUTPUT_SHIFTER_SUPPORT 1
#endif
#ifndef MF_INPUT_SHIFTER_SUPPORT
#define MF_INPUT_SHIFTER_SUPPORT 1
#endif
#ifndef MF_TFT_SUPPORT
#define MF_TFT_SUPPORT 1
#endif

#define MODULE_MAX_PINS 41
#define MAX_OUTPUTS 40
#define MAX_BUTTONS 40
#define MAX_LEDSEGMENTS 4
#define MAX_ENCODERS 20
#define MAX_STEPPERS 10
#define MAX_MFSERVOS 0
#define MAX_MFLCD_I2C 2
#define MAX_ANALOG_INPUTS 18
#define MAX_OUTPUT_SHIFTERS 4
#define MAX_INPUT_SHIFTERS 4
#define MAX_TFT_DISPLAYS 1

#define STEPS 64
#define STEPPER_SPEED 400 // 300 already worked, 467, too?
#define STEPPER_ACCEL 800

#define MOBIFLIGHT_TYPE "MobiFlight Teensy"
#define MOBIFLIGHT_SERIAL "1234567890"
#define MOBIFLIGHT_NAME "MobiFlight Teensy"
#define EEPROM_SIZE 4284
#define MEMLEN_CONFIG 1496

#define RANDOM_SEED_INPUT A0

#endif