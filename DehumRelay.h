/*
  DehumRelay.h - Library using a relay to control a dehumidifier
  Created by Kevin D. Kearney, May 10,2020.
  Released into the public domain.
*/

#ifndef DehumRelay_h
#define DehumRelay_h

class DehumRelay
{
    public:
        DehumRelay(int RelayPin);
        void EngageRelay();
        void DisengageRelay();
    private:
        int relayPin;
};
#endif