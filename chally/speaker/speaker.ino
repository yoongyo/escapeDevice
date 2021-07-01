#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 

int firstRoom = 12;
int lastRoom = 13;
int btn = 5;
boolean wonka = true;

boolean one = true;
boolean two = false;
boolean three = false;

void setup() {
  pinMode(firstRoom, INPUT_PULLUP);
  pinMode(lastRoom, INPUT_PULLUP);
  pinMode(btn, INPUT_PULLUP);

  Serial.begin(9600);
  // mp3 module
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(30);
}

void loop() {
//  boolean play_state = digitalRead(6);// connect Pin3 to BUSY pin of player
//  Serial.println(play_state);
//  if(play_state == HIGH){
//    mp3_next ();
//  }
  boolean play_state = digitalRead(6);
  if (one) {
    Serial.println("첫번째방");
    if(play_state == 0){
      mp3_play(1);
    }
  }
  if (two) {
    Serial.println("두번째방");
    if (wonka) {
      mp3_play(2);
      wonka = false;
    }
    if(play_state == 0) {
      mp3_play(3);
    }
  }
  if (three) {
    Serial.println("세번째방");
    if(play_state == 1) {
      mp3_play(4);
    }
  }
  
  // 버튼 누르면 리셋
  if (digitalRead(btn) == 1) {
    wonka = true;
  }
  // 문이 둘다 닫혀있을 때
  if (digitalRead(firstRoom) == 1 && digitalRead(lastRoom) == 1) {
    one = true;
    two = false;
    three = false;
  }
  // 첫째방 문이 열리고
  else if (digitalRead(firstRoom) == 0 && digitalRead(lastRoom) == 1) {
    one = false;
    two = true;
    three = false;
  }
  // 두번째방 문이 열리고
  else if (digitalRead(firstRoom) == 0 && digitalRead(lastRoom) == 0) {
    one = false;
    two = false;
    three = true;
  }
  Serial.println(digitalRead(firstRoom));
  Serial.println(digitalRead(lastRoom));

}
