#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(10, 11); 

int doorSensor = 2;
int resetBtn = 6;
int door = 12;
int dynamiteBox = 13;
int eyes = 9;
int mageneticSensor = 8;

int steps = 0;

long previousMillis = 0; //이전시간
long delayTime = 100; //0.1초(100) 대기시간
boolean ledState = false; //LED 현재상태

void setup() {
  pinMode(resetBtn, INPUT_PULLUP);
  pinMode(door, OUTPUT);
  pinMode(eyes, OUTPUT);
  pinMode(dynamiteBox, OUTPUT);
  pinMode(mageneticSensor, INPUT);
  pinMode(doorSensor, INPUT_PULLUP);
  
  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(30);

  Serial.begin(9600);
} 

void loop() {
  digitalWrite(door, HIGH);
  digitalWrite(dynamiteBox, HIGH);
  Serial.println(digitalRead(resetBtn));
  // 문 열리면 여자 음성과 함께 다음방 문 열림
  if(steps == 0 && digitalRead(doorSensor) == 0) {
    steps = 1;
    delay(1500);
    mp3_play(1);
    previousMillis = 0;
    ledState = false;
    blinkLED();
    delay(10000);
    digitalWrite(eyes, LOW);
    digitalWrite(door, LOW);
    delay(200);
  }
  // 손에 반지를 올리면 다이너마이트 상자 열리기 
  if(steps == 1 && digitalRead(mageneticSensor) == 0) {
    mp3_play(2); 
    previousMillis = 0;
    ledState = false;
    blinkLED();
    delay(12000);
    digitalWrite(dynamiteBox, LOW);
    digitalWrite(eyes, LOW);
    delay(200);
    
    steps = 2;
  }
  // 문이 닫히고 버튼이 눌리면 리셋되기 
  if(digitalRead(doorSensor) == 1 && digitalRead(resetBtn) == 0) {
    // 리셋 
    mp3_play(3);
    delay(5000);
    digitalWrite(door, LOW);
    delay(200);
    steps = 0;
  }
}

void blinkLED() {
  unsigned long currentMillis = millis(); //현재시간값 가져옴
  if(currentMillis - previousMillis >= 100){ //1000초 시간이 흘렀는지 체크
    previousMillis = currentMillis; //1초가 지나 참임으로 1초 지난 현재시간을 이전시간에 저장
    ledState=!ledState;   //1초 if문이 참이니깐 1초 단위로 ledState 값을 반전시키면 1초 단위로 참/거짓됨.
    digitalWrite(eyes, ledState);   //참(5V) or 거짓(0V) 
  }
}
