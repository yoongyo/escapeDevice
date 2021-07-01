#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 

int firstRoom = 7;
int first = true;
int btn = 13;
void setup() {
  pinMode(firstRoom, INPUT_PULLUP);
  pinMode(btn, INPUT_PULLUP);
  Serial.begin(9600);
  // mp3 module
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(18);
}

void loop() {
  
  Serial.println(digitalRead(firstRoom));
  if (first) {
    mp3_play();
    if(digitalRead(firstRoom) == 0){
      mp3_stop();
      first = false;
    }
    
  }
  if (digitalRead(btn) == 0){
    first = true;
  }
}
