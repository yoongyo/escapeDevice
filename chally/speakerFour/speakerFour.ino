#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 
// 오른쪽 버튼 누르면 1

int sensor = 6;
int btn = 13;
int state = 0;

void setup() {
  pinMode(sensor, INPUT_PULLUP);
  pinMode(btn, INPUT_PULLUP);
  Serial.begin(9600);
  // mp3 module
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(23);
}

void loop() {
  Serial.println(digitalRead(sensor));
  if (digitalRead(btn) == 1) {
    mp3_stop();
    state = 0;
  }
  if (state == 0) {
    if (digitalRead(sensor) == 0) {
      state = 1;
      mp3_play();
    }
  }
}
