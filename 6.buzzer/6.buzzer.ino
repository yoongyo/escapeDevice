#include <Time.h>
#include <TimeAlarms.h>
#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 
// 1, 3, 4, 7, 8, 10
// mp3_1 = 아악
// mp3_2 = 틀린소리
// mp3_3 = 으아아아아아ㅏㄱ

int magnetic = 8;

int womanDoor = 13;   // nc    열때는 HIGH  닫혀있을 때는 LOW
int moodLight = 12;    // no   켤때는 HIGH  끌때는 LOW

int light = 52;       // nc

int led1 = 5;     
int led2 = 3;     
int led3 = 23;    
int led4 = 39;   
int led5 = 37;    
int led6 = 33;      
int led7 = 36;    
int led8 = 32;      
int led9 = 22;    
int led10 = 26; 

int ledList[] = {5, 3, 23, 39, 37, 33, 36, 32, 22, 26};

int button1 = 7;     
int button2 = 2;    
int button3 = 38;   
int button4 = 25;      
int button5 = 35;    
int button6 = 41;              
int button7 = 34;     
int button8 = 30;    
int button9 = 24;     
int button10 = 28;

int delayTime = 50;
int ledLen = 10;

String currentState = "step0";

int step2State = 0;

long previousMillis = 0;
boolean ledState = false;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(26);

  pinMode(magnetic, INPUT_PULLUP);
  pinMode(light, OUTPUT);
  pinMode(womanDoor, OUTPUT);
  pinMode(moodLight, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);
  pinMode(led10, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  pinMode(button6, INPUT_PULLUP);
  pinMode(button7, INPUT_PULLUP);
  pinMode(button8, INPUT_PULLUP);
  pinMode(button9, INPUT_PULLUP);
  pinMode(button10, INPUT_PULLUP);  
}

void loop() {
  Serial.println(currentState);
  if(currentState == "step0") {
    digitalWrite(moodLight, LOW);   // HIGH일 때 꺼짐, LOW 켜짐
    digitalWrite(womanDoor, LOW);   // HIGH일 때 닫김, LOW 열림
    digitalWrite(light, LOW);
    delay(200);
  }
  if(digitalRead(magnetic) == 0 && currentState == "step0") {
    // 액자 문제를 풀어 상자가 열림
    currentState = "step1";
  } 
  if (currentState == "step1") {
    step1();
  }
  if (currentState == "step2") {
    step2();
  }
  if(currentState == "step3") {
    step3();
  }
  if(currentState == "step4") {
    step4();
  }
  if(currentState == "step5") {
    step5();
  }
}

void allLedON() {
  for (int i = 0; i < 10; i++){
    digitalWrite(ledList[i], HIGH); 
  }
}

void allLedOFF() {
  for (int i = 0; i < 10; i++){
    digitalWrite(ledList[i], LOW); 
  }
}

void waveLed() {
  for(int i = 0; i < ledLen; i++) {
    long currentMillis = millis();
//    digitalWrite(ledList[i], HIGH);
    if(currentMillis - previousMillis >= delayTime) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(ledList[i], ledState);
    }
//    Alarm.delay(delayTime);
//    digitalWrite(ledList[i], LOW);
  }
  
  for (int i = ledLen -1; i > -1; i--) {
    long currentMillis = millis();
//    digitalWrite(ledList[i], HIGH);
//    Alarm.delay(delayTime);
//    digitalWrite(ledList[i], LOW);
    if(currentMillis - previousMillis >= delayTime) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(ledList[i], ledState);
    }
  }

  delayTime = delayTime - 5;
  if(delayTime < 0) {
    delayTime = 100;
  }
}

void step1() {
  // 지문 읽을 시간 10초를 줌
  delay(10000);
  // 소등
  digitalWrite(light, HIGH);
  // 무드등 ON
  digitalWrite(moodLight, HIGH);
  delay(200);
  // 전체 led ON
  allLedON();
  delay(5000);
  // 전체 led OFF
  allLedOFF();
  delay(1000);
  currentState = "step2";
}

void step2() {
  if (step2State == 0) {
    digitalWrite(led1, HIGH);
  }
  if (step2State == 1) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }
  if (step2State == 2) {
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
  }
  if (step2State == 3) {
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
  }
  if (step2State == 4) {
    digitalWrite(led4, LOW);
    digitalWrite(led5, HIGH);
  }
  if (step2State == 5) {
    digitalWrite(led5, LOW);
    digitalWrite(led6, HIGH);
  }
  if (step2State == 6) {
    digitalWrite(led6, LOW);
    digitalWrite(led7, HIGH);
  }
  if (step2State == 7) {
    digitalWrite(led7, LOW);
    digitalWrite(led8, HIGH);
  }
  if (step2State == 8) {
    digitalWrite(led8, LOW);
    digitalWrite(led9, HIGH);
  }
  if (step2State == 9) {
    digitalWrite(led9, LOW);
    digitalWrite(led10, HIGH);
  }
  if (step2State == 10) {
    digitalWrite(led10, LOW);
    currentState = "step3";
  }
  
  if(step2State == 0 && digitalRead(button1) == 0){
    step2State = 1;
    mp3_play(1);
  }
  if(step2State == 1 && digitalRead(button2) == 0){
    step2State = 2;
  }
  if(step2State == 2 && digitalRead(button3) == 0){
    step2State = 3;
    mp3_play(1);
  }
  if(step2State == 3 && digitalRead(button4) == 0){
    step2State = 4;
    mp3_play(1);
  }
  if(step2State == 4 && digitalRead(button5) == 0){
    step2State = 5;
  }
  if(step2State == 5 && digitalRead(button6) == 0){
    step2State = 6;
    mp3_play(1);
  }
  if(step2State == 6 && digitalRead(button7) == 0){
    step2State = 7;
  }
  if(step2State == 7 && digitalRead(button8) == 0){
    step2State = 8;
  }
  if(step2State == 8 && digitalRead(button9) == 0){
    step2State = 9;
    mp3_play(1);
  }
  if(step2State == 9 && digitalRead(button10) == 0){
    step2State = 10;    
    mp3_play(1);
  }
}

void step3() {
  waveLed();
  if(digitalRead(button2) == 0 || digitalRead(button5) == 0) {
    currentState = "step2";
    step2State = 0;
    allLedOFF();
    mp3_play(2);
  }
  if(digitalRead(button7) == 0 || digitalRead(button8) == 0){
    currentState = "step2";
    step2State = 0;
    allLedOFF();
    mp3_play(2);
  }
  if(digitalRead(button1)==0 && digitalRead(button3)==0 && digitalRead(button4)==0 && digitalRead(button6)==0 && digitalRead(button9)==0 && digitalRead(button10)==0){
    currentState = "step4";
    allLedOFF();
  } 
}

void step4() {
  mp3_play(3);
  delay(4500);
  // 문 열림
  digitalWrite(womanDoor, HIGH);
  delay(200);
  // light ON
  digitalWrite(light, LOW);
  // 무드등 OFF
  digitalWrite(moodLight, LOW);
  delay(200);
  currentState = "step5";
}

void step5() {
  if(digitalRead(button7)==0 && digitalRead(button9)==0 && digitalRead(button10)==0) {
    currentState = "step0";
    step2State = 0;
  }
}
