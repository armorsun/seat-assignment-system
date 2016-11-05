#define PhotoInterrupter 2

#include "checkCardPlaced.h"
#include "Arduino.h"

void checkCardPlaced() {

pinMode(PhotoInterrupter,INPUT);

//Serial.println(digitalRead(PhotoInterrupter)); // <- for debuging 
//Resistance of LED should be about 330Ohm.
//Resistance of detector should be about 10k.

  if(digitalRead(PhotoInterrupter)==0) //placed
  {
    readCardData();
  }

  if(digitalRead(PhotoInterrupter)==1) //not placed
  {
    if( seatStatus ==  1 ) {resetAll();} // occupied
  }
}
