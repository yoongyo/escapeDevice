#include <SPI.h>
#include <MFRC522.h>
#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 

int mg = 8;
const byte numReaders = 4;
const byte ssPins[] = {3,4,6,7};

const byte resetPin = 53;
const String medicine[] = {"c5354b73" , "f5b74973", "2c21fc31", "da3cb880"};
bool correct[] = {false, false, false, false};

MFRC522 mfrc522[numReaders];
String currentIDs[numReaders];

bool finish = false;
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
    Serial.println("play = false");
  }
  if(digitalRead(mg) == 1 && currentIDs[0] == "" && currentIDs[1] == "" && currentIDs[2] == "" && currentIDs[3] == "") {
    finish = false;
    correct[0] = false;
    correct[1] = false;
    correct[2] = false;
    correct[3] = false;
    play = false;
  }
  
  if(correct[0] == true && correct[1] == true && correct[2] == true && correct[3] == true && digitalRead(mg) == 0) {
    mp3_play(1);
    delay(60000);
    finish = true;
    play = true;
  } 
  if (finish) {
    if(!play && digitalRead(mg) == 0) {
      mp3_play(1);
      delay(60000);
      play = true;
    }
  }
  for (uint8_t i = 0; i < numReaders; i++) {
    mfrc522[i].PCD_Init();
    String readRFID = "";
    if (mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()) {
      readRFID = dump_byte_array(mfrc522[i].uid.uidByte, mfrc522[i].uid.size);
    }
    if (readRFID != currentIDs[i]) {
      changedValue = true;
      currentIDs[i] = readRFID;
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
      if (i == 0 && (currentIDs[i] == medicine[0])){
        correct[i] = true;
      } 
      if (i == 1 && (currentIDs[i] == medicine[1])){
        correct[i] = true;
      } 
      if (i == 2 && (currentIDs[i] == medicine[2])){
        correct[i] = true;
      } 
      if (i == 3 && (currentIDs[i] == medicine[3])){
        correct[i] = true;
      } 
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
