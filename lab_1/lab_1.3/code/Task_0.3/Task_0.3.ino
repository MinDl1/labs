#define SENSOR_FLAME_PIN 4
int flame;
void setup()
{
  pinMode(SENSOR_FLAME_PIN, INPUT);
  Serial.begin(9600);
}
void loop() {
  flame = digitalRead(SENSOR_FLAME_PIN);
  if (flame == 1){
    Serial.println("Обнаружено пламя");
    delay(150);
  } 
  else{
    Serial.println("Пламя не обнаружено");
  }
 // delay(500);
}