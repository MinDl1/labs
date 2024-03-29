#include <Wire.h> // Добавляем необходимые библиотеки
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN A0 // к какому пину будет подключен сигнальный выход датчика
// SCL_PIN = A5
// SDA_PIN = A4
#define DHTTYPE DHT11 //выбор используемого датчика DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
//инициализация датчика
DHT dht(DHTPIN, DHTTYPE);
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

void setup()
{
    lcd.init(); // Инициализация lcd
    lcd.backlight(); // Включаем подсветку
    lcd.createChar(1, degree); // Создаем символ под номером 1
    Serial.begin(9600);
    dht.begin();
}
void loop() {
    // Добавляем паузы в несколько секунд между измерениями
    delay(2000);
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit
    float f = dht.readTemperature(true);
    // Выводим показания влажности и температуры
    lcd.setCursor(0, 0); // Устанавливаем курсор в начало 1 строки
    lcd.print("Hum = % "); // Выводим текст
    lcd.setCursor(7, 0); // Устанавливаем курсор на 7 символ
    lcd.print(h, 1); // Выводим на экран значение влажности
    lcd.setCursor(0, 1); // Устанавливаем курсор в начало 2 строки
    lcd.print("Temp = \1C "); // Выводим текст, \1 - значок градуса
    lcd.setCursor(7, 1); // Устанавливаем курсор на 7 символ
    lcd.print(t,1); // Выводим значение температуры
}