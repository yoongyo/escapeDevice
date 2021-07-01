#include <SPI.h>
#include <MFRC522.h>
#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 

int mg = 8;
const byte numReaders = 4;
const byte ssPins[] = {3,4,6,7};

const byte resetPin = 53;
const String medicine[] = {"c5354b73" , "f5b74973", "2c21fc31", "da3cb880"};
String ids[] = {"", "", "", ""};


MFRC522 mfrc522[numReaders];
String currentIDs[numReaders];

bool play = false;

void setup() {
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(28);
  
  pinMode(mg, INPUT);
  Serial.begin(9600);
  Serial.println(F("Serial communication started"));
  
  // Initialise the SPI bus
  SPI.begin();

  for (uint8_t i = 0; i < numReaders; i++) {
    mfrc522[i].PCD_Init(ssPins[i], resetPin);
    delay(4);
    Serial.print(F("Reader #"));
    Serial.print(i);
    Serial.print(F(" initialised on pin "));
    Serial.print(String(ssPins[i]));
    Serial.print(F(". Antenna strength: "));
    Serial.print(mfrc522[i].PCD_GetAntennaGain());
    Serial.print(F(". Version : "));
    mfrc522[i].PCD_DumpVersionToSerial();
    delay(100);
  }

  Serial.println(F("--- END SETUP ---"));
}


void loop() {
  boolean rfidSolved = true;
  boolean changedValue = false;
  if(digitalRead(mg) == 1) {
    play = false;
  }
  if(ids[0] == medicine[0] && ids[1] == medicine[1] && ids[2] == medicine[2] && ids[3] == medicine[3] && digitalRead(mg) == 0){
    if (!play) {
      mp3_play(1);
      delay(60000);
      Serial.println("FFFF");
    }
    play = true;
  }
  
  for (uint8_t i = 0; i < numReaders; i++) {
    mfrc522[i].PCD_Init();
    String readRFID = "";
    if (mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()) {
      readRFID = dump_byte_array(mfrc522[i].uid.uidByte, mfrc522[i].uid.size);
    }
    if (readRFID != currentIDs[i] ) {
      changedValue = true;
      currentIDs[i] = readRFID;
      Serial.println(readRFID);
    }
    
    mfrc522[i].PICC_HaltA();
    mfrc522[i].PCD_StopCrypto1();
  }
  if (changedValue) {
    for (uint8_t i = 0; i < numReaders; i++) {
      Serial.print(F("Reader #"));
      Serial.print(String(i));
      Serial.print(F(" on Pin #"));
      Serial.print(String((ssPins[i])));
      Serial.print(F(" detected tag: "));
      Serial.println(currentIDs[i]);
      ids[i] = currentIDs[i];
    }
    Serial.println(F("--------------"));
  }
}

String dump_byte_array(byte *buffer, byte bufferSize) {
  String read_rfid = "";
  for (byte i = 0; i < bufferSize; i++) {
    read_rfid = read_rfid + String(buffer[i], HEX);
  }
  return read_rfid;
}
