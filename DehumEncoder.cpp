#include "DehumEncoder.h"

Encoder myEnc(ENCODER_PIN1, ENCODER_PIN2);

long oldPosition = -999;
const int highLimit = 320;
const int lowLimit = 100;

void DehumEncoder::InitializeHumiditySetting(int defaultSetting){
    oldPosition = defaultSetting * 4;
    myEnc.write(oldPosition);
}

int DehumEncoder::GetHumiditySetting()
{
    long newPosition = myEnc.read();
    
    if (newPosition != oldPosition)
    {
        if (newPosition > highLimit)
        {
            myEnc.write(highLimit);
        }
        else if (newPosition < lowLimit)
        {
            myEnc.write(lowLimit);
        }
        else
        {
            oldPosition = newPosition;
        }
    }
    return oldPosition / 4;
}