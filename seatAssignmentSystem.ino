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

#define ESP8266_RX 11
#define ESP8266_TX 12

SoftwareSerial wifiSerial(ESP8266_RX, ESP8266_TX);
MFRC522 mfrc522(10, 9); //9=RST_PIN 10=SS_PIN
LiquidCrystal_I2C lcd(0x27, 20, 4);

const char* ssid = "Kai";
const char* password = "xddddddd";

int seatStatus = -1; //3 status: -1=avaliable, 0=temporarily out, 1=occupied (LEDID: -1=green, 0=blue, 1=red(occupied))
int timeRemained;
byte UIDStored[4]; //the UID stored.
int action = 1;  //7 action, anyone can add, if needed

//action=1, display avaliable and green light.
//action=2, display temporarily out and blue light.
//action=3, display occupied and red.
//action=4, display invalid and flash red light.
//action=5, display "Right ID card" when be back.
//action=6, display "Card is registered."
//action=7, display "NOT Right ID card"

void setup() {
  Serial.begin(9600);
  while (!Serial);
  wifiSerial.begin(9600);

  // lcd initialization
  lcd.init();
  lcd.backlight();

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
}

void loop() {

  //---Remind that the effect LEDControl(x,2) and lcddisplay are constant.---//
  //---Remind that the effect LEDControl(x,1) has the function of delaying 0.75s.//

  checkCardPlaced();//using photointerupter to detect if a card is placed, if yes call readCardData(),
  //if not, do nothing.

  checkBtnPressed();//check seatStatus first,
  //if seat avaliable or temporarily out, do nothing,
  //if occupied, start countdown(e.g.  set timeRemained=1800), turn on blue LED, set seatStatus temporarily out, uploadData().

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
//void LCDDisplay(){}   //check action

//void readCardData(){} //check seatStatus,
//if not avaliable, flash red light and do nothing, set action=4
//if avaliable, check card is valid or not, is the same or not,
//if not, flash Red LED, set action=4
//if yes, turn on green LED, call uploadData() , set timeRemaind=0, set seatStatus=occupied, set action=3

//void LEDControl(int LEDID){}//turn on,turn off, flash...., LEDID: -1=green, 0=blue, 1=red, check action

//void uploadData(){}//upload card, timeRemained, status, using json format.

//void resetAll(){}//seatStatus=-1, action=1, timeRemained=0, LCDDisplay, LEDControl, uploadData
