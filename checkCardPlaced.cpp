#define PhotoInterrupter A3

#include "checkCardPlaced.h"
#include "Arduino.h"
#include "readCardData.h"
#include "resetAll.h"

extern int seatStatus;

void checkCardPlaced() {

  extern int seatStatus; //access to global variable.

  pinMode(PhotoInterrupter, INPUT);
  Serial.println(analogRead(PhotoInterrupter));

  //Serial.println(digitalRead(PhotoInterrupter)); // <- for debuging
  //Resistance of LED should be about 330ohm.
  //Resistance of detector should be about 10k.

  if (digitalRead(PhotoInterrupter) == 1 && (seatStatus != 1)) //card placed
  {
    readCardData();
  }

  if ((digitalRead(PhotoInterrupter) == 0) && (seatStatus == 1)) // occupied, then reset All.
  {
    resetAll(); 
  }
}
