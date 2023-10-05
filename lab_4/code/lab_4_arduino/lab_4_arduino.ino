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

void setup() {
 Serial.begin(115200);
 WiFi.softAP(ssid, password);
 WiFi.softAPConfig(local_ip, gateway, subnet);
 delay(100);

 //Для страниц
 //server.on("/SendAuth", handle_auth);
 server.on("/", handle_auth);
 server.on("/getRoot", handle_auth);
 server.on("/getDHT11", get_page_DHT11);
 server.on("/getMQ135", get_page_MQ135);
 server.on("/getFlame_sensor", get_page_Flame_sensor);
 server.on("/getPump_Wet", get_page_Pump_Wet);

 //для датчиков
 server.on("/getDHT11_temp", get_data_DHT11_temp);
 server.on("/getDHT11_wet", get_data_DHT11_wet);
 server.on("/getMQ135_ppm", get_data_MQ135_ppm);
 server.on("/getFlame_sens", get_data_Flame_sens);
 server.on("/getPump_work", get_data_Pump_work);
 server.on("/getWet_ground", get_data_Wet_ground);

 server.onNotFound(handle_NotFound);

 //Для куки чтобы отслеживать их и выдовать
 const char * headerkeys[] = {"User-Agent", "Cookie"} ;
 size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
 //ask server to track these headers
 server.collectHeaders(headerkeys, headerkeyssize);

 server.begin();
 Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  delay(2);
}

bool is_authentified() {
  if (server.hasHeader("Cookie")) {
    String cookie = server.header("Cookie");
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      return true;
    }
  }
  return false;
}

void handle_auth(){
  if (is_authentified()) {
    String s = MAIN_page; // Чтение содержимого HTML
    server.send (200, "text/html", s);
    return;
  }
  bool login_bool = false;
  bool passwd_bool = false;
  for (int i = 0; i < server.args(); i++){
    if(server.argName(i) == "login" && server.arg(i) == "esp32")login_bool = true;     // получить имя параметра и значение Сравниваем
    else if(server.argName(i) == "passwd" && server.arg(i) == "01234567")passwd_bool = true;
  }
  if(login_bool && passwd_bool){
    String s = MAIN_page; // Чтение содержимого HTML
    server.sendHeader("Cache-Control", "no-cache");
    //server.sendHeader("Set-Cookie", "login=esp32");
    server.sendHeader("Set-Cookie", "ESPSESSIONID=1");

    server.send (200, "text/html", s); // Отправить веб-страницу
  }
  else{
    String s = Auth_page; // Чтение содержимого HTML
    server.send (200, "text/html", s); // Отправить веб-страницу
  }
}

/*void handle_root() {
  if (!is_authentified()){
    server.sendHeader("Location", "/");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  String s = MAIN_plain; // Чтение содержимого HTML
  server.send (200, "text/html", s); // Отправить веб-страницу
}*/

void get_page_DHT11(){
  if (!is_authentified()) {
    String s = MAIN_page; // Чтение содержимого HTML
    server.send (200, "text/html", s);
    return;
  }
  String s = DHT11_page; // Чтение содержимого HTML
  server.send (200, "text/html", s); // Отправить веб-страницу
}

void get_page_MQ135(){
  if (!is_authentified()) {
    String s = MAIN_page; // Чтение содержимого HTML
    server.send (200, "text/html", s);
    return;
  }
  String s = MQ135_page; // Чтение содержимого HTML
  server.send (200, "text/html", s); // Отправить веб-страницу
}

void get_page_Flame_sensor(){
  if (!is_authentified()) {
    String s = MAIN_page; // Чтение содержимого HTML
    server.send (200, "text/html", s);
    return;
  }
  String s = Flame_sensor_page; // Чтение содержимого HTML
  server.send (200, "text/html", s); // Отправить веб-страницу
}

void get_page_Pump_Wet(){
  if (!is_authentified()) {
    String s = MAIN_page; // Чтение содержимого HTML
    server.send (200, "text/html", s);
    return;
  }
  String s = Pump_Wet_page; // Чтение содержимого HTML
  server.send (200, "text/html", s); // Отправить веб-страницу
}

void get_data_DHT11_temp(){
  if (!is_authentified()) {
    String s = MAIN_page; // Чтение содержимого HTML
    server.send (200, "text/html", s);
    return;
  }
  int a = random(10, 30);
  String temp = String (a);
  server.send (200, "text/plain", temp);
}

void get_data_DHT11_wet(){
  if (!is_authentified()) {
    String s = MAIN_page; // Чтение содержимого HTML
    server.send (200, "text/html", s);
    return;
  }
  int a = random(30, 90);
  String wetness = String (a);
  server.send (200, "text/plain", wetness);
}

void get_data_MQ135_ppm(){
  if (!is_authentified()) {
    String s = MAIN_page; // Чтение содержимого HTML
    server.send (200, "text/html", s);
    return;
  }
  int a = random(300, 900);
  String ppm = String (a);
  server.send (200, "text/plain", ppm);
}

void get_data_Flame_sens(){
  if (!is_authentified()) {
    String s = MAIN_page; // Чтение содержимого HTML
    server.send (200, "text/html", s);
    return;
  }
  int a = random(2); 
  String flame = String (a);
  server.send (200, "text/plain", flame);
}

void get_data_Pump_work(){
  if (!is_authentified()) {
    String s = MAIN_page; // Чтение содержимого HTML
    server.send (200, "text/html", s);
    return;
  }
  int a = random(2);
  String pump = String (a);
  server.send (200, "text/plain", pump);
}

void get_data_Wet_ground(){
  if (!is_authentified()) {
    String s = MAIN_page; // Чтение содержимого HTML
    server.send (200, "text/html", s);
    return;
  }
  int a = random(60, 120);
  String wetground = String (a);
  server.send (200, "text/plain", wetground);
}

void handle_NotFound(){
 server.send(404, "text/plain", "Not found");
}