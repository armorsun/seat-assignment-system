#define BTNPIN 6

#include "Arduino.h"
#include "checkBtnPressed.h"
#include "LEDControl.h"
#include "uploadData.h"
#include "lcddisplay.h"

extern int seatStatus;
extern int timeRemained;
extern unsigned long millisWhenLeave;
extern int action;

void checkBtnPressed() {

  pinMode(BTNPIN, INPUT);
  int buttonState = digitalRead(BTNPIN);

  if (buttonState == HIGH) {

    if (seatStatus == -1 || seatStatus == 0) {
      //if seat avaliable or temporarily out, do nothing,
      return;
    } else if (seatStatus == 1) {
      //if occupied...
      seatStatus = 0;       //1. set seatStatus temporarily out,
      LEDControl(0, 2);     //2. turn on blue LED,
      LEDControl(1, 0);     //3. turn off red LED!
      action = 2;          
      lcddisplay(); 
      timeRemained = 10;    //4. start counting down 30 mins ; in the test version, time is 10 secs.
      uploadData();         //5. report to RPi
      millisWhenLeave = millis(); //6. record the millisecond when start countdown
      delay(500);
    }
  }
}

