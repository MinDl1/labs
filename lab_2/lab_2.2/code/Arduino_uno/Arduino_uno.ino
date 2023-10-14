#include "ESP32_MailClient.h"
#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>
#include "pages.h"

#include <MFRC522.h> //library responsible for communicating with the module RFID-RC522
#include <SPI.h> //library responsible for communicating of SPI bus
#define SS_PIN 5
#define RST_PIN 27
#define SIZE_BUFFER 18
#define MAX_SIZE_BLOCK 16
#define greenPin 12
#define redPin 32
#define SOUND_PIN 33
bool grD = false;
bool rdD = false;

//used in authentication
MFRC522::MIFARE_Key key;
//authentication return status code
MFRC522::StatusCode status;
// Defined pins to module RC522
MFRC522 mfrc522(SS_PIN, RST_PIN);
 
// замените на свои учетные данные
const char* ssid = "";
const char* password = "";

#define emailSenderAccount    ""  
#define emailSenderPassword   ""
#define emailRecipient        ""
#define smtpServer            "smtp.mail.ru"
#define smtpServerPort        465
#define emailSubject          "ESP32 door"
SMTPData smtpData;

WebServer server(80);

bool bool_o_c = false;
String our_code = "somes";

LiquidCrystal_I2C lcd(0x27,16,2); // Задаем адрес и размерность дисплея

void setup(){
    Serial.begin(9600);
    pinMode(greenPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    pinMode(SOUND_PIN, OUTPUT);

    lcd.init(); // Инициализация lcd
    lcd.backlight(); // Включаем подсветку

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(200);
    }
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());


    //Для страниц
    server.on("/", handle_root);
    server.on("/Auth", handle_auth);
    server.onNotFound(handle_NotFound);
    //для датчиков
    server.on("/getData", get_data);
    //Для куки чтобы отслеживать их и выдовать
    const char * headerkeys[] = {"User-Agent", "Cookie"} ;
    size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
    //ask server to track these headers
    server.collectHeaders(headerkeys, headerkeyssize);
    server.begin();


    smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);
    // Указываем адрес почты-получателя
    smtpData.setSender("ESP32", emailSenderAccount);
    // Указываем приоритет письма (Высокий, Обычный, Низкий или от 1 до 5(1-наивысший))
    smtpData.setPriority("High");
    // Указываем тему письма
    smtpData.setSubject(emailSubject);
    // Пишем сообщение обычным текстом
    smtpData.setMessage("Hello World! - Sent from ESP32 board", false);
    // Добавляем еще получателей, если нужно.
    smtpData.addRecipient(emailRecipient);
    smtpData.setSendCallback(sendCallback);


    SPI.begin(); // Init SPI bus
    // Init MFRC522
    mfrc522.PCD_Init();
    Serial.println("Approach your reader card...");
    Serial.println();
}

void sendCallback(SendStatus msg) {
  // Выводим текущий статус
  Serial.println(msg.info());
 
  // Что-нибудь выводим, чтобы проверить, работает ли код.
  if (msg.success()) {
    Serial.println("----------------");
  }
}

int is_authentified() {
  if (server.hasHeader("Cookie")) {
    String cookie = server.header("Cookie");
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      return 1;
    }
    if (cookie.indexOf("ESPSESSIONID=2") != -1) {
      return 2;
    }
  }
  return 0;
}

void handle_auth(){
  int auth_ = is_authentified();
  if (auth_ == 1 || auth_ == 2) {
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
    if(server.arg("login") == "admin" && server.arg("passwd") == "12345"){
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", "ESPSESSIONID=2");
      server.sendHeader("Location", "/");
      server.sendHeader("Cache-Control", "no-cache");
      server.send(301);
      return;
    }
  }
  server.send (200, "text/html", Auth_page); // Отправить веб-страницу
}

