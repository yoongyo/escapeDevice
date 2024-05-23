#include <Time.h>
#include <TimeAlarms.h>

// W = 2
// n = 3
// k = 4
// a = 5
// o = 6

// kanow

// nkwoa -> konaw
int Nlight = 3;
int Klight = 4;
int Olight = 5;
int Alight = 6;
int Wlight = 2;

int window = 13;
int pipeStart = 12;
int btn = 11;  // 리셋 버튼
int pipeEnd = 10;
int pump = 9;

int pipeFirst = false;
int pumpFirst = false;

void setup() {
  Serial.begin(9600);
  pinMode(Klight, OUTPUT);
  pinMode(Olight, OUTPUT);
  pinMode(Nlight, OUTPUT);
  pinMode(Alight, OUTPUT);
  pinMode(Wlight, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(pipeStart, INPUT_PULLUP);
  pinMode(pipeEnd, INPUT_PULLUP);
  pinMode(window, INPUT_PULLUP);
  pinMode(btn, INPUT_PULLUP);
}

void loop() {
  unsigned long currentMillis = millis();
  digitalWrite(Klight, HIGH);
  digitalWrite(Olight, HIGH);
  digitalWrite(Nlight, HIGH);
  digitalWrite(Alight, HIGH);
  digitalWrite(Wlight, HIGH);
  if (digitalRead(pipeStart) == 1) {
    pipeFirst = true;
  }
  if (digitalRead(window) == 0) {
    pumpFirst = true;
  }
  if (digitalRead(pipeEnd) == 1) {
    digitalWrite(Klight, HIGH);
    digitalWrite(Olight, HIGH);
    digitalWrite(Nlight, HIGH);
    digitalWrite(Alight, HIGH);
    digitalWrite(Wlight, HIGH);
    pipeFirst = false;
  }
  // 모두 닫은 상태에서 불이 모두 꺼지고 리셋 버튼 누르는것을 확인하고 문제 없으면 OK
  // 닫기 전에 리셋 누르면 delay 때문에 묻힘 
  if (pipeFirst) {
    digitalWrite(Klight, LOW);
    Alarm.delay(1500);
    digitalWrite(Olight, LOW);
    digitalWrite(Klight, HIGH);
    Alarm.delay(1500);
    digitalWrite(Nlight, LOW);
    digitalWrite(Olight, HIGH);
    Alarm.delay(1500);
    digitalWrite(Alight, LOW);
    digitalWrite(Nlight, HIGH);
    Alarm.delay(1500);
    digitalWrite(Wlight, LOW);
    digitalWrite(Alight, HIGH);
    Alarm.delay(1500);
    digitalWrite(Wlight, HIGH);
    Alarm.delay(3000);
  }
  if (digitalRead(btn) == 0) {
    pumpFirst = false;
    pipeFirst = false;
    digitalWrite(pump, LOW);
    digitalWrite(Klight, HIGH);
    digitalWrite(Olight, HIGH);
    digitalWrite(Nlight, HIGH);
    digitalWrite(Alight, HIGH);
    digitalWrite(Wlight, HIGH);
  }
  if (pumpFirst) {
    digitalWrite(pump, LOW);
  } else {
    digitalWrite(pump, HIGH);
  }
}
