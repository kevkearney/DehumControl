#include "DehumLogic.h"

const int engageBuffer = 3;
const int disengageBuffer = 3;

int _oldHumiditySetting = -999;

int _oldTemp;
int _oldHum;

bool _isDisplayChange = false;
bool _isRunning = false;
bool _isSleeping = false;

DehumRelay dehumidifyRelay(5);
millisDelay sleepDelay;

void DehumLogic::InitializeLogic(){
    _isSleeping = true;
    sleepDelay.start(60000);
}

bool DehumLogic::isDisplayChange()
{
    bool currentState = _isDisplayChange;
    _isDisplayChange = false;

    return currentState;
}

bool DehumLogic::isRunning()
{
    return _isRunning;
}

bool DehumLogic::isSleeping()
{
    return _isSleeping;
}

int DehumLogic::GetSleepTime()
{
    return sleepDelay.remaining();
}

void DehumLogic::_EngageDehumidify()
{
    if (!_isRunning && !_isSleeping)
    {
        dehumidifyRelay.EngageRelay();
        _isRunning = true;
    }
}

void DehumLogic::_DisengageDehumidity()
{
    if (_isRunning)
    {
        dehumidifyRelay.DisengageRelay();
        sleepDelay.start(60000);
        _isSleeping = true;
        _isRunning = false;
    }
}

void DehumLogic::EvaluateData(int currentHumidity, int currentTemperature, int humiditySetting)
{
    if(sleepDelay.justFinished())
    {
        _isSleeping = false;
    }

    if (_oldTemp != currentTemperature)
    {
        _oldTemp = currentTemperature;
        _isDisplayChange = true;
    }

    if (_oldHum != currentHumidity || _oldHumiditySetting != humiditySetting)
    {
        _oldHum = currentHumidity;
        _oldHumiditySetting = humiditySetting;
        _isDisplayChange = true;

        if (_oldHumiditySetting + engageBuffer < _oldHum)
        {
            _EngageDehumidify();
        }
        else if(_oldHumiditySetting - disengageBuffer > _oldHum)
        {
            _DisengageDehumidity();
        }
        else 
        {
            //Do nothing.
        }
    }
}
