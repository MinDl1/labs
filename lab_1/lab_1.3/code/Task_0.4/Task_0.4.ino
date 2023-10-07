#define PUMP_PIN 3
#define WET_PIN A2
int soilMoistureValue = 0;
int percentage = 0;

void setup(){
    pinMode(PUMP_PIN, OUTPUT);
    Serial.begin();
}

void loop(){
    soilMoistureValue = analogRead(WET_PIN);
    percentage = map(soilMoistureValue, 490, 1023, 100, 0);
    Serial.println(percentage);
    if(percentage < 10){
        Serial.println("pump on");
        digitalWrite(PUMP_PIN, LOW);
    }
    if(percentage > 80){
        Serial.println("pump off");
        digitalWrite(PUMP_PIN, HIGH);
    }
}