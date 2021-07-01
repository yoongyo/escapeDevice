int knock = 13;
int relay = 12;

void setup() {
  pinMode(knock, INPUT);
  pinMode(relay, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int data = digitalRead(knock);
  if(data == LOW){
    Serial.println("FUCK");
    delay(200);
    digitalWrite(relay, HIGH);
  }
}
