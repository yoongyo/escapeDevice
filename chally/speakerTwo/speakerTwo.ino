#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 

// 첫방 열으면 0
// 두번째 방 아직안됨
// 오른쪽 버튼 누르면 0

int secondSensor = 9;
int firstSensor = 13;
int btn = 7;
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
  Serial.println(state);
  boolean play_state = digitalRead(3);  // connect Pin3 to BUSY pin of player
  
  // 리셋 버튼을 누르면
  if(digitalRead(btn) == 0) {
    state = 0;
    mp3_stop();
    delayState = true;
    delayState2 = true;
  }
  if (digitalRead(firstSensor) == 0) {
    state = 2;
  }

  if (digitalRead(secondSensor) == 0) {
    state = 3;
  }
  
  if (state == 2) {
    if (delayState) {
      delay(65000);
      delayState = false;
    }
    if (play_state == 1) {
      Serial.println("ft");
      mp3_play();
    }
  }
  if (state == 3) {
    if (delayState2) {
      mp3_stop();
      delayState2 = false;
    }
  }
}
