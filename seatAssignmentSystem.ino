#include "lcddisplay.h"
#include "checkCardPlaced.h"
#include "LEDControl.h"
#include "checkBtnPressed.h"
#include "resetAll.h"
#include "uploadData.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <SoftwareSerial.h>

//for the RFID using 11, 12.
//#define ESP8266_RX 11 
//#define ESP8266_TX 12
#define ESP8266_RX A0
#define ESP8266_TX A1

SoftwareSerial wifiSerial(ESP8266_RX, ESP8266_TX);
MFRC522 mfrc522(10, 9); //9=RST_PIN 10=SS_PIN
LiquidCrystal_I2C lcd(0x27, 20, 4);

const char* ssid = "Kai";
const char* password = "xddddddd";

int seatStatus = -1; //3 status: -1=avaliable, 0=temporarily out, 1=occupied (LEDID: -1=green, 0=blue, 1=red(occupied))
int timeRemained;
byte UIDStored[4] = { 0, 0, 0, 0 }; //the UID stored.
int action = 1;  //7 action, anyone can add, if needed
unsigned long millisWhenLeave = 0;
unsigned long millisElapsed;

//action=1, display avaliable and green light.
//action=2, display temporarily out and blue light. USED AT THE CHANGE OF SEAT STATUS!!!
//action=3, display occupied and red.
//action=4, display invalid and flash red light.
//action=5, display "Right ID card" when be back.
//action=6, display "Card is registered."
//action=7, display "NOT Right ID card"
//action=8, display the updating the time! USED DURING THE SEAT STATUS!!!

void setup() {
  Serial.begin(9600);
  while (!Serial);
  wifiSerial.begin(9600);

  // lcd initialization
  lcd.init(); // controller open
  lcd.backlight(); // light open

  // RFID initialization
  SPI.begin();
  mfrc522.PCD_Init();

  //wifi initialization
  wifiSerial.println("AT+RST");
  wifiSerial.flush();

  if (wifiSerial.find("ready")) {
    Serial.println("WiFi module is good!");
  }
  else {
    Serial.println("Is WiFi module connected ?");
  }

  if (WiFiConnected()) {
    Serial.println("WiFi is connected!");
  }
  else {
    Serial.println("Cannot connect to WiFi!");
  }

  // the default setting of LED & LCD
  LEDControl(-1, 2);
  lcddisplay();
}

void loop() {

  //---Remind that the effect LEDControl(x,2) and lcddisplay are constant.---//
  //---Remind that the effect LEDControl(x,1) has the function of delaying 0.75s.//

  //====from "available" to "Away"====// -> IMPOSSIBLE

  //====from "occupied" to "Away"====// -> by button [checkBtnPressed()]
  checkBtnPressed();

  //==== from "Away" to "available" ====// -> after 5 secs [here in main program]
  if (seatStatus == 0) {
    millisElapsed = millis() - millisWhenLeave;
    if (millisElapsed < 10000) { // 10000 the for debugging ; actually 1800000
      Serial.print("Milliseconds elapsed: ");
      Serial.println(millisElapsed);

      timeRemained = timeRemained - millisElapsed/1000; // automatically calculated as integer.
      action = 8;
      lcddisplay();
      
    } else if (millisElapsed >= 10000) {
      Serial.print("TIME'S UP!");
      resetAll();
    }
  }

  //====from "Available" to "occupied" ====// -> by card in [readCardData()]
  //====from "occupied" to "Available" ====// -> by card out [checkCardPlaced()]
  //====from "Away" to "occupied" ====// -> by card back [readCardData()]
  checkCardPlaced();

}

boolean WiFiConnected() {
  wifiSerial.println("AT+CWMODE=1");
  String connectCmd = "AT+CWJAP=\"";
  connectCmd += ssid;
  connectCmd += "\",\"";
  connectCmd += password;
  connectCmd += "\"";
  wifiSerial.println(connectCmd);
  delay(2000);

  if (wifiSerial.find("CONNECTED")) {
    return true;
  } else {
    while (wifiSerial.available()) {
      Serial.write(wifiSerial.read());
    }
    return false;
  }
}
