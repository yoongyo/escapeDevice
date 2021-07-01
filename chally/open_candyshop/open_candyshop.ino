// red 12시 
// blue 2시 40분   
// green 3시 30분
// yello 6시
// white 9시 

int AredH = A12;     
int AredM = A13;
int AblueH = A11;
int AblueM = A10;
int AgreenH = A9;
int AgreenM = A8;
int AyelloH = A7;
int AyelloM = A6;
int AwhiteH = A4;
int AwhiteM = A5;

int emlock = 10;
int led = 9;
int mainLight = 7;  // main 전구
int btn = 13;

boolean ok = true;

void setup() {
  Serial.begin(9600);
  pinMode(emlock, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(mainLight, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
}

void loop() {
  int redH = analogRead(AredH);   
  int redM = analogRead(AredM);   
  int blueH = analogRead(AblueH); 
  int blueM = analogRead(AblueM);  
  int greenH = analogRead(AgreenH);  
  int greenM = analogRead(AgreenM);  
  int yelloH = analogRead(AyelloH);  
  int yelloM = analogRead(AyelloM);
  int whiteH = analogRead(AwhiteH);
  int whiteM = analogRead(AwhiteM);
  Serial.println((blueM));
  if (digitalRead(btn) == 1) {
    ok = true;
    digitalWrite(emlock, LOW);
    digitalWrite(led, LOW);
    digitalWrite(mainLight, LOW);
  }
  if (ok) {
    if (redH >= 0 && redH < 50){  
      Serial.println("1"); //  12
      if (redM >= 0 && redH < 50) {  
        Serial.println("2");
        if (blueH > 30 && blueH < 330) {                       //  2~3
          Serial.println("3"); //  12

          if (blueM > 770 && blueM < 1024) { 
            Serial.println("4");//  12
//  8
            if (greenH > 210 && greenH < 390) {  
              Serial.println("5");//  12
//  3
              if (greenM > 580 && greenM < 680) { 
              Serial.println("6");//  12
//  6
                if (yelloH > 580 && yelloH < 680) {  
                  Serial.println("7");//  12
//  6
                  if (yelloM >= 0 && yelloM < 50) {  
                    Serial.println("8");  
//  12
                    if (whiteH >900 && whiteH < 1040) {         //  9
                      if (whiteM >= 0 && whiteM < 50)  {                        //  12
                        ok = false;
                        digitalWrite(emlock, HIGH);
                        digitalWrite(led, HIGH);
                        digitalWrite(mainLight, HIGH);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
