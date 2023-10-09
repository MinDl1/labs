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
int t_w_numTones = 10;
// Ноты 
int t_w_tones[10] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
DHT dht(DHTPIN, DHTTYPE);

//gas
int gas_numTones = 10;
// Ноты 
int gas_tones[10] = {400, 400, 400, 400, 400, 400, 400, 400, 400, 400};
#define ANALOGPIN A1 //подключение аналогового сигнального пина

//flame
int flame_numTones = 10;
// Ноты 
int flame_tones[10] = {300, 300, 300, 300, 300, 300, 300, 300, 300, 300};
#define SENSOR_FLAME_PIN 4
int flame = 0;

//pump
int pump_numTones = 10;
// Ноты 
int pump_tones[10] = {200, 200, 200, 200, 200, 200, 200, 200, 200, 200};
#define PUMP_PIN 2
#define WET_PIN A2
int soilMoistureValue = 0;
int percentage = 0;

#define LED_DIOD 12
#define LED_DIOD1 8
#define LED_DIOD2 9
#define LED_DIOD3 10
#define SOUND_PIN 6

void setup()
{
    lcd.init(); // Инициализация lcd
    lcd.backlight(); // Включаем подсветку
    lcd.createChar(1, degree); // Создаем символ под номером 1

    //Устанавливаем пины вход или выход
    pinMode(SENSOR_FLAME_PIN, INPUT);

    pinMode(PUMP_PIN, OUTPUT);
    pinMode(WET_PIN, INPUT);

    pinMode(LED_DIOD, OUTPUT);
    pinMode(LED_DIOD1, OUTPUT);
    pinMode(LED_DIOD2, OUTPUT);
    pinMode(LED_DIOD3, OUTPUT);
    pinMode(SOUND_PIN, OUTPUT);

    Serial1.begin(115200);
}
void loop() {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    dht.begin();
    float h = dht.readHumidity();
    // Read temperature as Celsius
    float t = dht.readTemperature();
    delay(3000); //Задержка для считывания

    //Отчищаем дисплей
    lcd.clear();
    // Условие если влажность и температура больше 30
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
        for (int i = 0; i < t_w_numTones; i++) { // цикл, чтобы звучала мелодия из нот и мигало в тот-же такт задержки
            tone(SOUND_PIN, t_w_tones[i]);
            digitalWrite(LED_DIOD1, HIGH);
            delay(800);
        }
        noTone(SOUND_PIN); //выключаем звук нот
    }
    else{
        // Выводим показания влажности и температуры
        lcd.setCursor(0, 0); // Устанавливаем курсор в начало 1 строки
        lcd.print("Hum = %  "); // Выводим текст
        lcd.setCursor(7, 0); // Устанавливаем курсор на 7 символ
        lcd.print(h, 1); // Выводим на экран значение влажности
        lcd.setCursor(0, 1); // Устанавливаем курсор в начало 2 строки
        lcd.print("Temp = \1C  "); // Выводим текст, \1 - значок градуса
        lcd.setCursor(7, 1); // Устанавливаем курсор на 7 символ
        lcd.print(t,1); // Выводим значение температуры
        digitalWrite(LED_DIOD1, LOW); //выключаем светодиод
    }

    //Инициализируем переменую датчика MQ135
    MQ135 gasSensor = MQ135(ANALOGPIN);
    // Считываем данные PPM(количества углекислого газа)
    float ppm = gasSensor.getPPM();
    // олучите сопротивление RZero датчика для целей калибровки
    float rzero = gasSensor.getRZero();
    delay(2000);
    lcd.clear();

    // Если ppm больше 35
    if(ppm > 35){
        lcd.setCursor(0, 0);
        lcd.print("ppm> : % ");
        lcd.print(ppm);
        for (int i = 0; i < gas_numTones; i++) {
            tone(SOUND_PIN, gas_tones[i]);
            digitalWrite(LED_DIOD2, HIGH);
            delay(400);
        }
        noTone(SOUND_PIN);
    }
    else{
        lcd.setCursor(0, 0);
        lcd.print("ppm< : %  ");
        lcd.print(ppm);
        digitalWrite(LED_DIOD2, LOW);
    }

    lcd.clear();
    //Считываем есть ли пламя
    flame = digitalRead(SENSOR_FLAME_PIN);
    delay(2000);
    if (flame == 1){
        lcd.setCursor(0, 0);
        lcd.print("Fire");
        for (int i = 0; i < flame_numTones; i++) {
            tone(SOUND_PIN, flame_tones[i]);
            digitalWrite(LED_DIOD3, HIGH);
            delay(200);
        }
        noTone(SOUND_PIN);
    } 
    else{
        lcd.setCursor(0, 0);
        lcd.print("No fire");
        digitalWrite(LED_DIOD3, LOW);
    }

    // Считываем Влажность почвы
    soilMoistureValue = analogRead(WET_PIN);
    percentage = map(soilMoistureValue, 490, 1023, 100, 0);
    delay(2000);
    lcd.clear();

    int int_pump = 0;
    //Если процент влажности почвы меньше 10 или влажность воздуха меньше 35 то включается насос и мигает светодиод и музыка играет
    if(percentage < 10 || h < 35){
        int_pump = 1;
        lcd.setCursor(0, 0);
        lcd.print("Pump on % ");
        lcd.print(percentage);
        digitalWrite(PUMP_PIN, HIGH);
        for (int i = 0; i < pump_numTones; i++) {
            tone(SOUND_PIN, pump_tones[i]);
            digitalWrite(LED_DIOD, HIGH);
            delay(100);
        }
        noTone(SOUND_PIN);
    }
    if(percentage > 80 && h > 35){
        int_pump = 0;
        lcd.setCursor(0, 0);
        lcd.print("Pump off % ");
        lcd.print(percentage);
        digitalWrite(PUMP_PIN, LOW);
        digitalWrite(LED_DIOD, LOW);
    }
    //String res = String(t)+','+String(h)+','+String(ppm)+','+String(flame)+','+String(int_pump)+','+String(percentage);
    String res = String(random(100))+','+String(random(100))+','+String(random(100))+','+String(random(100))+','+String(random(100))+','+String(random(100));
    Serial.write(res);
}