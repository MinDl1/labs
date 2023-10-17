// ВАЖНЫЕ библиотеки
#include <FastBot.h> 

//вайфай
#define WIFI_SSID "" 
#define WIFI_PASS "" 
//токен
#define BOT_TOKEN ""
//датчики
#define ky_038 32
#define ky_018 33

//массивы
const int count_mass = 5;
String hi_mass[count_mass] = {"Привет!", "Hello", "Прив", "Hi", "Салам"};
String how_mass[count_mass] = {"Нормально", "Норма, а у тебя?", "Нормас", "Бомба", "Бомба, а у тебя?"};

//старт бот
FastBot bot(BOT_TOKEN); 

// Функция setup(опередления различных начальных настроек)
void setup() { 
    connectWiFi(); 
    bot.attach(newMsg);
    bot.showMenu("Привет! \t Как дела? \n Звук \t Свет");
    pinMode(ky_038, INPUT);
    pinMode(ky_018, INPUT);
} 

// бесконечный цикл
void loop() { 
    bot.tick(); 
} 

// подключение к вайфая
void connectWiFi() { 
    delay(2000); 
    Serial.begin(115200); 
    Serial.println(); 
    WiFi.begin(WIFI_SSID, WIFI_PASS); 
    while (WiFi.status() != WL_CONNECTED) { 
      delay(500); 
      Serial.print("."); 
      if (millis() > 15000){
        ESP.restart(); 
      }
    }
    Serial.println("Connected"); 
} 

//ответ на сообщение
void newMsg(FB_msg& msg) { 
    String tem = "("+msg.chatID+", "+msg.username+", "+msg.text+")"; 
    Serial.println(msg.text.substring(0, 22));
    if(msg.text == "/start"){
      bot.sendMessage("Вот список моих команд: \n1)Привет\n2)как дела?\nСвет\nЗвук\nНапоминание в формате(последнее число мсек): Напоминание Сделать лабу|3000", msg.chatID);
    }
    else if(msg.text == "Hello" || msg.text == "Hi" || msg.text == "Привет" || msg.text == "Привет!"){ 
      int i = random(count_mass);
      Serial.println("From: "+msg.chatID+"; text: "+msg.text+"; respose: "+hi_mass[i]);
      bot.sendMessage(hi_mass[i], msg.chatID); 
    }
    else if(msg.text == "Как дела?" || msg.text == "How are you?" || msg.text == "как дела?" || msg.text == "how u?"){
      int i = random(count_mass);
      Serial.println("From: "+msg.chatID+"; text: "+msg.text+"; respose: "+how_mass[i]);
      bot.sendMessage(how_mass[i], msg.chatID);
    }
    else if(msg.text == "Звук"){
      String s = String(analogRead(ky_038));
      Serial.println("From: "+msg.chatID+"; text: "+msg.text+"; respose: "+s);
      bot.sendMessage("Звук: "+s, msg.chatID);
    }
    else if(msg.text == "Свет"){
      String s = String(analogRead(ky_018));
      Serial.println("From: "+msg.chatID+"; text: "+msg.text+"; respose: "+s);
      bot.sendMessage("Свет: "+s, msg.chatID);
    }
    else if(msg.text.substring(0, 22) == "Напоминание"){
      String s = msg.text.substring(22);
      String text_time[2] = {"", ""};
      for(int i = 0, j = 0; i < msg.text.length(); i++ ){
        if(s[i] != '|'){
          text_time[j]+=s[i];
        }
        else{
          j++;
        }
      }
      
      while(true){
        int delay_ = text_time[1].toInt();
        Serial.println(delay_);
        delay(delay_);
        Serial.println("From: "+msg.chatID+"; text: "+msg.text+"; respose: "+text_time[0]);
        bot.sendMessage(text_time[0], msg.chatID);
      }

    }
    else{
      bot.sendMessage("Вот список моих команд: \n1)Привет\n2)как дела?\nСвет\nЗвук\nНапоминание в формате(последнее число мсек): Напоминание Сделать лабу|3000", msg.chatID);
    }
    Serial.println(tem); 
}
