#define RLED 3
#define GLED 4
#define BLED 5

#include "LEDControl.h"
#include "Arduino.h"

void LEDControl(int LEDID, int action){ 

pinMode(RLED,OUTPUT);
pinMode(GLED,OUTPUT);
pinMode(BLED,OUTPUT);

  //LEDID: -1=green(avaliable), 0=blue(temporarily out), 1=red(occupied)
  //LEDID: 2=on, 1=flash, 0=off.
  
  if( LEDID==-1 && action==2 ) digitalWrite(GLED,HIGH); // Green on
  if( LEDID== 0 && action==2 ) digitalWrite(BLED,HIGH); // blue on
  if( LEDID== 1 && action==2 ) digitalWrite(RLED,HIGH); // red on
  if( LEDID==-1 && action==0 ) digitalWrite(GLED,LOW); // Green off
  if( LEDID== 0 && action==0 ) digitalWrite(BLED,LOW); // blue off
  if( LEDID== 1 && action==0 ) digitalWrite(RLED,LOW); // red off
  if( LEDID==-1 && action==1 ) { // Green flash
    digitalWrite(GLED,HIGH); 
    delay(500);
    digitalWrite(GLED,LOW); 
    delay(500);
  }
  if( LEDID== 0 && action==1 ) { // blue flash
    digitalWrite(BLED,HIGH); 
    delay(500);
    digitalWrite(BLED,LOW); 
    delay(500);
  }
  if( LEDID== 1 && action==1 ) { // red flash
    digitalWrite(RLED,HIGH); 
    delay(500);
    digitalWrite(RLED,LOW); 
    delay(500);
  }
}
