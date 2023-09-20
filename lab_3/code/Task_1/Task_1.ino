#include <Wire.h> // Добавляем необходимые библиотеки
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include "MQ135.h"

// For LCD DISPLAY
// SCL_PIN = A5
// SDA_PIN = A4
byte degree[8] = // кодируем символ градуса
{
    B00111,
    B00101,
    B00111,
    B00000,
    B00000,
    B00000,
    B00000,
};
LiquidCrystal_I2C lcd(0x27,16,2); // Задаем адрес и размерность дисплея

// Temp and Wet
#define DHTPIN A0 // к какому пину будет подключен сигнальный выход датчика
#define DHTTYPE DHT11 //выбор используемого датчика DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
//инициализация датчика
DHT dht(DHTPIN, DHTTYPE);
int t_w_numTones = 10;
// Ноты C, C#, D, D#, E, F, F#, G, G#, A
int t_w_tones[10] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
#define DIOD_T_W 3

//gas
int gas_numTones = 10;
// Ноты C, C#, D, D#, E, F, F#, G, G#, A
int gas_tones[10] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
#define DIOD_GAS 3
#define ANALOGPIN A1 //подключение аналогового сигнального пина
MQ135 gasSensor = MQ135(ANALOGPIN);

//flame
int flame_numTones = 10;
// Ноты C, C#, D, D#, E, F, F#, G, G#, A
int flame_tones[10] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
#define SENSOR_FLAME_PIN 4
#define DIOD_FLAME 3
int flame = 0;

//pump
int pump_numTones = 10;
// Ноты C, C#, D, D#, E, F, F#, G, G#, A
int pump_tones[10] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
#define PUMP_PIN 2
#define WET_PIN A2
#define DIOD_PUMP 1
int soilMoistureValue = 0;
int percentage = 0;

#define SOUND_PIN 6

void setup()
{
    lcd.init(); // Инициализация lcd
    lcd.backlight(); // Включаем подсветку
    lcd.createChar(1, degree); // Создаем символ под номером 1



    pinMode(SENSOR_FLAME_PIN, INPUT);
    pinMode(DIOD_FLAME, OUTPUT);

    pinMode(PUMP_PIN, OUTPUT);
    pinMode(DIOD_WET, OUTPUT);

    pinMode(SOUND_PIN, OUTPUT);

    Serial.begin(9600);
    dht.begin();
}
void loop() {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit
    float f = dht.readTemperature(true);
    if(h > 10 && t > 30){
        // Выводим показания влажности и температуры
        lcd.setCursor(0, 0); // Устанавливаем курсор в начало 1 строки
        lcd.print("Hum =  %"); // Выводим текст
        lcd.setCursor(7, 0); // Устанавливаем курсор на 7 символ
        lcd.print(h, 1); // Выводим на экран значение влажности
        lcd.setCursor(0, 1); // Устанавливаем курсор в начало 2 строки
        lcd.print("Temp = \1C "); // Выводим текст, \1 - значок градуса
        lcd.setCursor(7, 1); // Устанавливаем курсор на 7 символ
        lcd.print(t,1); // Выводим значение температуры
        digitalWrite(DIOD_T_W, HIGH);
        for (int i = 0; i < t_w_numTones; i++) {
            tone(SOUND_PIN, t_w_tones[i]);
            delay(500);
        }
        noTone(SOUND_PIN);
    }
    else{
        // Выводим показания влажности и температуры
        lcd.setCursor(0, 0); // Устанавливаем курсор в начало 1 строки
        lcd.print("Hum = % "); // Выводим текст
        lcd.setCursor(7, 0); // Устанавливаем курсор на 7 символ
        lcd.print(h, 1); // Выводим на экран значение влажности
        lcd.setCursor(0, 1); // Устанавливаем курсор в начало 2 строки
        lcd.print("Temp = \1C "); // Выводим текст, \1 - значок градуса
        lcd.setCursor(7, 1); // Устанавливаем курсор на 7 символ
        lcd.print(t,1); // Выводим значение температуры
        digitalWrite(DIOD_T_W, LOW);
    }

    float ppm = gasSensor.getPPM();
    float rzero = gasSensor.getRZero();
    if(ppm > 20){
        lcd.setCursor(0, 0);
        lcd.print("ppm : % ");
        lcd.print(ppm);
        lcd.setCursor(7, 0);
        lcd.print(" > 20");
        digitalWrite(DIOD_GAS, HIGH);
        for (int i = 0; i < gas_numTones; i++) {
            tone(SOUND_PIN, gas_tones[i]);
            delay(500);
        }
        noTone(SOUND_PIN);
    }
    else{
        lcd.setCursor(0, 0);
        lcd.print("ppm : % ");
        lcd.print(ppm);
        lcd.setCursor(7, 0);
        lcd.print(" < 20");
        digitalWrite(DIOD_GAS, LOW);
    }

    flame = digitalRead(SENSOR_FLAME_PIN);
    if (flame == 1){
        lcd.setCursor(0, 0);
        lcd.print("Есть Пламя");
        digitalWrite(DIOD_FLAME, HIGH);
        for (int i = 0; i < flame_numTones; i++) {
            tone(SOUND_PIN, flame_tones[i]);
            delay(500);
        }
        noTone(SOUND_PIN);
    } 
    else{
        lcd.setCursor(0, 0);
        lcd.print("Нет Пламя");
        digitalWrite(DIOD_FLAME, LOW);
    }

    soilMoistureValue = analogRead(WET_PIN);
    percentage = map(soilMoistureValue, 490, 1023, 100, 0);
    Serial.println(percentage);
    if(percentage < 10 || h < 10){
        lcd.setCursor(0, 0);
        lcd.print("Pump on");
        digitalWrite(PUMP_PIN, LOW);
        digitalWrite(DIOD_PUMP, HIGH);
        for (int i = 0; i < pump_numTones; i++) {
            tone(SOUND_PIN, pump_tones[i]);
            delay(500);
        }
        noTone(SOUND_PIN);
    }
    if(percentage > 80 || h > 10){
        lcd.setCursor(0, 0);
        lcd.print("Pump off");
        digitalWrite(PUMP_PIN, HIGH);
        digitalWrite(DIOD_PUMP, LOW);
    }
    
    delay(1000);
}