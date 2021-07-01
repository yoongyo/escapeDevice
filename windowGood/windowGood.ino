int redLed = 4;

int blinckDelay = 200;

void setup() {
  pinMode(redLed, OUTPUT);
}

// 750 375 375 750 


void loop() {
  digitalWrite(redLed, HIGH);
  blinck();
  digitalWrite(redLed, LOW);
  delay(750-blinckDelay);
  digitalWrite(redLed, HIGH);
  blinck();
  digitalWrite(redLed, LOW);
  delay(375-blinckDelay);
  digitalWrite(redLed, HIGH);
  blinck();
  digitalWrite(redLed, LOW);
  delay(375-blinckDelay);
  digitalWrite(redLed, HIGH);
  blinck();
  digitalWrite(redLed, LOW);
  delay(750-blinckDelay);
  digitalWrite(redLed, HIGH);
  blinck();
  digitalWrite(redLed, LOW);
  delay(5000);
}

void blinck() {
  delay(blinckDelay);
}
