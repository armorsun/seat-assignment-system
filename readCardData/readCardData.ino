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
       uploadData(); // report the system
       LEDControl(1,2); // 
       seatStatus = -1 ; // the state changed into occupied
      else // temporary out.
      {
      /* pseudocode
      if (rfidRead != rfidStored ) { // not right card.flash red light and do nothing.
        LEDControl(1,1); 
        action = 4;
        lcddisplay();
      }
      
      else { // right card  
        // action = 5? (lcddisplay("Right ID card");) delay(2000);
        seatStatus = -1 ; // the state changed into occupied
        action = 3;
        lcddisplay();
        LEDControl(1,2); // red light 
        uploadData();
      }
      */
      /*
      1. action
      2. lcddisplay
      3. LEDcontrol
      4. uploadData.
     */ 
    } 
  }
}

