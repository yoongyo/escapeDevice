#include <Keypad.h>
#include <Wire.h>    // I2C control 라이브러리
#include <LiquidCrystal_I2C.h> 
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial mySerial(10, 11); 
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

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int count = 0; 
int count2 = 0;   
char len;
char len1;
char len2;
char phoneNum[100] = "";
char count1 = 0; 
char first = true;
char ceo02 = false;
char man04 = false;
char ceoPhone[16] = "02) 35682-4793C";
char manPhone[17] = "04) 51467-568834C";
char phoneName[100] = "";
char star[100] ="";
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  mySerial.begin(9600);
  mp3_set_serial(mySerial);    
  delay(1);                    
  mp3_set_volume(22);
}
 
void loop()
{
  char key = kpd.getKey();
  if (((key >= '0' && key <= '9') || (key == 'C')) && (count1 <16)){
      if (man04 && count2 < 11) {
        if (len2 == 4){
          star[len2+1] = ' ';
          star[len2+2] = '\0';
        }
        if (key >= '0' && key <= '9'){
          count2++;
          len2 = strlen(star);
          star[len2] = '*';
          star[len2+1] = '\0';
          lcd.setCursor(0,1);
          lcd.print(star);
        }
      }
      
      if (ceo02 && count < 11 ) {
        if (len1 == 4){
          phoneName[len1+1] = ' ';
          phoneName[len1+2] = '\0';
        }
        if (key == '1'){
          count++;
          len1 = strlen(phoneName);
          phoneName[len1] = 'A';
          phoneName[len1+1] = '\0';
          lcd.setCursor(0,1);
          lcd.print(phoneName);
        }
        if (key == '2'){
          count++;
          len1 = strlen(phoneName);
          phoneName[len1] = 'Y';
          phoneName[len1+1] = '\0';
          lcd.setCursor(0,1);
          lcd.print(phoneName);
        }
        if (key == '3'){
          count++;
          len1 = strlen(phoneName);
          phoneName[len1] = 'E';
          phoneName[len1+1] = '\0';
          lcd.setCursor(0,1);
          lcd.print(phoneName);
        }
        if (key == '4'){
          count++;
          len1 = strlen(phoneName);
          phoneName[len1] = 'R';
          phoneName[len1+1] = '\0';
          lcd.setCursor(0,1);
          lcd.print(phoneName);
        }
        if (key == '5'){
          count++;
          len1 = strlen(phoneName);
          phoneName[len1] = 'M';
          phoneName[len1+1] = '\0';
          lcd.setCursor(0,1);
          lcd.print(phoneName);
        }
        if (key == '6'){
          count++;
          len1 = strlen(phoneName);
          phoneName[len1] = 'I';
          phoneName[len1+1] = '\0';
          lcd.setCursor(0,1);
          lcd.print(phoneName);
        }
        if (key == '7'){
          count++;
          len1 = strlen(phoneName);
          phoneName[len1] = 'O';
          phoneName[len1+1] = '\0';
          lcd.setCursor(0,1);
          lcd.print(phoneName);
        }
        if (key == '8'){
          count++;
          len1 = strlen(phoneName);
          phoneName[len1] = 'L';
          phoneName[len1+1] = '\0';
          lcd.setCursor(0,1);
          lcd.print(phoneName);
        }
        if (key == '9'){
          count++;
          len1 = strlen(phoneName);
          phoneName[len1] = 'S';
          phoneName[len1+1] = '\0';
          lcd.setCursor(0,1);
          lcd.print(phoneName);
        }
        if (key == '0'){
          count++;
          len1 = strlen(phoneName);
          phoneName[len1] = 'B';
          phoneName[len1+1] = '\0';
          lcd.setCursor(0,1);
          lcd.print(phoneName);
        }
      }
      
      
      count1++;
      len = strlen(phoneNum);
      phoneNum[len] = key;
      phoneNum[len+1] = '\0';
      lcd.setCursor(0,0);
      Serial.println(phoneNum);
      if(phoneNum[0]=='0' && phoneNum[1]=='2' && first){
        first = false;
        phoneNum[len+1] = ')';
        phoneNum[len+2] = ' ';
        phoneNum[len+3] = '\0';
        ceo02 = true;
      }
      if(phoneNum[0]=='0' && phoneNum[1]=='4' && first){
        first = false;
        phoneNum[len+1] = ')';
        phoneNum[len+2] = ' ';
        phoneNum[len+3] = '\0';
        man04 = true;
      }
      if (len == 8 && (ceo02 == true || man04 == true)){
        phoneNum[len+1] = '-';
        phoneNum[len+2] = '\0';
      }
      lcd.print(phoneNum);
      if (key == 'C'){
        int manGood = strcmp(phoneNum, manPhone);
        int ceoGood = strcmp(phoneNum, ceoPhone);
        Serial.println(ceoGood);
        Serial.println(manGood);
        if(manGood == 0){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Calling Manager");
          lcd.setCursor(0,1);
          lcd.print("MARIO MILLER");
          mp3_play(2);

        } else if(ceoGood == 0) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Calling... CEO");
          lcd.setCursor(0,1);
          lcd.print("EMILY ROSE");
          mp3_play(1);
        }  
        else {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Not Number");
          phoneNum[0] = '\0';
          count1 = 0;
          first = true;
          ceo02 = false;
          man04 = false;
        }
      }
  }
  if (key == '*' || key == '#'){
    lcd.clear();
    phoneName[0] = '\0';
    count = 0;
    phoneNum[0] = '\0';
    count1 = 0;
    star[0] = '\0';
    count2 = 0;
    first = true;
    ceo02 = false;
    man04 = false;
  }
}