void handle_root(){
  int auth_ = is_authentified();
  if (auth_ != 1 && auth_ != 2) {
    server.sendHeader("Location", "/Auth");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  if(auth_ == 1){
    server.send (200, "text/html", MAIN_page); // Отправить веб-страницу
    return;
  }
  server.send (200, "text/html", MAIN_page_admin); // Отправить веб-страницу
}

void handle_NotFound(){
 server.send(404, "text/plain", "Not found");
}

void get_data(){
  int auth_ = is_authentified();
  if (auth_ != 1 && auth_ != 2) {
    server.sendHeader("Location", "/Auth");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  String res_data = "";
  if(bool_o_c && auth_ != 2){
    lcd.clear();
    lcd.setCursor(0, 0); // Устанавливаем курсор в начало 1 строки
    lcd.print("Close");
    rdD = true;
    lcd.clear();
    server.send (200, "text/plain", String("Доступ запрещен, Доступ запрещен, Закрыто")); // Отправить
    return;
  }
  if(server.argName(0) == "read_write"){
    if(server.arg(0) == "r"){
      if (!mfrc522.PICC_IsNewCardPresent()){
        res_data = String("Карта не приложена"); // Отправить
      }
      else{
        res_data = String("Карта приложена"); // Отправить
      }
      // Select a card
      if (!mfrc522.PICC_ReadCardSerial()){
        res_data += String(", Карта не прочитана"); // Отправить
      }
      else{
        res_data += String(", Карта прочитана"); // Отправить
      }
      res_data+=","+readingData();

      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();
    }
    else if(server.arg(0) == "w"){
      if(server.argName(1) == "wrin"){
        if (!mfrc522.PICC_IsNewCardPresent()){
          res_data = String("Карта не приложена"); // Отправить
        }
        else{
          res_data = String("Карта приложена"); // Отправить
        }
        // Select a card
        if (!mfrc522.PICC_ReadCardSerial()){
          res_data += String(", Карта не прочитана"); // Отправить
        }
        else{
          res_data += String(", Карта прочитана"); // Отправить
        }

        String s = writingData(server.arg(1));
        res_data+=","+s;
        mfrc522.PICC_HaltA();
        mfrc522.PCD_StopCrypto1();
      }
    }
  }
  if(auth_ == 2){
    if(server.argName(0) == "open"){
      if(server.arg(0) == "o"){
        Serial.println("opened door");
        grD = true;
        res_data+= ", Открыто";

        //Отправляем письмо
        if (!MailClient.sendMail(smtpData)) Serial.println("Ошибка отправки, " + MailClient.smtpErrorReason());
        //Очищаем память
        smtpData.empty();
      }
      else{
        res_data+= ", Закрыто";
    }
    }
    if(server.argName(0) == "open_close"){
      if(server.arg(0) == "c"){
        if(bool_o_c){
          bool_o_c = false;
        }
        else{
          bool_o_c = true;
        }
      }
    }
    if(bool_o_c){
      res_data += ", Запрещено";
    }
    else{
      res_data += ", Разрешено";
    }
    }
  server.send (200, "text/plain", res_data); // Отправить
}

void loop() {
    server.handleClient();
    if(grD){
      digitalWrite(greenPin, 1);
      digitalWrite(SOUND_PIN, 1);
      lcd.clear();
      lcd.setCursor(0, 0); // Устанавливаем курсор в начало 1 строки
      lcd.print("Opened");
      delay(1000);
      digitalWrite(SOUND_PIN, 0);
      digitalWrite(greenPin, 0);
      grD = false;
    }
    if(rdD){
      digitalWrite(redPin, 1);
      digitalWrite(SOUND_PIN, 1);
      lcd.clear();
      lcd.setCursor(0, 0); // Устанавливаем курсор в начало 1 строки
      lcd.print("Closed");
      delay(1000);
      digitalWrite(redPin, 0);
      digitalWrite(SOUND_PIN, 0);
      rdD = false;
    }
}

//reads data from card/tag
String readingData(){
    //prints the technical details of the card/tag
    mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));
    //prepare the key - all keys are set to FFFFFFFFFFFFh
    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
    //buffer for read data
    byte buffer[SIZE_BUFFER] = {0};
    //the block to operate
    byte block = 1;
    byte size = SIZE_BUFFER; //authenticates the block to operate
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("Authentication failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        rdD = true;
        return String("Authentication failed: ")+String(mfrc522.GetStatusCodeName(status));
    }
    //read data from block
    status = mfrc522.MIFARE_Read(block, buffer, &size);
    String re = (char*)buffer;
    String res_ = "";
    for(int i = 0; i < 5; i++){
      res_+=re[i];
    }
    Serial.println(res_);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("Reading failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        rdD = true;
        return String("Reading failed: ")+String(mfrc522.GetStatusCodeName(status));
    }
    else if(res_ == our_code){
        grD = true;

        //Отправляем письмо
        if (!MailClient.sendMail(smtpData)) Serial.println("Ошибка отправки, " + MailClient.smtpErrorReason());
        //Очищаем память
        smtpData.empty();

        Serial.print(F("\nData from block ["));
        Serial.print(block);Serial.print(F("]: "));
        //prints read data
        for (uint8_t i = 0; i < MAX_SIZE_BLOCK; i++){
            Serial.write(buffer[i]);
        }
        Serial.println(" ");
        return String("открыто");
    }
    else{
      Serial.print(F("\nData from block ["));
      Serial.print(block);Serial.print(F("]: "));
      //prints read data
      String res_ = "";
      for (uint8_t i = 0; i < MAX_SIZE_BLOCK; i++){
          Serial.write(buffer[i]);
      }
      Serial.println(" ");
      rdD = true;
      return String("Закрыто");
    }
}

String writingData(String in_) {
    //prints thecnical details from of the card/tag
    mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));
    // waits 30 seconds dor data entry via Serial
    Serial.setTimeout(30000L);
    Serial.println(F("Enter the data to be written with the '#' character at the end \n[maximum of 16 characters]:"));
    Serial.println(in_);
    //prepare the key - all keys are set to FFFFFFFFFFFFh
    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
    //buffer para armazenamento dos dados que iremos gravar
    //buffer for storing data to write
    byte buffer[MAX_SIZE_BLOCK] = "";
    for(int i = 0; i < MAX_SIZE_BLOCK && i < in_.length(); i++){
      buffer[i] = in_[i];
    }
    byte block; //the block to operat
    int dataSize; //size of data (bytes)
    //recover on buffer the data from Serial
    //all characters before chacactere '#'
    dataSize = in_.length();
    //void positions that are left in the buffer will be filled with whitespace
    for(int i=dataSize; i < MAX_SIZE_BLOCK; i++)buffer[i] = ' ';
    block = 1; //the block to operate
    //String str = (char*)buffer; //transforms the buffer data in String
    //Serial.println(str);
    //authenticates the block to operate
    //Authenticate is a command to hability a secure communication
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        rdD = true;
        return String("PCD_Authenticate() failed: ");
    }
    else Serial.println(F("PCD_Authenticate() success: "));
    //Writes in the block
    status = mfrc522.MIFARE_Write(block, buffer, MAX_SIZE_BLOCK);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Write() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        rdD = true;
        return String("MIFARE_Write() failed: "); 
    }
    else{
        Serial.println(F("MIFARE_Write() success: "));
        grD = true;

        //Отправляем письмо
        if (!MailClient.sendMail(smtpData)) Serial.println("Ошибка отправки, " + MailClient.smtpErrorReason());
        //Очищаем память
        smtpData.empty();

        return String("Открыто");
    }
}