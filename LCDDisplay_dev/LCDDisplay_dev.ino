#include "lcddisplay.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//GND - GND
//VCC - 5V
//SDA - ANALOG Pin 4
//SCL - ANALOG pin 5

int seatStatus;  //avaliable
int timeReamined;
String cardID;
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display  
int action;

void setup()
{  
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  
  Serial.println("testing seatStatus == -1...");
  seatStatus = -1; //available
  lcddisplay();
  delay(3000);

  Serial.println("testing action == 4...");
  action = 4; //available
  lcddisplay();
  delay(3000);
  action =0;
  
  Serial.println("testing seatStatus == 1...");
  seatStatus = 1; //occupied
  lcddisplay();
  delay(3000);

  Serial.println("testing seatStatus == 0...");
  seatStatus = 0; //temperarily leave

  for(int i=1800; i>=0; i--){
    timeReamined = i;
    lcddisplay(); // update LCD by inspecting Time 
    delay(1000);
  }
  
  Serial.println("done testing!");

}


void loop()
{
}


