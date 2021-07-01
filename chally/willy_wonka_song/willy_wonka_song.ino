#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(11, 10); 


int firstRoom = 13;
int start = false;
int btn = 4;

void setup() {
  Serial.begin(9600);
  pinMode(firstRoom, INPUT_PULLUP);
  pinMode(btn, INPUT_PULLUP);
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(30);
}

void loop() {
  if (digitalRead(btn) == 0) {
    start = false; 
  }
  Serial.println(digitalRead(firstRoom));
  if(!start) {
    if(digitalRead(firstRoom) == 0) {
      mp3_play(2);
      start = true;
    }
  }
}
