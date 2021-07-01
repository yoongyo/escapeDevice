#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 

int firstSensor = 2;
int secondSensor = 3;
int btn = 13;
int state = 2;

void setup() {
  pinMode(firstSensor, INPUT);
  pinMode(secondSensor, INPUT);
  Serial.begin(9600);
  // mp3 module
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(30);
}

void loop() {
  Serial.println(digitalRead(secondSensor));
  // 리셋 버튼을 누르면
  if(digitalRead(btn) == 1) {
    mp3_stop();
  }
  if(digitalRead(firstSensor) == 0) {
    delay(55000);
    mp3_play(1);
  }
  if(digitalRead(secondSensor) == 0) {
    mp3_play(2);
  }
}


//  if (digitalRead(btn) == 1) {
//    mp3_stop();
//  }
//  if(digitalRead(firstSensor) == HIGH) {
//    delay(60000);
//    if (state == 2) {
//      mp3_play(2); 
//    }
//    else if (state == 3) {
//      mp3_play(3); 
//    }
//    boolean play_state = digitalRead(4);
//    if (play_state == HIGH){
//      if (state == 2) {
//        state = 3;
//      }
//      else {
//        state = 2;
//      }
//    }
//  }
//  if(digitalRead(secondSensor) == HIGH) {
//    mp3_play(4);
//  }
