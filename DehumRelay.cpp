#include "DehumRelay.h"
#include "Arduino.h"


DehumRelay::DehumRelay(int RelayPin)
{
    relayPin = RelayPin;
    pinMode(relayPin, OUTPUT);
}

void DehumRelay::EngageRelay()
{
    digitalWrite(relayPin, HIGH); // motor runs for one sec
}

void DehumRelay::DisengageRelay()
{
    digitalWrite(relayPin, LOW); // motor runs for one sec
}
