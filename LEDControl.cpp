//LEDControl(x,2), lcddisplay will constant
//LEDControl(x,1), delaying 0.75s

//LEDID: -1=green(avaliable), 0=blue(temporarily out), 1=red(occupied)
//action: 2=on, 1=flash, 0=off

#define RLED 5
#define GLED 4
#define BLED 3

#include "LEDControl.h"
#include "Arduino.h"

void LEDControl(int LEDID, int action) {

  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);

  if ( LEDID == -1 && action == 2 ) digitalWrite(GLED, HIGH);
  if ( LEDID == 0 && action == 2 ) digitalWrite(BLED, HIGH);
  if ( LEDID == 1 && action == 2 ) digitalWrite(RLED, HIGH);
  if ( LEDID == -1 && action == 0 ) digitalWrite(GLED, LOW);
  if ( LEDID == 0 && action == 0 ) digitalWrite(BLED, LOW);
  if ( LEDID == 1 && action == 0 ) digitalWrite(RLED, LOW);

  //-----flashing itself has the function of delaying .75 seconds.-----//
  // if you want flash  twice, call it twice.
  if ( LEDID == -1 && action == 1 ) { // Green flash
    digitalWrite(GLED, HIGH);
    delay(375);
    digitalWrite(GLED, LOW);
    delay(375);
  }
  
  if ( LEDID == 0 && action == 1 ) { // blue flash
    digitalWrite(BLED, HIGH);
    delay(375);
    digitalWrite(BLED, LOW);
    delay(375);
  }
  
  if ( LEDID == 1 && action == 1 ) { // red flash
    digitalWrite(RLED, HIGH);
    delay(375);
    digitalWrite(RLED, LOW);
    delay(375);
  }
}
