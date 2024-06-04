/*
  Sketh to control Water flux according read value from moistore sensor


*/


/*************** PINS DECLARATIONS ***************/
int pinSensor = A0;
int pinWaterController = 13;


/************ COMOM VARIABLES / CONSTANTS ********/
bool waterActivated = false;
int currentSensorValue = 0;
int currentMappedValue = 0;
const int LIMIT_UMIDITY = 55;

/*
  https://www.biomaker.org/block-catalogue/2021/12/17/soil-moisture-sensor-aideepen-v12
  [...]
  The range will be divided into three sections: dry, wet, water. Their related values are:
  Dry: (520 430]
  Wet: (430 350]
  Water: (350 260]
  [...]
*/
const int MIN_SENSOR_CAPACITY = 0;
const int MAX_SENSOR_CAPACITY = 1023;




void setup() {
  Serial.begin(9600);
  pinMode(pinSensor,INPUT);
  pinMode(pinWaterController,OUTPUT);
  digitalWrite(pinWaterController,LOW);
}

void loop() {
  handleWaterActive(checkNeedWater());
  delay(1000);
}

/**
* check current moisture return true if limit moisture is less than current value
*/
bool checkNeedWater() {
  bool result = false;
  currentSensorValue = analogRead(pinSensor);
  currentMappedValue = map(currentSensorValue,MAX_SENSOR_CAPACITY,MIN_SENSOR_CAPACITY,0,100);
  result = currentMappedValue < LIMIT_UMIDITY;
  Serial.print("currentSensorValue: ");Serial.print(currentSensorValue);Serial.print(" | ");Serial.print(currentMappedValue);Serial.print("%");
  if (result) {
    Serial.println("  water most are activated");
  } else {
    Serial.println("  water most are deactivated");
  }
  return result;
}


void handleWaterActive(bool active){
  if (active && !waterActivated) {     
    Serial.println("activating water...");
    digitalWrite(pinWaterController,HIGH);
    waterActivated = true;
  } else if (!active && waterActivated) {
    Serial.println("deactivating water...");
    digitalWrite(pinWaterController,LOW);
    waterActivated = false;
  }  
}