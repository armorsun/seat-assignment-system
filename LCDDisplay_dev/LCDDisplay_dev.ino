#include "lcddisplay.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//GND - GND
//VCC - 5V
//SDA - ANALOG Pin 4
//SCL - ANALOG pin 5

int timeReamined;
String cardID;
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display  
int action;

void setup()
{  
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  
  Serial.println("testing action == 1...");
  action = 1; //display avaliable and green light.
  lcddisplay();
  delay(3000);

  Serial.println("testing action == 4...");
  action = 4; //display invalide and flash red light.
  lcddisplay();
  delay(3000);
  
  Serial.println("testing action == 3...");
  action = 3; //display occupied and red.
  lcddisplay();
  delay(3000);

  
  Serial.println("testing action == 2...");
  action = 2;//display temporarily out and blue light.
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


