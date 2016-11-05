#include "lcddisplay.h"
#include "Arduino.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

void lcddisplay(){

  extern int seatStatus;  // access to global variable
  
  LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display  
  lcd.init();                      // initialize the lcd 
  lcd.backlight();

  if(seatStatus == -1){
    lcd.setCursor(0,0);
    lcd.print("[-1]");
    lcd.setCursor(0,1);
    lcd.print("insert ID card");
  }else if(seatStatus == 1) {
    lcd.setCursor(0,0);
    lcd.print("[1]");
    lcd.setCursor(0,1);
    lcd.print("insert ID card");
  }else if(seatStatus == 0) {
    lcd.setCursor(0,0);
    lcd.print("[0]");
    lcd.setCursor(0,1);
    lcd.print("insert ID card");
  }
  
}

