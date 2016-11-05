#include "lcddisplay.h"

//GND - GND
//VCC - 5V
//SDA - ANALOG Pin 4
//SCL - ANALOG pin 5

int seatStatus = -1;  //avaliable

void setup()
{  
  Serial.begin(9600);
  
  Serial.println("testing seatStatus = -1...");
  lcddisplay();
  delay('3000');
  
  Serial.println("testing seatStatus = 1...");
  seatStatus = 1; //occupied
  lcddisplay();
  delay('3000');

  Serial.println("testing seatStatus = 0...");
  seatStatus = 0; //temperarily leave
  lcddisplay();
  delay('3000');
  Serial.println("done testing!");

}


void loop()
{
//  Serial.print("mark3;");
}


