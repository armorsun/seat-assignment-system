#include "lcddisplay.h"
#include "checkCardPlaced.h"
#include "LEDControl.h"
#include "checkBtnPressed.h"
#include "resetAll.h"
#include "uploadData.h"//empty now!
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int seatStatus;//3 status: -1=avaliable, 0=temporarily out, 1=occupied (LEDID: -1=green, 0=blue, 1=red(occupied))
int timeRemained;
String cardID;
LiquidCrystal_I2C lcd(0x27,20,4);
int action;  //4 action, anyone can add, if needed
            //action=1, display avaliable and green light.
            //action=2, display temporarily out and blue light.
            //action=3, display occupied and red.
            //action=4, display invalide and flash red light.

void setup(){
    lcd.init(); 
    lcd.backlight();
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
