#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 

int magnetic1 = 2;
int magnetic2 = 3;
int magnetic3 = 4;
int magnetic4 = 5;
int magnetic5 = 6;
int magnetic6 = 7;

int relay = 13;

int post = 9;

bool finish = false;

void setup() {
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(26);
  
  pinMode(magnetic1, INPUT);
  pinMode(magnetic2, INPUT);
  pinMode(magnetic3, INPUT);
  pinMode(magnetic4, INPUT);
  pinMode(magnetic5, INPUT);
  pinMode(magnetic6, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(post, OUTPUT);
}

void loop() {
  digitalWrite(relay, LOW);
  digitalWrite(post, HIGH);
  if (digitalRead(magnetic1) == 0 && digitalRead(magnetic2) == 0 && digitalRead(magnetic3) == 0 && digitalRead(magnetic4) == 0 && digitalRead(magnetic5) == 0 && digitalRead(magnetic6) == 0) {
    digitalWrite(relay, HIGH);
    delay(200);
    if(!finish) {
      delay(10000);
      mp3_play(1);
      delay(5000);
      digitalWrite(post, LOW);
      delay(1000);
      finish = true;
    }
  }
  if (digitalRead(magnetic1) == 1 && digitalRead(magnetic2) == 1 && digitalRead(magnetic3) == 1 && digitalRead(magnetic4) == 1 && digitalRead(magnetic5) == 1 && digitalRead(magnetic6) == 1) {
    finish = false;
  }
}
