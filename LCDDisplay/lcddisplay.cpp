#include "lcddisplay.h"
#include "Arduino.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

void lcddisplay(){

  extern int seatStatus;  // access to global variable
  extern LiquidCrystal_I2C lcd;
  extern int Time;
  
//  LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display  
//  lcd.init();
//  lcd.backlight();

  if(seatStatus == -1){

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("[Avaliable]");
    lcd.setCursor(0,1);
    lcd.print("Insert ID card");
    
  }else if(seatStatus == 1) {

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("[Occupied]");
    lcd.setCursor(0,1);
    lcd.print("Report if empty");
    
  }else if(seatStatus == 0) {

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("[Away]");
    lcd.setCursor(0,1);
    int remainSec = (1800-Time)%60;
    int remainMin = ((1800-Time) - remainSec)/60;
    lcd.print("Reset in ");
    lcd.print(remainMin);
    lcd.print(":");
    lcd.print(remainSec);
    
  }
  
}

