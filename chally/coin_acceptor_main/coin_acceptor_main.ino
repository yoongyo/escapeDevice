#define chocolate1 10
#define chocolate2 11
#define chocolate3 9
#define btn 12
#define resetBtn 5

#include <LiquidCrystal_I2C.h>  // LCD 라이브러리
#include <Servo.h>              // Servo 라이브러리 

LiquidCrystal_I2C lcd(0x27,16,2); 
Servo servo;

// coin acceptor
const int coinInt = 0; 
int pulses = 0;
boolean insert = false;
volatile long timeLastPulse = 0;
int money;

// chocolate 
boolean first = false;
boolean last = false; 
int chocolatePrice = 850;

// servo 
int initValue = 76;
int safeValue = 7;
int outValue = 145;

void setup() {
  Serial.begin(9600); 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Wonka's Shop");
  lcd.setCursor(0,1);
  lcd.print(money);

  // chocolate
  pinMode(chocolate1, OUTPUT);
  pinMode(chocolate2, OUTPUT);
  pinMode(chocolate3, OUTPUT);

  // servo  7pin
  servo.attach(7);
  servo.write(initValue);

  // coin acceptor
  attachInterrupt(digitalPinToInterrupt(2), coinInserted, RISING);   

  // btn
  pinMode(btn, INPUT_PULLUP);
  pinMode(resetBtn, INPUT_PULLUP);
}

void coinInserted() {
  pulses++;
  timeLastPulse = millis();
  insert = true;
}

void loop() {
  Serial.println(digitalRead(resetBtn));
  if (digitalRead(resetBtn) == 0) {
    first = false;
    last = false;
    digitalWrite(chocolate1, LOW);
    digitalWrite(chocolate2, LOW);
    digitalWrite(chocolate3, LOW);
  }
  if (digitalRead(btn) == 1) {
    if (money == chocolatePrice && first == false) {
      digitalWrite(chocolate1, HIGH);
      first = true;
      money = 0;
      lcd.setCursor(0,1);
      lcd.print(money);
      servo.write(safeValue);
      delay(1000);
      servo.write(initValue);
    }
    else if (money == chocolatePrice && first == true && last == false) {
      digitalWrite(chocolate2, HIGH);
      last = true;
      money = 0;
      lcd.setCursor(0,1);
      lcd.print(money);
      servo.write(safeValue);
      delay(1000);
      servo.write(initValue);
    }
    else if (money == chocolatePrice && last == true) {
      digitalWrite(chocolate3, HIGH);
      money = 0;
      lcd.setCursor(0,1);
      lcd.print(money);
      first = false;
      last = false;
      servo.write(safeValue);
      delay(1000);
      servo.write(initValue);
    }
    else {
      servo.write(outValue);
      delay(1000);
      servo.write(initValue);
    }
    money = 0;
    lcd.init();
    lcd.setCursor(0,0);
    lcd.print("Wonka's Shop");
    lcd.setCursor(0,1);
    lcd.print(money);
  }
  
  long timeFromLastPulse = millis() - timeLastPulse;
  if (pulses > 0 && timeFromLastPulse > 300 && insert) {
    insert = false;
    if (pulses == 1) {
      money = money + 100;
      pulses = 0;
      lcd.setCursor(0,1);
      lcd.print(money);
    }
    else if (pulses == 5) {
      money = money + 500;
      pulses = 0;
      lcd.setCursor(0,1);
      lcd.print(money);
    }
    else if (pulses == 10) {
      money = money + 50;
      pulses = 0;
      lcd.setCursor(0,1);
      lcd.print(money);
    }
    pulses = 0;
  }
}
