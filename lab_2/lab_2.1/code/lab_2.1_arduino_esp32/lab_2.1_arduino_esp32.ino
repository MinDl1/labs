// ВАЖНЫЕ библиотеки
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

int count_args = 6;
String res_in = "0,0,0,0,0,0";
int time_ = 0;

// Функция setup(опередления различных начальных настроек)
void setup() {
 Serial.begin(115200);
 // настройки вайфая
 WiFi.softAP(ssid, password);
 WiFi.softAPConfig(local_ip, gateway, subnet);
 delay(100);

 //Для страниц
 server.on("/", handle_root);
 server.on("/Auth", handle_auth);
 server.on("/getDHT11", handle_DHT11);
 server.on("/getMQ135", handle_MQ135);
 server.on("/getFlame_sensor", handle_Flame_sensor);
 server.on("/getPump_Wet", handle_Pump_Wet);

 //для датчиков
 server.on("/getData", get_data);

 // если страница не найдена
 server.onNotFound(handle_NotFound);

 //Для куки чтобы отслеживать их и выдовать
 const char * headerkeys[] = {"User-Agent", "Cookie"} ;
 size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
 //ask server to track these headers
 server.collectHeaders(headerkeys, headerkeyssize);
 //страт сервера
 server.begin();
}

// повторяющаяся функция в которой мы читаем данные с Arduino UNO R3 и таймера и ждет кдиентов к серверу
void loop() {
  server.handleClient();

  if(Serial.available()){
    res_in = Serial.readString();
    res_in.trim();
  }
  time_ = millis();
  delay(2);
}

// для аутентификации по куки
bool is_authentified() {
  if (server.hasHeader("Cookie")) {
    String cookie = server.header("Cookie");
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      return true;
    }
  }
  return false;
}

// для аутентификации
void handle_auth(){
  if (is_authentified()) {
    server.sendHeader("Location", "/");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  // получить имя параметра и значение Сравниваем
  if (server.hasArg("login") && server.hasArg("passwd")) {
    if(server.arg("login") == "esp32" && server.arg("passwd") == "01234567"){
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", "ESPSESSIONID=1");
      server.sendHeader("Location", "/");
      server.sendHeader("Cache-Control", "no-cache");
      server.send(301);
      return;
    }
  }
  server.send (200, "text/html", Auth_page); // Отправить веб-страницу
}

// для главного роута
void handle_root(){
  if (!is_authentified()) {
    server.sendHeader("Location", "/Auth");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  server.send (200, "text/html", MAIN_page); // Отправить веб-страницу
}

// для датчика dht11 страница
void handle_DHT11(){
  if (!is_authentified()) {
    server.sendHeader("Location", "/Auth");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  server.send (200, "text/html", DHT11_page); // Отправить веб-страницу
}

// для датчика mq135 страница
void handle_MQ135(){
  if (!is_authentified()) {
    server.sendHeader("Location", "/Auth");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  server.send (200, "text/html", MQ135_page); // Отправить веб-страницу
}

// для датчики flame_sensor страница
void handle_Flame_sensor(){
  if (!is_authentified()) {
    server.sendHeader("Location", "/Auth");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  server.send (200, "text/html", Flame_sensor_page); // Отправить веб-страницу
}

// для датчики pump_wet страница
void handle_Pump_Wet(){
  if (!is_authentified()) {
    server.sendHeader("Location", "/Auth");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  server.send (200, "text/html", Pump_Wet_page); // Отправить веб-страницу
}

// для датчиков отправки данных
void get_data(){
  if (!is_authentified()) {
    server.sendHeader("Location", "/Auth");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  String res[count_args];
  parse_string(res_in, res, count_args);

  String res_str = "";
  if(server.argName(0) == "DHT11" && server.arg(0) == "1"){
    res_str=res[0]+",";
    res_str+=res[1]+",";
  }
  if(server.argName(1) == "MQ135" && server.arg(1) == "1")res_str+=res[2]+",";
  if(server.argName(2) == "Flame_sensor" && server.arg(2) == "1")res_str+=res[3]+",";
  if(server.argName(3) == "Pump_Wet" && server.arg(3) == "1"){
    res_str+=res[4]+",";
    res_str+=res[5]+",";
  }
  if(server.argName(4) == "ttime" && server.arg(4) == "1")res_str+=String(time_/1000);
  server.send (200, "text/plain", res_str); // Отправить
}

// для парсинга строки на нужное нам разделение
void parse_string(String res_in, String *res, int count_args){
  for(int i = 0, j = 0; i < res_in.length() && j < count_args; i++){
    if(',' == res_in[i]){
      j++;
    }
    else{
      res[j]+=res_in[i];
    }
  }
}

//для несуществующей страницы
void handle_NotFound(){
 server.send(404, "text/plain", "Not found");
}