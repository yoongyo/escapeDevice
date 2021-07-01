int button11 = 36;
int button12 = 37;
int button13 = 4;
int button14 = 5;
int button15 = 6;
int button16 = 7;
int button17= 8;
int button21 = 22;
int button22 = 23;
int button23 = 28;
int button24 = 29;
int button25 = 42;
int button26 = 43;
int button27 = 52;
int relay = 2;

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(button11, INPUT_PULLUP);
  pinMode(button12, INPUT_PULLUP);
  pinMode(button13, INPUT_PULLUP);
  pinMode(button14, INPUT_PULLUP);
  pinMode(button15, INPUT_PULLUP);
  pinMode(button16, INPUT_PULLUP);
  pinMode(button17, INPUT_PULLUP);
  pinMode(button21, INPUT_PULLUP);
  pinMode(button22, INPUT_PULLUP);
  pinMode(button23, INPUT_PULLUP);
  pinMode(button24, INPUT_PULLUP);
  pinMode(button25, INPUT_PULLUP);
  pinMode(button26, INPUT_PULLUP);
  pinMode(button27, INPUT_PULLUP);
}

void loop() {
  digitalWrite(relay, HIGH);
  if(digitalRead(button11) == HIGH) {
    if(digitalRead(button12) == LOW) {
      if(digitalRead(button13) == HIGH) {
        if(digitalRead(button14) == HIGH) {
          if(digitalRead(button15) == LOW) {
            if(digitalRead(button16) == HIGH) {
              if(digitalRead(button17) == LOW){
                if(digitalRead(button21) == LOW) {
                  if(digitalRead(button22) == HIGH) {
                    if(digitalRead(button23) == LOW) {
                      if(digitalRead(button24) == HIGH) {
                        if(digitalRead(button25) == HIGH) {
                          if(digitalRead(button26) == LOW) {
                            if(digitalRead(button27) == HIGH) {
                              digitalWrite(relay, LOW);
                              delay(200);
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
    }
  }
}
