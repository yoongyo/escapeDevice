#include <Keypad.h>
#include <Wire.h>    // I2C control 라이브러리
#include <LiquidCrystal_I2C.h> 

int liftUp = 12;   // no  -> 비밀번호 맞으면 HIGH
int relay = 13;    // nc  -> 비밀번호 맞으면 LOW
int liftDown = 11;  // no  -> 474747 맞으면 HIGH
int doorSensor = 10; // 


LiquidCrystal_I2C lcd(0x27,16,2); 

const byte ROWS = 4; 
const byte COLS = 4;
 
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'#','0','*', 'D'}
};
 
byte rowPins[ROWS] = {6, 7, 8, 9};
byte colPins[COLS] = {2, 3, 4, 5};

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char password[8] = "369524";
char passwordInput[8] = "";
char len;
char* print1 = "Password:";
int position = 0;
int wrong = 0;
int count = 0;

void setup() {
  pinMode(liftUp, OUTPUT);  
  pinMode(relay, OUTPUT);
  pinMode(liftDown, OUTPUT);
  pinMode(doorSensor, INPUT_PULLUP);

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print(print1);
}

void loop() {
  Serial.println(digitalRead(doorSensor));
  digitalWrite(relay, HIGH);
  digitalWrite(liftUp, HIGH);
  digitalWrite(liftDown, LOW);
  
  char key = kpd.getKey();
  if(key) {
    count++;
    len = strlen(passwordInput);
    passwordInput[len] = key;
    passwordInput[len+1] = '\0';
    Serial.println(passwordInput);
    lcd.setCursor(10,0);
    lcd.print(passwordInput);
    if(count == 6){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(print1);
      if(strcmp("474747", passwordInput) == 0) {
        digitalWrite(liftDown, HIGH);
        delay(15000);
        digitalWrite(liftDown, LOW);
        delay(500);
      }
      // 비밀번호 맞으면
      if(strcmp(password, passwordInput) == 0){
        if(digitalRead(doorSensor) == 0){
          lcd.setCursor(0,1);
          lcd.print("Correct Password");
          delay(1500);
          digitalWrite(liftUp, LOW);
          delay(8000);
          digitalWrite(liftUp, HIGH);
          digitalWrite(relay, LOW);
          delay(20000);
        } else {
          lcd.setCursor(0,1);
          lcd.print("Close Door");
          delay(3000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(print1);
        }
      } else {
        lcd.setCursor(0,1);
        lcd.print("Wrong Password");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(print1);  
      }  
      // 474747 다운
      
      count = 0;
      passwordInput[0] = '\0';
      
    }
    if(key == '*' || key == '#'){ // *, # 버튼을 눌렀을 경우
      count = 0;
      passwordInput[0] = '\0';
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(print1);
    } 
  }
}
