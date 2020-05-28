#include "DehumDHT.h"
#include <millisDelay.h>
#include "DehumRelay.h"

millisDelay sampleDelay;
bool firstRun = true;

DehumRelay samplefanRelay(6);

DHT dht(DHTPIN, DHTTYPE);

void DehumDHT::InitializeSensors()
{
  Serial.println(F("DHT22 initialize!"));
  dht.begin();
  sampleDelay.start(300000);
  firstRun = true;
}

bool DehumDHT::GetSensorValues(int &temperature, int &humidity)
{
  if(sampleDelay.justFinished() || firstRun){
    float fltTemperature = dht.readTemperature();
    float fltHumidity = dht.readHumidity();

    samplefanRelay.DisengageRelay();
    firstRun = false;

    int tempCelcius = round(fltTemperature);

    humidity = round(fltHumidity);
    temperature = ((tempCelcius * 9 / 5) + 32);
    return true;
  } else {
    if(sampleDelay.isRunning()){
      if(sampleDelay.remaining() < 120000){
        //turn on samplefan
        Serial.println(F("Fan Enaged"));
        samplefanRelay.EngageRelay();
      }
    } else {
      sampleDelay.repeat();
    }
  }
}