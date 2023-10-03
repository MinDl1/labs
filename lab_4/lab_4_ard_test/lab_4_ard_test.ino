#include <WiFi.h>
#include <WebServer.h>
#include "pages.h"
/* Установите здесь свои SSID и пароль */
const char* ssid = "ESP32";
const char* password = "01234567";
/* Настройки IP адреса */
IPAddress local_ip(192,168,2,1);
IPAddress gateway(192,168,2,1);
IPAddress subnet(255,255,255,0);
WebServer server(80);
uint8_t LED1pin = 4;
bool LED1status = LOW;
uint8_t LED2pin = 5;
bool LED2status = LOW;

void setup() {
 Serial.begin(115200);
 pinMode(LED1pin, OUTPUT);
 pinMode(LED2pin, OUTPUT);
 WiFi.softAP(ssid, password);
 WiFi.softAPConfig(local_ip, gateway, subnet);
 delay(100);
 server.on("/", handle_root);
 server.on("/setLED", handle_LED);
 server.on("/readADC", handle_ADC);

 server.onNotFound(handle_NotFound);
 server.begin();
 Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  if(LED1status)
  {digitalWrite(LED1pin, HIGH);}
  else
  {digitalWrite(LED1pin, LOW);}
  if(LED2status)
  {digitalWrite(LED2pin, HIGH);}
  else
  {digitalWrite(LED2pin, LOW);}

  if(Serial.available() > 0){
    int inByte = Serial.read(); //чтение значения с клавиатуры
    //если первый написанный байт равен первому символу
    if(inByte == 'q'){
      digitalWrite(LED1pin, HIGH);
      LED1status = HIGH;
      Serial.println("GOOOO");
    }
  }
}

void handle_root() {
 String s = MAIN_page; // Чтение содержимого HTML
 server.send (200, "text / html", s); // Отправить веб-страницу
}

void handle_ADC () {
 int a = random(10, 30); //analogRead (A0);
 String adcValue = String (a);
 server.send (200, "text/plain", adcValue); // Отправляем значение ADC только клиентскому ajax-запросу
}

void handle_LED () {
 String t_state = server.arg ("LEDstate"); 
 Serial.println (t_state);
 server.send (200, "text/plain", t_state); // Отправить веб-страницу
}

void handle_NotFound(){
 server.send(404, "text/plain", "Not found");
}