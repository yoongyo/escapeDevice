#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 

int right4 = 2;
int left3 = 3;
int left2 = 22;
int left1 = 5;
int left4 = 6;
int right3 = 7;
int right1 = 8;
int right2 = 24;

int ledList[] = {2, 3, 22, 5, 6, 7, 8, 24};
int blinkDelayTime = 200;

int button = 53;

int resetBtn = 52;

int uvLanternBox = 13;

int beforeState = 0;
int afterState = 1;

bool knockTime = false;

long previousMillis = 0;
long currentMillis = 0;

long buttonTime = 0;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(18);
  pinMode(resetBtn, INPUT_PULLUP);
  pinMode(uvLanternBox, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  for (int i=0; i<8; i++) {
    pinMode(ledList[i], OUTPUT);
  }
  Serial.println("fuck");
}

void loop() {
//  Serial.println(digitalRead(resetBtn));
  if(digitalRead(resetBtn) == 0) {
    knockTime = false;
  }
  
  digitalWrite(uvLanternBox, LOW);
//  Serial.println(digitalRead(button));
  // 버튼 누름 감지 
  if(!knockTime){
    if(digitalRead(button) == 0) {
      buttonTime++;
      if(buttonTime >= 100) {
        knockTime = true;
        delay(1000);
        digitalWrite(uvLanternBox, HIGH);
        delay(200);
        allLedOn();
      }
    }
  }
  
  // 버튼 누르기 전 
  if(!knockTime) {
    beforePattern();
  } 
  // 버튼 누른 후 
  else {
    afterPattern();
  }
}

void beforePattern() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= 3000 && beforeState == 0) {
    digitalWrite(right3, HIGH);
    digitalWrite(left2, HIGH);
    previousMillis = currentMillis;
    beforeState = 1;
  }
  if (currentMillis - previousMillis >= 1500 && beforeState == 1) {
    digitalWrite(right3, LOW);
    digitalWrite(left2, LOW);
    previousMillis = currentMillis;
    beforeState = 2;
  }
  if (beforeState == 2) {
    digitalWrite(right2, HIGH);
    digitalWrite(left3, HIGH);
  }
  if (currentMillis - previousMillis >= 1500 && beforeState == 2) {
    digitalWrite(right2, LOW);
    digitalWrite(left3, LOW);
    previousMillis = currentMillis;
    beforeState = 3;
  }
  if (beforeState == 3) {
    digitalWrite(right4, HIGH);
    digitalWrite(left1, HIGH);
  }
  if (currentMillis - previousMillis >= 1500 && beforeState == 3) {
    digitalWrite(right4, LOW);
    digitalWrite(left1, LOW);
    previousMillis = currentMillis;
    beforeState = 4;
  }
  if (beforeState == 4) {
    digitalWrite(right1, HIGH);
    digitalWrite(left4, HIGH);
  }
  if (currentMillis - previousMillis >= 1500 && beforeState == 4) {
    digitalWrite(right1, LOW);
    digitalWrite(left4, LOW);
    previousMillis = currentMillis;
    beforeState = 5;
  }
  if (beforeState == 5) {
    digitalWrite(right4, HIGH);
    digitalWrite(left1, HIGH);
  }
  if (currentMillis - previousMillis >= 1500 && beforeState == 5) {
    digitalWrite(right4, LOW);
    digitalWrite(left1, LOW);
    previousMillis = currentMillis;
    beforeState = 6;
  }
  if (beforeState == 6) {
    digitalWrite(right2, HIGH);
    digitalWrite(left3, HIGH);
  }
  if (currentMillis - previousMillis >= 1500 && beforeState == 6) {
    digitalWrite(right2, LOW);
    digitalWrite(left3, LOW);
    previousMillis = currentMillis;
    beforeState = 0;
  }
}

void afterPattern() {
  if (afterState == 1) {
    allLedOn();
    currentMillis = millis();
    if (currentMillis - previousMillis >= blinkDelayTime) {
      allLedOff();
      afterState = 2;
      previousMillis = currentMillis;
    }
  }

  if (afterState == 2){
    currentMillis = millis();
    if (currentMillis - previousMillis >= 750-blinkDelayTime) {
      afterState = 3;
      previousMillis = currentMillis;
    }
  }
  
  if (afterState == 3) {
    allLedOn();
    currentMillis = millis();
    if (currentMillis - previousMillis >= blinkDelayTime) {
      allLedOff();
      afterState = 4;
      previousMillis = currentMillis;
    }
  }

  if (afterState == 4){
    currentMillis = millis();
    if (currentMillis - previousMillis >= 375-blinkDelayTime) {
      afterState = 5;
      previousMillis = currentMillis;
    }
  }

  if (afterState == 5) {
    allLedOn();
    currentMillis = millis();
    if (currentMillis - previousMillis >= blinkDelayTime) {
      allLedOff();
      afterState = 6;
      previousMillis = currentMillis;
    }
  }

  if (afterState == 6) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= 375-blinkDelayTime) {
      afterState = 7;
      previousMillis = currentMillis;
    }
  }

  if (afterState == 7){
    allLedOn();
    currentMillis = millis();
    if (currentMillis - previousMillis >= blinkDelayTime) {
      allLedOff();
      afterState = 8;
      previousMillis = currentMillis;
    }
  }

  if (afterState == 8) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= 750-blinkDelayTime) {
      afterState = 9;
      previousMillis = currentMillis;
    }
  }

  if (afterState == 9){
    allLedOn();
    currentMillis = millis();
    if (currentMillis - previousMillis >= blinkDelayTime) {
      allLedOff();
      afterState = 10;
      previousMillis = currentMillis;
    }
  }

  if (afterState == 10) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= 3500-blinkDelayTime) {
      afterState = 1;
      previousMillis = currentMillis;
    }
  }
}


void allLedOn() {
  for(int i=0; i<8; i++) {
    digitalWrite(ledList[i], HIGH);
  }
}

void allLedOff() {
  for(int i=0; i<8; i++) {
    digitalWrite(ledList[i], LOW);
  }
}
