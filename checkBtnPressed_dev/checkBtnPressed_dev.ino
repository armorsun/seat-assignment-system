#include "lcddisplay.h"
#include "checkCardPlaced.h"
#include "LEDControl.h"
#include "checkBtnPressed.h"

int seatStatus;//3 status: -1=avaliable, 0=temporarily out, 1=occupied (LEDID: -1=green, 0=blue, 1=red(occupied))
int timeRemained;

void setup() {
  seatStatus = -1;
  checkBtnPressed();

  seatStatus = 0;
  checkBtnPressed();

  seatStatus = 1;
  checkBtnPressed();
}

void loop() {

}





