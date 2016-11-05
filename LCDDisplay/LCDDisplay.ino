#include "lcddisplay.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//GND - GND
//VCC - 5V
//SDA - ANALOG Pin 4
//SCL - ANALOG pin 5

int seatStatus = -1;  //avaliable
int Time = 0;
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display  

void setup()
{  
//  Serial.begin(9600);
//  
//  lcd.init();
//  lcd.backlight();
//  
//  Serial.println("testing seatStatus = -1...");
//  lcddisplay();
//  delay('20');
//  
//  Serial.println("testing seatStatus = 1...");
//  seatStatus = 1; //occupied
//  lcddisplay();
//  delay('20');
//
//  Serial.println("testing seatStatus = 0...");
//  seatStatus = 0; //temperarily leave
//
//  for(int i=0; i<=10; i++){
//    Time = i;
//    lcddisplay();
//    delay('10');
//  }
//  
//  Serial.println("done testing!");

}


void loop()
{
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  
  Serial.println("testing seatStatus = -1...");
  lcddisplay();
  delay('20');
  
  Serial.println("testing seatStatus = 1...");
  seatStatus = 1; //occupied
  lcddisplay();
  delay('20');

  Serial.println("testing seatStatus = 0...");
  seatStatus = 0; //temperarily leave

  for(int i=0; i<=10; i++){
    Time = i;
    lcddisplay();
    delay('10');
  }
  
  Serial.println("done testing!");
  
}


