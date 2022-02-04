// MFVirtualButton.h
//
/// \mainpage MF Virtual Button module for MobiFlight Framework
/// \par Revision History
/// \version 1.0 Initial release
/// \author  Sebastian Moebius (mobiflight@moebiuz.de) DO NOT CONTACT THE AUTHOR DIRECTLY: USE THE LISTS
// Copyright (C) 2013-2014 Sebastian Moebius

#ifndef MFVirtualOutput_h
#define MFVirtualOutput_h

#include <stdlib.h>
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif

/////////////////////////////////////////////////////////////////////
/// \class MFVirtualOutput MFVirtualOutput.h <MFVirtualOutput.h>
class MFVirtualOutput
{
public:
    MFVirtualOutput(uint8_t pin = 1);
    void set(uint8_t value);
    uint8_t get();
    
private:
    uint8_t       _pin;
    uint8_t       _value;
};
#endif 