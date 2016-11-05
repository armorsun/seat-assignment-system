#include "checkBtnPressed.h"

void setup() {
  
  Serial.begin(9600);

}

void loop() {
  Serial.println("a"+millis());
  delay(1000);
}
