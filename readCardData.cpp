#include "readCardData.h"
#include "Arduino.h"
#include "LEDControl.h"
#include "lcddisplay.h"
#include "uploadData.h"
#include <SPI.h>
#include <MFRC522.h>

void readCardData() {
  extern int seatStatus;
  extern int timeRemained;
  extern int action;
  extern byte UIDStored[4];
  extern MFRC522 mfrc522;

  //==== trouble processing 1: "the other card in." ====// // no such condition
  /*
    if (seatStatus == 1) { //occupied: flash red light and do nothing.
      action = 3; // occupied.
      lcddisplay();
      LEDControl(1, 1); //light flashing and delay for 1.5s.
      LEDControl(1, 1);
      //actuators be back into original states
      LEDControl(1, 2); // light

    } else { // temporary output or available
  */

  //==== trouble processing 2: "invalid Card." ====//

  // check card is valid or not first.
  // IsNewCardPresent for excatly "new" card.
  boolean rfidValid = (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial());

  if (rfidValid == false) { // the  card is invalid.

    LEDControl(0, 0); // turn off green and blue light.
    LEDControl(-1, 0);// turn off green and blue light.

    action = 4;
    lcddisplay(); // "invalid Card."

    LEDControl(1, 1); // flash Red LED and delay1.5s.
    LEDControl(1, 1);

    //actuators be back into original states
    if (seatStatus == 0) { //temporary out
      LEDControl(0, 2); // blue light
      action = 2;
      lcddisplay();

    } else { //available
      LEDControl(-1, 2); // green light
      action = 1;
      lcddisplay();
    }

  } else { // the  card is valid.
    byte *id = mfrc522.uid.uidByte;  //get UID of card and store in the id array;
    byte idSize = mfrc522.uid.size;  //get length of UID

    if ( seatStatus == -1) {//from "Available" to "occupied"

      // store the UID
      for (byte i = 0; i < idSize; i++) {
        UIDStored[i] = id[i];
        Serial.println(uint8_t(UIDStored[i]));
      }
  
      Serial.println();
      action = 6;
      lcddisplay(); // "The card is registered."
      LEDControl(-1, 1); // flashing green and delay 1.5s
      LEDControl(-1, 1); // after flashing, green light is off.

      //actuators be back into original states
      seatStatus = 1; // the state changed into occupied
      LEDControl(1, 2); // Red LED on.
      action = 3;
      lcddisplay(); // "Occupied."

      uploadData();

    } else if ( seatStatus == 0 ) { //"away"

      //==== trouble processing 3 of "Away": "wrong Card." ====//
      // if same == 1, the UIDread is same as Stored one.
      boolean same = !((UIDStored[1] - id[1])&&(UIDStored[2] - id[2])&&(UIDStored[3] - id[3])&&(UIDStored[4] - id[4]));

      if (same == false) { // not right card,flash red light and do nothing.
        LEDControl(0, 0);
        action = 7;
        lcddisplay();
        LEDControl(1, 1); // flashing red for1.5s.
        LEDControl(1, 1);

        //actuators be back into original states

        action = 2;
        lcddisplay();
        LEDControl(0, 2);

        //====from "Away" to "occupied" ====//

      } else { // right card

        LEDControl(0, 0); // turn off blue light
        action = 5;
        lcddisplay();
        LEDControl(-1, 1); // flashing green for1.5s.
        LEDControl(-1, 1);

        //actuators be back into original states

        seatStatus = 1 ; // the state changed into occuppied
        LEDControl(1, 2); // red light
        action = 3;
        lcddisplay();
        timeRemained = 0;
        uploadData();

      } // right card check
    } //seatStatus == 0
  } // rfidValid == 1
} // whole fuction


