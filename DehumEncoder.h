 
/*
  DehumEncoder.h - Library using a rotary encoder with DehumControl
  Created by Kevin D. Kearney, May 9,2020.
  Released into the public domain.
*/

#ifndef DehumEncoder_h
#define DehumEncoder_h

#define ENCODER_PIN1 3       
#define ENCODER_PIN2 2   

#include <Encoder.h>

class DehumEncoder
{
    public:
        void InitializeHumiditySetting(int defaultHumidity);
        int GetHumiditySetting();
};
#endif