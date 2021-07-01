#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 

int dynamite1 = 2; // 집문 왼쪽
int dynamite2 = 3; // 방안 왼쪽 구석탱이
int dynamite3 = 4; // 지하실 입구
int dynamite4 = 5; // 지하실 안쪽
int dynamite5 = 6; // 방안 오른쪽 구석탱이
int dynamite6 = 7; // 집문 오른쪽
//int dynamite7 = 8; // 방안 입구

int button = 9;
int led = 12;
int emLock = 13;
bool finish = false;

void setup() {
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(30);
  Serial.begin(9600);
  
  pinMode(dynamite1, INPUT);
  pinMode(dynamite2, INPUT);
  pinMode(dynamite3, INPUT);
  pinMode(dynamite4, INPUT);
  pinMode(dynamite5, INPUT);
  pinMode(dynamite6, INPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(emLock, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  Serial.println("dm5: " + String(digitalRead(dynamite5)));

  
//  Serial.println("dm1: " + String(digitalRead(dynamite1)));
//  Serial.println("dm2: " + String(digitalRead(dynamite2)));
//  Serial.println("dm3: " + String(digitalRead(dynamite3)));
//  Serial.println("dm4: " + String(digitalRead(dynamite4)));
//  Serial.println("dm5: " + String(digitalRead(dynamite5)));
//  Serial.println("dm6: " + String(digitalRead(dynamite6)));
  digitalWrite(emLock, LOW);
  digitalWrite(led, LOW);
  if(digitalRead(button) == 0) {
    if(digitalRead(dynamite1) == 0){
      if(digitalRead(dynamite2) == 0) {
        if(digitalRead(dynamite3) == 0) {
          if(digitalRead(dynamite4) == 0) {
            if(digitalRead(dynamite5) == 0) {
              if(digitalRead(dynamite6) == 0){
                finish = true;
                mp3_play(3);   // 다이너마이트 터지는 소리
                digitalWrite(led, HIGH);
                delay(5000);
                digitalWrite(emLock, HIGH);
                delay(500);
                delay(20000);
                finish = false;
              }
            }
          }
        }
      }
    }
  }
  if(!finish) {
    if(digitalRead(button) == 0) {
      if(digitalRead(dynamite1) == 0 || digitalRead(dynamite2) == 0 || digitalRead(dynamite3) == 0 || digitalRead(dynamite4) == 0 || digitalRead(dynamite5) == 0 || digitalRead(dynamite6) == 0){
        mp3_play(1);    // 삐-삐익 
        delay(3000);
      }
    }
  }
}
