#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 

int btn = 13;
int relay = 7;

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
  Serial.begin(9600);
  // mp3 module
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(30);
}

void loop() {
  mp3_set_volume(30);
  Serial.println(digitalRead(btn));
  if (digitalRead(btn) == 0) {
    mp3_play(1);
    delay(19000);
    digitalWrite(relay, HIGH);
    delay(2000);
    digitalWrite(relay, LOW);
  }
}
