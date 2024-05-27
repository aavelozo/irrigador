int pinSensor = A0;
int pinWater = 13;
bool waterActivated = false;
int currentSensorValue = 0;
int currentMappedValue = 0;
const int LIMIT_MOISTURE = 15;

void setup() {
  Serial.begin(9600);
  pinMode(pinWater,OUTPUT);
  digitalWrite(pinWater,LOW);
}

void loop() {
  handleWaterActive(checkMoistureLimit());
  delay(1000);
}

/**
* check current moisture return true if limit moisture is less than current value
*/
bool checkMoistureLimit() {
  currentSensorValue = 1023 - analogRead(pinSensor);
  currentMappedValue = map(currentSensorValue,0,1023,0,100);
  Serial.print("currentSensorValue: ");Serial.print(currentSensorValue);Serial.print(",");Serial.println(currentMappedValue);
  return currentMappedValue < LIMIT_MOISTURE;
}

void handleWaterActive(bool active){
  if (active && !waterActivated) {     
    Serial.println("activating water...");
    digitalWrite(pinWater,HIGH);
    waterActivated = true;
    Serial.println("  activated");
  } else if (!active && waterActivated) {
    Serial.println("deactivating water...");
    digitalWrite(pinWater,LOW);
    waterActivated = false;
    Serial.println("  deactivated");
  }
}