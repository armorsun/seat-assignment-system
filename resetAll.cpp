#include "Arduino.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

extern int seatStatus;
extern int timeRemained;
extern LiquidCrystal_I2C lcd;
extern int action;
extern unsigned long millisWhenLeave;
extern unsigned long millisElapsed;

void resetAll(){

  seatStatus = -1;  // reset to "Away"
  action = 1;        // display avaliable and green light.
  timeRemained = 0; // not counting
  lcd.init(); 
  lcd.backlight();
  millisElapsed = 0;
  millisWhenLeave = 0;
  
}

