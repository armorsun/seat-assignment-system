#include "lcddisplay.h"
#include "checkCardPlaced.h"
#include "LEDControl.h"

int seatStatus//3 status: -1=avaliable, 0=temporarily out, 1=occupied (LEDID: -1=green, 0=blue, 1=red(occupied))
int Time
String cardID
LiquidCrystal_I2C lcd(0x27,20,4);

void setup(){
    lcd.init(); 
    lcd.backlight();
}

void loop(){

}

void LCDDisplay(){}

void checkCardPlaced()//using photointerupter to detect if a card is placed, call readCardData(), if not, check seatStatus, if occupied, call resetAll(), if temporarily out, do nothing.

void readCardData(){}//check seatStatus, if not avaliable, flash red light and do nothing, if avaliable, check card is valid or not, is the same or not, if not, flash Red LED, if yes, turn on Green LED, call uploadData() , stop countDown(reset), set seatStatus occupied,;

void LEDControl(int LEDID, int action){}//turn on,turn off, flash...., LEDID: -1=green, 0=blue, 1=red(occupied)
//void countDown(bool reset){}//if time's up call resetAll(), uploadData().

void uploadData()//upload card, time, status, using json format.

void checkBtnPressed(){}//check seatStatus first, if seat avaliable or temporarily out, do nothing, if occupied, call countDown(), turn on blue LED, set seatStatus temporarily out, upload.

void resetAll(){}
