/*
  DehumDisplay.h - Library for displaying humidity data on lcd
  Created by Kevin D. Kearney, May 9, 2020.
  Released into the public domain.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <millisDelay.h>

#ifndef DehumDisplay_h
#define DehumDisplay_h

class DehumDisplay
{
  public:
    void CurrentReadingDisplay(int currentHumidity, int currentTemperature, int currentSetting, String newStatus);
    bool InitializeDisplay(const char *version);
    void PollDisplayTimer();
  private:
    void _DisplayOff();
};
#endif