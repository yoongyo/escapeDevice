#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 

void setup() {
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(18);
}

void loop() {
  mp3_play();
}
