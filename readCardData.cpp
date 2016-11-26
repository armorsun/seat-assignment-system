#include "readCardData.h"
#include "Arduino.h"
#include <SPI.h>
#include <MFRC522.h>

void readCardData(){
  // global variables
  extern int seatStatus;
  extern int action;
  extern byte UIDStored[4]; 
  extern MFRC522 mfrc522(10,9);
  
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
  LEDControl(1,1);  //light
  // no uploading.
 
  }else{ // temporary output or available
    // check card is valid or not first.
    // the card validity variable = card exist && the card number is read.
    boolean rfidValid = (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial());
  
      if ( rfidValid == false ) { // the  card is invalid.
       action = 4;
       lcddisplay(); // "invalid Card."
       LEDControl(1,1); // flash Red LED
       
       delay(2000);
       
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
      }
    
      if ( rfidValid == true ) { // the  card is valid.
      byte *id = mfrc522.uid.uidByte;  //get UID of card and store in the id array;
      byte idSize = mfrc522.uid.size;  //get length of UID
      
        if ( seatStatus == 1) {// available.
      
        // store the UID
        for (byte i = 0; i < idSize; i++){ UIDStored[i]=id[i]; }
      
         action = 6; 
         lcddisplay(); // "The card is registered."
         LEDControl(-1,1); // flashing green
       
         delay(2000); //
       
         action = 1;
         lcddisplay(); // "Occupied."
         LEDControl(1,2); // Red LED on.
         seatStatus = -1; // the state changed into occupied
         uploadData(); // report the system
        }else if( seatStatus == 0 ) // temporary out.
        { // if same == 0, the UIDread is same as Stored one.
          int same = (UIDStored[1]-id[1])*(UIDStored[2]-id[2])*(UIDStored[3]-id[3])*(UIDStored[4]-id[4]);

          if( same != 0 ) { // not right card.flash red light and do nothing.
            action = 7;
            lcddisplay();
            LEDControl(0,1); // flashing blue
          
            delay(2000);
          
            action = 2;
            lcddisplay();
            LEDControl(0,2);
          }else { // right card  
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


