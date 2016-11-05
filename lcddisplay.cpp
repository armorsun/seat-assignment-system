#include "lcddisplay.h"
#include "Arduino.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

void lcddisplay(){

  extern int seatStatus;  // access to global variable
  extern LiquidCrystal_I2C lcd;
  extern int timeReamined;
  extern int action;
  
//  LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display  
//  lcd.init();
//  lcd.backlight();

  if(action == 4){

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("[Error]");
    lcd.setCursor(0,1);
    lcd.print("Invaid ID card");
    
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
    int remainedSec = timeReamined%60;
    int remainedMin = (timeReamined - remainedSec)/60;
    lcd.print("Reset in ");
    lcd.print(remainedMin);
    lcd.print(":");
    lcd.print(remainedSec);
    
  }
  
}

