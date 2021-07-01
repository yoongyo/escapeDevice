#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 

int magnetic1 = 2;
int magnetic2 = 3;
int magnetic3 = 4;
int magnetic4 = 5;
int magnetic5 = 6;
int magnetic6 = 7;
int magnetic7 = 8;
int relay = 13;
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
  pinMode(magnetic7, INPUT);
  pinMode(relay, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(relay, HIGH);
  if(digitalRead(magnetic1)) == HIGH) {
    if(currentState == 0) {
      currentState = 1;
      mp3_play(1);
    }else {
      currentState = 0;
      mp3_play(1);
    }
  }
  if(digitalRead(magnetic2)) == HIGH) {
    if(currentState == 1) {
      currentState = 2;
      mp3_play(1);
    }else {
      currentState = 0;
      mp3_play(2);
    }
  }
  if(digitalRead(magnetic3)) == HIGH) {
    if(currentState == 2) {
      currentState = 3;
      mp3_play(1);
    }else {
      currentState = 0;
      mp3_play(2);
    }
  }
  if(digitalRead(magnetic4)) == HIGH) {
    if(currentState == 3) {
      currentState = 4;
      mp3_play(1);
    }else {
      currentState = 0;
      mp3_play(2);
    }
  }
  if(digitalRead(magnetic5)) == HIGH) {
    if(currentState == 4) {
      currentState = 5;
      mp3_play(1);
    }else {
      currentState = 0;
      mp3_play(2);
    }
  }
  if(digitalRead(magnetic6)) == HIGH) {
    if(currentState == 5) {
      currentState = 6;
      mp3_play(1);
    }else {
      currentState = 0;
      mp3_play(2);
    }
  }
  if(digitalRead(magnetic7)) == HIGH) {
    if(currentState == 6) {
      // 성공
      delay(2000);
      digitalWrite(relay, LOW);
      delay(200);
      currentState = 0;
    }else {
      currentState = 0;
      mp3_play(2);
    }
  }
}
