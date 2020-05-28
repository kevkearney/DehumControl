#include "DehumDisplay.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the display address to 0x27 for a 16 chars and 2 line display

bool _displayOn;
String _oldStatus = "XXXX";

millisDelay lcdDelay;

const byte temp[8] PROGMEM = {
  B01110,
  B01010,
  B01010,
  B01010,
  B01010,
  B01110,
  B11111,
  B01110
};

const byte hum[8] PROGMEM = {
  B00000,
  B00010,
  B00100,
  B01110,
  B01110,
  B11111,
  B11111,
  B01110
};

const byte target[8] PROGMEM = {
  B01110,
  B10001,
  B10101,
  B10001,
  B01110,
  B00100,
  B01010,
  B10001
};


bool DehumDisplay::InitializeDisplay(const char *version)
{
  _displayOn = true;
  lcd.init(); // initialize the display
  lcd.init();

  lcd.createChar_P(0, temp);
  lcd.createChar_P(1, hum);
  lcd.createChar_P(2, target);

  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print(F("DehumControl"));
  lcd.setCursor(1, 1);
  lcd.print(F("Version: "));
  lcd.print(version);

  lcdDelay.start(10000);  // start a 10sec delay
}

void DehumDisplay::CurrentReadingDisplay(int currentHumidity, int currentTemperature, int currentSetting, String newStatus)
{
  if (_oldStatus != newStatus)
  {
    _oldStatus = newStatus;
    //lcd.clear();
  }

  lcd.backlight();
  lcd.display();
  lcd.setCursor(1, 0);
  lcd.write(byte(1));
  lcd.print(currentHumidity);
  lcd.print(F("% "));
  lcd.write(byte(0));
  lcd.print(currentTemperature);
  lcd.print(F("F "));
  lcd.write(byte(2));
  lcd.print(currentSetting);
  lcd.print(F("%"));

  lcd.setCursor(1, 1);
  lcd.print(F("Status:")); 
  lcd.print(_oldStatus); 

  lcdDelay.start(10000);  // start a 10sec delay
  _displayOn = true;
}

void DehumDisplay::PollDisplayTimer()
{
  if (_displayOn && lcdDelay.justFinished())
  {
    _DisplayOff();
    _displayOn = false;
  }
}

void DehumDisplay::_DisplayOff()
{
  lcd.noBacklight();
  lcd.noDisplay();
}
