#include <Time.h>
#include <TimeAlarms.h>
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
int uvLanternBox = 52;

int knockSensor = 12;
int door = 13;

bool knockTime = false;
int beforeState = 1;
int afterState = 1;

// 노크 값들
const int rejectValue = 25;
const int averageRejectValue = 15;
const int knockFadeTime = 100;
const int maximumKnocks = 20;
const int knockComplete = 1200;
int secretCode[maximumKnocks] = {100, 50, 50, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  
int knockReadings[maximumKnocks];   
int knockSensorValue = 0;           
int programButtonPressed = false; 

long previousMillis = 0;
long currentMillis = 0;

void setup() {
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(18);
  pinMode(door, OUTPUT);
  pinMode(uvLanternBox, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  for (int i=0; i<8; i++) {
    pinMode(ledList[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  digitalWrite(door, LOW);
  digitalWrite(uvLanternBox, LOW);
  
  // 버튼 누름 감지 
  if(digitalRead(button) == 0) {
    knockTime = true;
    digitalWrite(uvLanternBox, HIGH);
    delay(200);
    allLedOn();
  }
  
  // 버튼 누르기 전 
  if(!knockTime) {
    beforePattern();
  } 
  // 버튼 누른 후 
  else {
    afterPattern();
//    knockDetect();
  }
}

void beforePattern() {
  currentMillis = millis();
  if (beforeState == 1) {
    digitalWrite(right1, HIGH);
    digitalWrite(left1, HIGH);
  }
  if (currentMillis - previousMillis >= 1500 && beforeState == 1) {
    digitalWrite(right1, LOW);
    digitalWrite(left1, LOW);
    previousMillis = currentMillis;
    beforeState = 2;
  }
  if (beforeState == 2) {
    digitalWrite(left2, HIGH);
    digitalWrite(right2, HIGH);
  }
  if (currentMillis - previousMillis >= 1500 && beforeState == 2) {
    digitalWrite(left2, LOW);
    digitalWrite(right2, LOW);
    previousMillis = currentMillis;
    beforeState = 3;
  }
  if (beforeState == 3) {
    digitalWrite(left3, HIGH);
    digitalWrite(right3, HIGH);
  }
  if (currentMillis - previousMillis >= 1500 && beforeState == 3) {
    digitalWrite(left3, LOW);
    digitalWrite(right3, LOW);
    previousMillis = currentMillis;
    beforeState = 4;
  }
  if (beforeState == 4) {
    digitalWrite(left4, HIGH);
    digitalWrite(right4, HIGH);
  }
  if (currentMillis - previousMillis >= 1500 && beforeState == 4) {
    digitalWrite(left4, LOW);
    digitalWrite(right4, LOW);
    previousMillis = currentMillis;
    beforeState = 5;
  }
  if (beforeState == 5) {
    digitalWrite(left1, HIGH);
    digitalWrite(right1, HIGH);
  }
  if (currentMillis - previousMillis >= 1500 && beforeState == 5) {
    digitalWrite(left1, LOW);
    digitalWrite(right1, LOW);
    previousMillis = currentMillis;
    beforeState = 6;
  }
  if (beforeState == 6) {
    digitalWrite(left2, HIGH);
    digitalWrite(right2, HIGH);
  }
  if (currentMillis - previousMillis >= 1500 && beforeState == 6) {
    digitalWrite(left2, LOW);
    digitalWrite(right2, LOW);
    previousMillis = currentMillis;
    beforeState = 7;
  }
  if (beforeState == 7) {
    digitalWrite(left3, HIGH);
    digitalWrite(right3, HIGH);
  }
  if (currentMillis - previousMillis >= 1500 && beforeState == 7) {
    digitalWrite(left3, LOW);
    digitalWrite(right3, LOW);
    previousMillis = currentMillis;
    beforeState = 8;
  }
  if (beforeState == 8) {
    digitalWrite(left4, HIGH);
    digitalWrite(right4, HIGH);
  }
  if (currentMillis - previousMillis >= 1500 && beforeState == 8) {
    digitalWrite(left4, LOW);
    digitalWrite(right4, LOW);
    previousMillis = currentMillis;
    beforeState = 1;
  }
}

void afterPattern() {
  Serial.println(afterState);
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

void blinkDelay() {
  Alarm.delay(blinkDelayTime);
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

void knockDetect() {
  knockSensorValue = digitalRead(knockSensor);
  if (knockSensorValue == 0){
    listenToSecretKnock();
  }
}

void listenToSecretKnock(){
  Serial.println("knock starting");   
  int i = 0;
  for (i=0;i<maximumKnocks;i++){
    knockReadings[i]=0;
  }
 
  int currentKnockNumber=0;               
  int startTime=millis();                 
  int now=millis();
  
  delay(knockFadeTime);                               
  do {
    knockSensorValue = digitalRead(knockSensor);
    if (knockSensorValue == 0){                   
      Serial.println("knock.");
      now=millis();
      knockReadings[currentKnockNumber] = now-startTime;
      Serial.println(knockReadings[currentKnockNumber]);
      currentKnockNumber ++;                             
      startTime=now;          
      delay(knockFadeTime);                             
    }
    now=millis();
  } while ((now-startTime < knockComplete) && (currentKnockNumber < maximumKnocks));  
  if (validateKnock() == true){
    triggerDoorUnlock(); 
  } else {
    Serial.println("Secret knock failed.");
  }
}

void triggerDoorUnlock(){
  Serial.println("Door unlocked!");
  int i=0;
  digitalWrite(door, HIGH);
  delay(200);
  allLedOff();
}

boolean validateKnock() {
  int i=0;
 
  int currentKnockCount = 0;
  int secretKnockCount = 0;
  int maxKnockInterval = 0;              
  
  for (i=0;i<maximumKnocks;i++){
    if (knockReadings[i] > 0){
      currentKnockCount++;
    }
    if (secretCode[i] > 0){           
      secretKnockCount++;
    }
    
    if (knockReadings[i] > maxKnockInterval){   
      maxKnockInterval = knockReadings[i];
    }
  }
  
  if (programButtonPressed==true) {
    for (i=0;i<maximumKnocks;i++) { 
      secretCode[i]= map(knockReadings[i],0, maxKnockInterval, 0, 100); 
    }
    delay(1000);
    delay(50);
    for (i = 0; i < maximumKnocks ; i++){
      if (secretCode[i] > 0){                                   
        delay(map(secretCode[i],0, 100, 0, maxKnockInterval)); 
      }
      delay(50);
    }
  return false;   
  }
  
  if (currentKnockCount != secretKnockCount){
    return false; 
  }
  
  int totaltimeDifferences=0;
  int timeDiff=0;
  for (i=0;i<maximumKnocks;i++){ // Normalize the times
    knockReadings[i]= map(knockReadings[i],0, maxKnockInterval, 0, 100);      
    timeDiff = abs(knockReadings[i]-secretCode[i]);
    if (timeDiff > rejectValue){ // Individual value too far out of whack
      return false;
    }
    totaltimeDifferences += timeDiff;
  }
  if (totaltimeDifferences/secretKnockCount>averageRejectValue){
    return false; 
  }
  return true;
}
