#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "LEDControl.h"
#include "lcddisplay.h"

extern int seatStatus;
extern int timeRemained;
extern LiquidCrystal_I2C lcd;
extern int action;
extern unsigned long millisWhenLeave;
extern unsigned long millisElapsed;

void resetAll() {

  seatStatus = -1;  // reset to "Available"
  action = 1;        // display avaliable
  LEDControl(1, 0); // lights off.
  LEDControl(0, 0); // lights off.
  LEDControl(-1, 2); //green light.
  timeRemained = 0; // not counting
  lcddisplay();
  millisElapsed = 0;
  millisWhenLeave = 0;

}

