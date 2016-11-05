#include "checkBtnPressed.h"

void setup() {
  
  Serial.begin(9600);
  pinMode(6, INPUT);

}

void loop() {

  if(digitalRead(6)==HIGH){
    Serial.println("Pressed at " + millis());    
  }

}
