/*
  DehumDHT.h - Library for using DHT22 hum control.
  Created by Kevin D. Kearney, May 09, 2020.
  Released into the public domain.
*/

#ifndef DehumDHT_h
#define DehumDHT_h

#include <DHT.h>

const int DHTPIN = 4;
const int DHTTYPE = 22;


class DehumDHT
{
  public:
    void InitializeSensors();
    bool GetSensorValues(int &temperature, int &humidity);
};
#endif