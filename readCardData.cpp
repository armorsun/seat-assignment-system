#include "readCardData.h"
#include "Arduino.h"
#include "LEDControl.h"
#include "lcddisplay.h"
#include "uploadData.h"
#include <SPI.h>
#include <MFRC522.h>

void readCardData(){
  // global variables
  extern int seatStatus;
  extern int action;
  extern byte UIDStored[4]; 
  extern MFRC522 mfrc522;
  
  //initialization in main program
  //MFRC522 mfrc522(10,9);
  //SPI.begin(); //initialize SPI
  //mfrc522.PCD_Init(); //initialize mfrc522  
            
  //action=1, display avaliable and green light.
  //action=2, display temporarily out and blue light.
  //action=3, display occupied and red.
  //action=4, display invalid and flash red light.
  //action=5, display "Right ID card" when be back.
  //action=6, display "Card is registered."
  //action=7, display "NOT Right ID card"
  
  if (seatStatus == 1){ //occupied: flash red light and do nothing.
  //action = 3; // occupied.
  //lcddisplay();
  LEDControl(1,1);  //light flashing and delay for 1.5s.
  LEDControl(1,1);  
  // no uploading.
  
  // -- actuators be back into original states -- //
  LEDControl(1,2); // light 
 
  }else{ // temporary output or available
    // check card is valid or not first.
    // the card validity variable = the card number is read.
    // IsNewCardPresent for excatly "new" card.
    boolean rfidValid = (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial());
  
      if (rfidValid == false) { // the  card is invalid.
       action = 4;
       lcddisplay(); // "invalid Card."
     
       LEDControl(0,0); // turn off green or blue light.
       LEDControl(-1,0);
       
       LEDControl(1,1); // flash Red LED and delay1.5s.
       LEDControl(1,1); 
      
        // -- actuators be back into original states -- //
       
         if(seatStatus == 0) { //lcd display the temporary out state.
         action = 2;
         lcddisplay(); 
         LEDControl(0,2); // blue light
         // with problem : what if the man insert an invalid card in 00:01?
   
         }else { //lcd display the available state.
         action = 2;
         lcddisplay();
         LEDControl(-1,2); // green light
         }
         
      }else { // the  card is valid.
      byte *id = mfrc522.uid.uidByte;  //get UID of card and store in the id array;
      byte idSize = mfrc522.uid.size;  //get length of UID
      
        if ( seatStatus == 1) {// available.
      
        // store the UID
        for (byte i = 0; i < idSize; i++){ UIDStored[i]=id[i]; }
      
         action = 6; 
         lcddisplay(); // "The card is registered."
         LEDControl(-1,1); // flashing green and delay 1.5s
         LEDControl(-1,1); 
        // after flashing, green light is off.
         action = 1;
         lcddisplay(); // "Occupied."
         LEDControl(1,2); // Red LED on.
         seatStatus = -1; // the state changed into occupied
         uploadData();
         
        }else if( seatStatus == 0 ) // temporary out.
        { 
          // if same == 1, the UIDread is same as Stored one.
          int same = !((UIDStored[1]-id[1])||(UIDStored[2]-id[2])||(UIDStored[3]-id[3])||(UIDStored[4]-id[4]));

          if(same == 0) { // not right card.flash red light and do nothing.
           
            action = 7;
            lcddisplay();
            LEDControl(0,1); // flashing blue
          
            delay(2000);
          
            action = 2;
            lcddisplay();
            LEDControl(0,2);
            
          }else { // right card  
            
            LEDControl(0,0); // turn off blue light
            action = 5;
            lcddisplay();
            LEDControl(-1,1); // flashing green
          
            delay(2000);
         
            action = 3;
            lcddisplay();
            LEDControl(1,2); // red light 
            seatStatus = -1 ; // the state changed into occupied
            uploadData();
          } // right card
        } //seatStatus == 0 
      } // rfidValid == 1
    } //seatStatus == 0 or 1.
} // whole fuction


