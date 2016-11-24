void setup() {
 // global variable : card UID
}

void loop() {
  // put your main code here, to run repeatedly:

}

void readCardData(){
  
  extern int seatStatus;
  extern int action;
  // the card validity variable = card exist + the card number is read.
  boolean rfidValid = (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial());

  if ( seatStatus == 1) { // not avaliable. flash red light and do nothing.
  LEDControl(1,1);  //light
  action = 3; // action3 : occupied.
  lcddisplay();
  }
  
  else { // temporary output or available
  ///////check card is valid or not first.///////
    if ( rfidValid == false ) { // the  card is valid.
      // LCDDisplay("the card is not invalid.")
       LEDControl(1,1); // flash Red LED
       action = 4;
       lcddisplay();
    }
    if ( rfidValid == true ) {     
      byte *idRead = mfrc522.uid.uidByte;  //get the UID of card and store in the id array;
      byte idSize = mfrc522.uid.size;  //get the length of UID
      
      if ( seatStatus == 1) // available.
       //idRead[] = idStored[]; //must ensure the array length
       action = 1 ;
       lcddisplay();
       /////// maybe report to the management system.
      else // temporary out.
      {
      
      /* pseudocode
      if (rfidRead != rfidStored ) { LEDControl(1,1); }
      // not right card.flash red light and do nothing.
      */
        LEDControl(-1,1);
        uploadData();
        //countDown(reset);
        
        seatStatus = -1 ; 
      }
    ///////check card is valid or not first./////// 
    } 
  }
}

