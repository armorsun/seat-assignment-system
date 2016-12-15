#define PhotoInterrupter 2

#include "checkCardPlaced.h"
#include "Arduino.h"
#include "readCardData.h"
#include "resetAll.h"

extern int seatStatus;

void checkCardPlaced() {

  extern int seatStatus; //access to global variable.
  
  pinMode(PhotoInterrupter,INPUT);

  Serial.println(digitalRead(PhotoInterrupter)); // <- for debuging 
//Resistance of LED should be about 330ohm.
//Resistance of detector should be about 10k.

  if(digitalRead(PhotoInterrupter)==0) //placed
  {
   readCardData();
  }

  if((digitalRead(PhotoInterrupter)==1)&&(seatStatus==1)) //not placed
  {
   resetAll(); // occupied, then reset All.
  }
}
