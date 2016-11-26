// for self-writing .h files, use " ".
#include "lcddisplay.h"
#include "checkCardPlaced.h"
#include "LEDControl.h"
#include "checkBtnPressed.h"
#include "resetAll.h"
#include "uploadData.h"//empty now!

// for downloaded .h files, use < >.
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

// construct an object of MFRC522 
MFRC522 mfrc522(10,9); //9=RST_PIN 10=SS_PIN

// construct an object of LCD
LiquidCrystal_I2C lcd(0x27,20,4);

int seatStatus -1; //3 status: -1=avaliable, 0=temporarily out, 1=occupied (LEDID: -1=green, 0=blue, 1=red(occupied))
               // default available 

int timeRemained;
byte UIDStored[4]; //the UID stored.

int action = 1;  //7 action, anyone can add, if needed
            // default available
            
            //action=1, display avaliable and green light.
            //action=2, display temporarily out and blue light.
            //action=3, display occupied and red.
            //action=4, display invalid and flash red light.
            //action=5, display "Right ID card" when be back.
            //action=6, display "Card is registered."
            //action=7, display "NOT Right ID card"

void setup(){
    // debuging
    Serial.begin(9600); 
    Serial.println("RFID reader is ready!"); 
    
    // lcd initialization
    lcd.init(); 
    lcd.backlight();
    
    // RFID initialization
    SPI.begin();
    mfrc522.PCD_Init(); 
}

void loop(){
    checkCardPlaced();//using photointerupter to detect if a card is placed, if yes call readCardData(), 
                          //if not, do nothing.

    checkBtnPressed();//check seatStatus first, 
                            //if seat avaliable or temporarily out, do nothing, 
                            //if occupied, start countdown(e.g.  set timeRemained=1800), turn on blue LED, set seatStatus temporarily out, uploadData().
                           
}

//yuda: Comment out following APIs to prevent multiple definition
//void LCDDisplay(){}   //check action

//void readCardData(){} //check seatStatus, 
                          //if not avaliable, flash red light and do nothing, set action=4 
                          //if avaliable, check card is valid or not, is the same or not, 
                                    //if not, flash Red LED, set action=4
                                    //if yes, turn on green LED, call uploadData() , set timeRemaind=0, set seatStatus=occupied, set action=3

//void LEDControl(int LEDID){}//turn on,turn off, flash...., LEDID: -1=green, 0=blue, 1=red, check action

//void uploadData(){}//upload card, timeRemained, status, using json format. 

//void resetAll(){}//seatStatus=-1, action=1, timeRemained=0, LCDDisplay, LEDControl, uploadData
