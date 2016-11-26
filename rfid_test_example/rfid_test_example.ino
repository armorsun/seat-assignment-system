#include <SPI.h>
#include <MFRC522.h>

// construct a object of MFRC522 
MFRC522 mfrc522(10,9); //9=RST_PIN 10=SS_PIN

int seatStatus = -1 ; //3 status: -1=avaliable, 0=temporarily out, 1=occupied (LEDID: -1=green, 0=blue, 1=red(occupied))
int action = 1;
byte UIDStored[4];

void setup(){ // in the main program
  Serial.begin(9600); // for debuging
  Serial.println("RFID reader is ready!");
  
  SPI.begin(); //initialize SPI
  mfrc522.PCD_Init(); //initialize mfrc522  
  
  pinMode(2,OUTPUT);
}
 
void loop() {

    // card proximity = 2.5cm.
    // check card is valid or not first.
    // the card validity variable = the card number is read. 
    // IsNewCardPresent for excatly "new" card.
    
    boolean rfidValid = (mfrc522.PICC_IsNewCardPresent()&&mfrc522.PICC_ReadCardSerial());
    if (rfidValid == true) {
      // the data structure is "byte".
      byte *id = mfrc522.uid.uidByte; // get UID
      byte idSize = mfrc522.uid.size; // get length of UID
 
      Serial.print("PICC type: "); 
      // card type by reading sak.
      MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
      Serial.println(mfrc522.PICC_GetTypeName(piccType));
 
      Serial.print("UID Size: ");
      Serial.println(idSize);
      
      // store the UID
      for (byte i = 0; i < idSize; i++){ 
      UIDStored[i]=id[i];
      }
      
      for (byte i = 0; i < idSize; i++) { // display UID
        Serial.print("idStored[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.println(UIDStored[i], HEX);// display UID in 16.
      }
      Serial.println();
    mfrc522.PICC_HaltA();
    digitalWrite(2,LOW);
    }else {
      
      Serial.println("no card.");
    
      digitalWrite(2,HIGH); 
      delay(700);
      digitalWrite(2,LOW); 
      delay(700);
      digitalWrite(2,HIGH); 
      delay(700);
      digitalWrite(2,LOW); 
      delay(700);

    }
}
