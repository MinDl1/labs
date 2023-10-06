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
 server.on("/", handle_root);
 server.on("/Auth", handle_auth);
 server.on("/getDHT11", handle_DHT11);
 server.on("/getMQ135", handle_MQ135);
 server.on("/getFlame_sensor", handle_Flame_sensor);
 server.on("/getPump_Wet", handle_Pump_Wet);

 //для датчиков
 server.on("/getData", get_data);

 server.onNotFound(handle_NotFound);

 //Для куки чтобы отслеживать их и выдовать
 const char * headerkeys[] = {"User-Agent", "Cookie"} ;
 size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
 //ask server to track these headers
 server.collectHeaders(headerkeys, headerkeyssize);

 server.begin();
 Serial.println("HTTP server started");
}

//String res_s = "";
void loop() {
  server.handleClient();

  /*
  if(Serial.available() == 0){}
  res_s = Serial.readString();
  res_s.trim();
  */

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

void handle_root(){
  if (!is_authentified()) {
    server.sendHeader("Location", "/Auth");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  server.send (200, "text/html", MAIN_page); // Отправить веб-страницу
}

void handle_DHT11(){
  if (!is_authentified()) {
    server.sendHeader("Location", "/Auth");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  server.send (200, "text/html", DHT11_page); // Отправить веб-страницу
}

void handle_MQ135(){
  if (!is_authentified()) {
    server.sendHeader("Location", "/Auth");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  server.send (200, "text/html", MQ135_page); // Отправить веб-страницу
}

void handle_Flame_sensor(){
  if (!is_authentified()) {
    server.sendHeader("Location", "/Auth");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  server.send (200, "text/html", Flame_sensor_page); // Отправить веб-страницу
}

void handle_Pump_Wet(){
  if (!is_authentified()) {
    server.sendHeader("Location", "/Auth");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  server.send (200, "text/html", Pump_Wet_page); // Отправить веб-страницу
}

void get_data(){
  if (!is_authentified()) {
    server.sendHeader("Location", "/Auth");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  int a1 = random(10, 30);
  int a2 = random(30, 90);
  int a3 = random(300, 900);
  int a4 = random(2);
  int a5 = random(2);
  int a6 = random(60, 120);
  //res_s send
  String res_in = String(a1)+","+String(a2)+","+String(a3)+","+String(a4)+","+String(a5)+","+String(a6);
  String res[6];
  for(int i = 0, j = 0; i < res_in.length(); i++){
    if(',' == res_in[i]){
      j++;
    }
    else{
      res[j]+=res_in[i];
    }
  }
  String res_str = "";
  if(server.argName(0) == "DHT11" && server.arg(0) == "1"){
    res_str=res[0]+",";
    res_str+=res[1]+",";
  }
  if(server.argName(1) == "MQ135" && server.arg(1) == "1")res_str+=res[2]+",";
  if(server.argName(2) == "Flame_sensor" && server.arg(2) == "1")res_str+=res[3]+",";
  if(server.argName(3) == "Pump_Wet" && server.arg(3) == "1"){
    res_str+=res[4]+",";
    res_str+=res[5];
  }
  Serial.println(res_str);
  server.send (200, "text/plain", res_str); // Отправить
}

void handle_NotFound(){
 server.send(404, "text/plain", "Not found");
}