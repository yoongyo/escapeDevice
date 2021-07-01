int knockSensor = A0;
int door = 10;

bool openDoor = false;

const int threshold = 800; 

// 노크 값들
const int rejectValue = 25;
const int averageRejectValue = 15;
const int knockFadeTime = 100;
const int maximumKnocks = 20;
const int knockComplete = 1200;
int secretCode[maximumKnocks] = {100, 50, 50, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  
int knockReadings[maximumKnocks];   
int knockSensorValue = 0;           
int programButtonPressed = false; 

void setup() {
  Serial.begin(9600);
  pinMode(door, OUTPUT);
  pinMode(knockSensor, INPUT);
}

void loop() {
  if(openDoor) {
    digitalWrite(door, HIGH);
  } else {
    digitalWrite(door, LOW);
  }
  knockDetect();
}

void knockDetect() {
  knockSensorValue = analogRead(knockSensor);
  if (knockSensorValue >= threshold){
    listenToSecretKnock();
  }
}

void listenToSecretKnock(){
  Serial.println("knock starting");   
  int i = 0;
  for (i=0;i<maximumKnocks;i++){
    knockReadings[i]=0;
  }
 
  int currentKnockNumber=0;               
  int startTime=millis();                 
  int now=millis();
  
  delay(knockFadeTime);                               
  do {
    knockSensorValue = analogRead(knockSensor);
    if (knockSensorValue >= threshold){                   
      Serial.println("knock.");
      now=millis();
      knockReadings[currentKnockNumber] = now-startTime;
      Serial.println(knockReadings[currentKnockNumber]);
      currentKnockNumber ++;                             
      startTime=now;          
      delay(knockFadeTime);                             
    }
    now=millis();
  } while ((now-startTime < knockComplete) && (currentKnockNumber < maximumKnocks));  
  if (validateKnock() == true){
    triggerDoorUnlock(); 
  } else {
    Serial.println("Secret knock failed.");
  }
}

void triggerDoorUnlock(){
  Serial.println("Door unlocked!");
  int i=0;
  openDoor = !openDoor;
}

boolean validateKnock() {
  int i=0;
 
  int currentKnockCount = 0;
  int secretKnockCount = 0;
  int maxKnockInterval = 0;              
  
  for (i=0;i<maximumKnocks;i++){
    if (knockReadings[i] > 0){
      currentKnockCount++;
    }
    if (secretCode[i] > 0){           
      secretKnockCount++;
    }
    
    if (knockReadings[i] > maxKnockInterval){   
      maxKnockInterval = knockReadings[i];
    }
  }
  
  if (programButtonPressed==true) {
    for (i=0;i<maximumKnocks;i++) { 
      secretCode[i]= map(knockReadings[i],0, maxKnockInterval, 0, 100); 
    }
    delay(1000);
    delay(50);
    for (i = 0; i < maximumKnocks ; i++){
      if (secretCode[i] > 0){                                   
        delay(map(secretCode[i],0, 100, 0, maxKnockInterval)); 
      }
      delay(50);
    }
  return false;   
  }
  
  if (currentKnockCount != secretKnockCount){
    return false; 
  }
  
  int totaltimeDifferences=0;
  int timeDiff=0;
  for (i=0;i<maximumKnocks;i++){ // Normalize the times
    knockReadings[i]= map(knockReadings[i],0, maxKnockInterval, 0, 100);      
    timeDiff = abs(knockReadings[i]-secretCode[i]);
    if (timeDiff > rejectValue){ // Individual value too far out of whack
      return false;
    }
    totaltimeDifferences += timeDiff;
  }
  if (totaltimeDifferences/secretKnockCount>averageRejectValue){
    return false; 
  }
  return true;
}
