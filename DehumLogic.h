/*
  DehumLogic.h - Library for temperature and timing logic.
  Created by Kevin D. Kearney, May 10, 2020.
  Released into the public domain.
*/

#include "DehumRelay.h"
#include "Arduino.h"
#include <millisDelay.h>

#ifndef DehumLogic_h
#define DehumLogic_h

class DehumLogic
{
public:
    void InitializeLogic();
    void EvaluateData(int currentHumidity, int currentTemperature, int humiditySetting);
    bool isDisplayChange();
    bool isRunning();
    bool isSleeping();
    int GetSleepTime();
private:
    void _EngageDehumidify();
    void _DisengageDehumidity();
};
#endif