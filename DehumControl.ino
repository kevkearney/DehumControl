#include "DehumDHT.h"
#include "DehumDisplay.h"
#include "DehumEncoder.h"
#include "DehumLogic.h"

const char version[6] = "0.4.4";

const int defaultHumiditySetting PROGMEM = 40;

String status = "Error";

DehumDisplay dehumDisplay;
DehumEncoder encoder;
DehumDHT dehumDHT;
DehumLogic dehumLogic;

void setup()
{
    Serial.begin(9600);
    Serial.println(F("DehumControl Debug:"));

    encoder.InitializeHumiditySetting(defaultHumiditySetting);
    dehumDHT.InitializeSensors();
    dehumDisplay.InitializeDisplay(version);
    dehumLogic.InitializeLogic();
    delay(2000);
    dehumDisplay.CurrentReadingDisplay(99, 99, 99, F("Init >  "));
    delay(2000);
}

void loop()
{
    int newTemp;
    int newHum;

    int encoderHumidity = encoder.GetHumiditySetting();
    bool tempSuccess = dehumDHT.GetSensorValues(newTemp, newHum);

    dehumLogic.EvaluateData(newHum, newTemp, encoderHumidity);

    if(dehumLogic.isDisplayChange()){
        if(dehumLogic.isRunning()){
            status = F("Running ");
        } else {
            if(!dehumLogic.isSleeping()){
                status = F("Stopped ");
            } else {
                int sleepTime = dehumLogic.GetSleepTime() / 60000;
                status = F("Sleep  ");
            }
        }
        dehumDisplay.CurrentReadingDisplay(newHum, newTemp, encoderHumidity, status);
    }

    dehumDisplay.PollDisplayTimer();
}