#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 

// 왼쪽 버튼 누르면 1
// 첫방 문 열으면 0
// 두번째 문 열으면 0
int firstSensor = 9;
int secondSensor = 3;
int btn = 13;
int state = 0;

boolean delayState = true;
boolean delayState2 = true;

void setup() {
  pinMode(firstSensor, INPUT_PULLUP);
  pinMode(secondSensor, INPUT_PULLUP);
  pinMode(btn, INPUT_PULLUP);
  Serial.begin(9600);
  // mp3 module
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(24);
}

void loop() {
  boolean play_state = digitalRead(4);
  // 왼쪽 리셋 버튼을 누르면
  Serial.println(digitalRead(secondSensor));
  if(digitalRead(btn) == 1) {
    state = 0;
    mp3_stop();
    delayState = true;
    delayState2 = true;
  }
  // 문이 열릴때 0
  if (digitalRead(firstSensor) == 0) {
    state = 2;
  }
  // 문 열렸을 때 0
  if (digitalRead(secondSensor) == 0) {
    state = 3;
  }
  if (state == 2) {
    if (delayState) {
      delay(65000);
      delayState = false;
    }
    if (play_state == 1) {
      mp3_play(1);
    }
  }
  if (state == 3) {
    if (delayState2) {
      mp3_stop();
      delayState2 = false;
    }
    if (play_state == 1) {
      mp3_play(2);
    }
  }
}
