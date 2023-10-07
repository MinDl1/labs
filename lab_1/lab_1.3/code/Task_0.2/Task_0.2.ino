#include "MQ135.h"
int soilMoistureValueGas = 0;
int percentage=0;
#define ANALOGPIN A1 //подключение аналогового сигнального пина
#define OUT_PIN 5
#define RZERO 206.85
MQ135 gasSensor = MQ135(ANALOGPIN);
bool noGas; //переменная для хранения значения о присутствии газа
int gasValue = 0; //переменная для хранения количества газа
void setup()
{
  pinMode(OUT_PIN,OUTPUT);
  float rzero = gasSensor.getRZero();
  Serial.begin(9600);
}
void loop()
{
  soilMoistureValueGas = analogRead(ANALOGPIN);
  float ppm = gasSensor.getPPM();
  Serial.println(percentage);
  Serial.print("CO2 ppm value : ");
  Serial.println(ppm);
  delay(2000); // 2 секунды задержки
}