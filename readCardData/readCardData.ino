void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

/*
void readCardData(){
  if ( seatStatus == 1) { LEDControl(1,1); }
  // not avaliable. flash red light and do nothing.
  
  if ( seatStatus == 0) {
    //check card is valid or not first.
    
    if ( rfidValid == 0 ) { 
      // LCDDisplay("the card is not valid.")
       LEDControl(1,1); // flash Red LED
    }
    if ( rfidValid == 1 ) {
      
      if (rfidRead != rfidStored ) { LEDControl(1,1); }
      // not right card.flash red light and do nothing.
      
      else // right card
      {
        LEDControl(-1,1);
        uploadData();
        //countDown(reset);
        
        seatStatus = -1 ; 
        LCDDisplay();
      }
      
    }
 
  }
}
*/
