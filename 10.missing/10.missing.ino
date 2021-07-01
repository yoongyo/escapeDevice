#include <SPI.h>
#include <MFRC522.h>

int relay = 12;

int mg = 25;
const byte numReaders = 4;
const byte ssPins[] = {4, 5, 40, 41};

const byte resetPin = 53;
bool correct[] = {false, false, false, false};

MFRC522 mfrc522[numReaders];
String currentIDs[numReaders];

bool finish = false;
bool finish2 = false;

void setup() {
  pinMode(relay, OUTPUT);
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
  digitalWrite(relay, LOW);
  boolean rfidSolved = true;
  boolean changedValue = false;
  if(digitalRead(mg) == 1 && currentIDs[0] == "" && currentIDs[1] == "" && currentIDs[2] == "" && currentIDs[3] == "") {
    finish = false;
    finish2 = false;
    correct[0] = false;
    correct[1] = false;
    correct[2] = false;
    correct[3] = false;
  }

  if(correct[0] == true && correct[1] == true && correct[2] == true && correct[3] == true && digitalRead(mg) == 0) {
    finish = true;
  } 
  
  if (finish) {
    if (!finish2) {
      digitalWrite(relay, HIGH);
      delay(3000);
      finish2 = true; 
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
      if (i == 0 && (currentIDs[i] == "5cbaf531" || currentIDs[i] == "f2de24d9" || currentIDs[i] == "93e29316" || currentIDs[i] == "fce3332")){
        Serial.println("호박");
        correct[i] = true;
      } 
      if (i == 1 && (currentIDs[i] == "a173985" || currentIDs[i] == "da3cb880" || currentIDs[i] == "3a9f3b86" || currentIDs[i] == "5c6ba932")){
        Serial.println("무전기");
        correct[i] = true;
      } 
      if (i == 2 && (currentIDs[i] == "6bb4ff21" || currentIDs[i] == "9a9b8619" || currentIDs[i] == "73768a16" || currentIDs[i] == "2a898b19" || currentIDs[i] == "d91b915a" || currentIDs[i] == "937a9916")){
        Serial.println("피자");
        correct[i] = true;
      } 
      if (i == 3 && (currentIDs[i] == "3c38b16" || currentIDs[i] == "1b4a222" || currentIDs[i] == "93e29316" || currentIDs[i] == "ca1b51a")){
        Serial.println("지갑");
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
