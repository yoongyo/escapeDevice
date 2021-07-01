#include<Servo.h> //Servo 라이브러리를 추가
Servo servo;      //Servo 클래스로 servo객체 생성
int value = 0;    // 각도를 조절할 변수 value

void setup() {
  servo.attach(8);     //맴버함수인 attach : 핀 설정
  Serial.begin(9600); //시리얼 모니터 사용 고고
}

void loop() {
  servo.write(20); 
  delay(3000);
  servo.write(89);
  delay(24000);
  servo.write(158);
  delay(3000);
  servo.write(89);
  delay(24000);
}
