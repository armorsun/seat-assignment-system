#include "lcddisplay.h"
#include "Arduino.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

void lcddisplay(){

  extern int seatStatus;  // access to global variable
  extern LiquidCrystal_I2C lcd;
  extern int timeRemained;
  extern int action;
  
//  LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display  
//  lcd.init();
//  lcd.backlight();

            //action=1, display avaliable and green light.
            //action=2, display temporarily out and blue light.
            //action=3, display occupied and red.
            //action=4, display invalid and flash red light.
            //action=5, display "Right ID card" when be back.
            //action=6, display "Card is registered."
            //action=7, display "NOT Right ID card"

  if(action == 4){

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("[Error]");
    lcd.setCursor(0,1);
    lcd.print("Invalid ID card");
    
  }else if(action == 1){

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("[Avaliable]");
    lcd.setCursor(0,1);
    lcd.print("Insert ID card");
    
  }else if(action == 3) {

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("[Occupied]");
    lcd.setCursor(0,1);
    lcd.print("Report if empty");
    
  }else if(action == 2) {

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("[Away]");
    lcd.setCursor(0,1);
    int remainedSec = timeRemained%60;
    int remainedMin = (timeRemained - remainedSec)/60;
    lcd.print("Reset in ");
    lcd.print(remainedMin);
    lcd.print(":");
    lcd.print(remainedSec);
    
  }else if(action == 5){
    lcd.setCursor(0,0);
    lcd.print("Right ID card");
    lcd.setCursor(0,1);
    lcd.print("");    
  }else if(action == 6){
    lcd.setCursor(0,0);
    lcd.print("Card is registered.");
    lcd.setCursor(0,1);
    lcd.print("");    
  }else if(action == 7){
    lcd.setCursor(0,0);
    lcd.print("NOT Right ID card");
    lcd.setCursor(0,1);
    lcd.print("");    
  }
  
}

