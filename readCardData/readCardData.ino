#include <SPI.h>
#include <MFRC522.h>

// construct a object of MFRC522
MFRC522 mfrc522(10,9); //9=RST_PIN 10=SS_PIN


void setup() {
 // global variable : card UID
}

void loop() {
  // put your main code here, to run repeatedly:

}

void readCardData(){
  
  // global variable.
  extern int seatStatus;
  extern int action;
  extern byte UIDStored[4]; 
  
  if ( seatStatus == 1) { //occupied: flash red light and do nothing.
  action = 3; // action3 : occupied.
  lcddisplay();
  LEDControl(1,1);  //light
  // no uploading.
  }
  
  ////////////////////////////////////////////////
  
  else { // temporary output or available
  
    // check card is valid or not first.
    // the card validity variable = card exist && the card number is read.
    boolean rfidValid = (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial());
  
    if ( rfidValid == false ) { // the  card is invalid.
       action = 4;
       lcddisplay(); // "the card is not invalid."
       LEDControl(1,1); // flash Red LED
    }
    
    if ( rfidValid == true ) { // the  card is valid.
      byte *id = mfrc522.uid.uidByte;  //get UID of card and store in the id array;
      byte idSize = mfrc522.uid.size;  //get length of UID
      
      if ( seatStatus == 1) // available.
      
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
             
      if( seatStatus == 0 ) // temporary out.
      {
        ref = (UIDStored[1]-id[1])*(UIDStored[2]-id[2])*(UIDStored[3]-id[3])*(UIDStored[4]-id[4])

        if( ref != 0 ) { // not right card.flash red light and do nothing.
          action = 7;
          lcddisplay();
          LEDControl(0,1); // flashing blue
          
          delay(2000);
          
          action = 2;
          lcddisplay();
          LEDControl(0,2);
        }
      
        else { // right card  
          action = 5 
          lcddisplay();
          LEDControl(-1,1); // flashing green
          
          delay(2000);
         
          action = 3;
          lcddisplay();
          LEDControl(1,2); // red light 
          seatStatus = -1 ; // the state changed into occupied
          uploadData();
      }
    } 
  }
}

