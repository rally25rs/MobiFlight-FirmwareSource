// MFVirtualOutput.cpp
//
// Copyright (C) 2013-2014

#include "MFVirtualOutput.h"

MFVirtualOutput::MFVirtualOutput(uint8_t pin)
{   
  _pin = pin;
  _value = false;
  pinMode(_pin, OUTPUT);    // set pin to input
  set(_value);
}

void MFVirtualOutput::set(uint8_t value)
{
  _value = value;
}

uint8_t MFVirtualOutput::get()
{
  return _value;
}
