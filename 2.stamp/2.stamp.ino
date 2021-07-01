#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 

int magnetic1 = 8;
int magnetic2 = 13;
int magnetic3 = 2;
int magnetic4 = 3;
int magnetic5 = 5;
int magnetic6 = 4;
int relay = 6;
int currentState = 0;

void setup() {
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(18);
  
  pinMode(magnetic1, INPUT);
  pinMode(magnetic2, INPUT);
  pinMode(magnetic3, INPUT);
  pinMode(magnetic4, INPUT);
  pinMode(magnetic5, INPUT);
  pinMode(magnetic6, INPUT);
  pinMode(relay, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(relay, LOW);
  if(currentState == 0) {
    if(digitalRead(magnetic1) == 0){
      currentState = 1;
      mp3_play(13);
    }
    if(digitalRead(magnetic2) == 0 || digitalRead(magnetic3) == 0 || digitalRead(magnetic4) == 0 || digitalRead(magnetic5) == 0 || digitalRead(magnetic6) == 0){
      mp3_play(14);
      delay(1000);
      currentState = 0; 
    }
  }

  if(currentState == 1) {
    if(digitalRead(magnetic2) == 0){
      currentState = 2;
      mp3_play(13);
    }
    if(digitalRead(magnetic3) == 0 || digitalRead(magnetic4) == 0 || digitalRead(magnetic5) == 0 || digitalRead(magnetic6) == 0){
      mp3_play(14);
      delay(1000);
      currentState = 0; 
    }
  }

  if(currentState == 2) {
    if(digitalRead(magnetic3) == 0){
      currentState = 3;
      mp3_play(13);
    }
    if(digitalRead(magnetic1) == 0 || digitalRead(magnetic4) == 0 || digitalRead(magnetic5) == 0 || digitalRead(magnetic6) == 0){
      mp3_play(14);
      delay(1000);
      currentState = 0; 
    }
  }

  if(currentState == 3) {
    if(digitalRead(magnetic4) == 0){
      currentState = 4;
      mp3_play(13);
    }
    if(digitalRead(magnetic1) == 0 || digitalRead(magnetic2) == 0 || digitalRead(magnetic5) == 0 || digitalRead(magnetic6) == 0){
      mp3_play(14);
      delay(1000);
      currentState = 0; 
    }
  }

  if(currentState == 4) {
    if(digitalRead(magnetic5) == 0){
      currentState = 5;
      mp3_play(13);
    }
    if(digitalRead(magnetic1) == 0 || digitalRead(magnetic2) == 0 || digitalRead(magnetic3) == 0 || digitalRead(magnetic6) == 0){
      mp3_play(14);
      delay(1000);
      currentState = 0; 
    }
  }

  if(currentState == 5) {
    if(digitalRead(magnetic6) == 0) {
      good();
    }
    if(digitalRead(magnetic1) == 0 || digitalRead(magnetic2) == 0 || digitalRead(magnetic3) == 0 || digitalRead(magnetic4) == 0){
      mp3_play(14);
      delay(1000);
      currentState = 0; 
    }
  }
}

void good() {
  mp3_play(13);
  delay(1500);
  digitalWrite(relay, HIGH);
  delay(10000);
  currentState = 0; 
}
