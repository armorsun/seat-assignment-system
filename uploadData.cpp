#include <WiFi.h>
#include <SoftwareSerial.h>
#include "Arduino.h"

extern SoftwareSerial wifiSerial;
extern int seatStatus;
extern byte UIDStored[4];
extern int timeRemained;

void uploadData() {
  wifiSerial.println("AT+CIPSTART=\"TCP\",\"140.112.94.163\",9489");
  delay(2000);
  String cmd = "GET /?id=" + String((char*)UIDStored) + "&status=" + String(seatStatus) + "&time="+ timeRemained +" HTTP/1.1\r\n\r\n";
  wifiSerial.print("AT+CIPSEND=");
  wifiSerial.println(cmd.length());
  wifiSerial.flush();

  delay(4000);
  wifiSerial.print(cmd);
}
