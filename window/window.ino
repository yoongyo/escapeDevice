#include <Time.h>
#include <TimeAlarms.h>
#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 


int leftLed1 = 2;
int leftLed2 = 3;
int leftLed3 = 4;
int leftLed4 = 5;
int rightLed1 = 6;
int rightLed2 = 7;
int rightLed3 = 8;
int rightLed4 = 9;

int button = 22;

int knockSensor = 12;
int relay = 13;

bool knockTime = false;

void setup() {
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(18);
  pinMode(relay, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(leftLed1, OUTPUT);
  pinMode(leftLed2, OUTPUT);
  pinMode(leftLed3, OUTPUT);
  pinMode(leftLed4, OUTPUT);
  pinMode(rightLed1, OUTPUT);
  pinMode(rightLed2, OUTPUT);
  pinMode(rightLed3, OUTPUT);
  pinMode(rightLed4, OUTPUT);
}

void loop() {
  digitalWrite(relay, HIGH);
  if(!knockTime) {
    blinkFuction();
  } 
  else {
    if(digitalRead(knockSensor) == 0) {
      digitalWrite(relay, HIGH);
      delay(200);
    }
    knockPattern();
  }
  
  if(digitalRead(button) == 0) {
    knockTime = true;
  }
}

void blickFunction() {
  digitalWrite(leftLed1, HIGH);
  digitalWrite(rightLed1, HIGH);
  Alarm.delay(1500);
  digitalWrite(leftLed1, LOW);
  digitalWrite(rightLed1, LOW);
  digitalWrite(leftLed2, HIGH);
  digitalWrite(rightLed2, HIGH);
  Alarm.delay(1500);
  digitalWrite(leftLed2, LOW);
  digitalWrite(rightLed2, LOW);
  digitalWrite(leftLed3, HIGH);
  digitalWrite(rightLed3, HIGH);
  Alarm.delay(1500);
  digitalWrite(leftLed3, LOW);
  digitalWrite(rightLed3, LOW);
  digitalWrite(leftLed4, HIGH);
  digitalWrite(rightLed4, HIGH);
  Alarm.delay(1500);
  digitalWrite(leftLed4, LOW);
  digitalWrite(rightLed4, LOW);
  digitalWrite(leftLed2, HIGH);
  digitalWrite(rightLed2, HIGH);
  Alarm.delay(1500);
  digitalWrite(leftLed2, LOW);
  digitalWrite(rightLed2, LOW);
  digitalWrite(leftLed4, HIGH);
  digitalWrite(rightLed4, HIGH);
  Alarm.delay(1500);
  digitalWrite(leftLed4, LOW);
  digitalWrite(rightLed4, LOW);
  digitalWrite(leftLed3, HIGH);
  digitalWrite(rightLed3, HIGH);
  Alarm.delay(1500);
  digitalWrite(leftLed3, LOW);
  digitalWrite(rightLed3, LOW);
  digitalWrite(leftLed1, HIGH);
  digitalWrite(rightLed1, HIGH);
  Alarm.delay(1500);
  digitalWrite(leftLed1, LOW);
  digitalWrite(rightLed1, LOW);
}

void knockPattern() {
  digitalWrite(leftLed1, HIGH);
  digitalWrite(leftLed2, HIGH);
  digitalWrite(leftLed3, HIGH);
  digitalWrite(leftLed4, HIGH);
  digitalWrite(rightLed1, HIGH);
  digitalWrite(rightLed2, HIGH);
  digitalWrite(rightLed3, HIGH);
  digitalWrite(rightLed4, HIGH);
}
