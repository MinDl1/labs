#include <FastBot.h> 

#define WIFI_SSID "**********" 
#define WIFI_PASS "**********" 
#define BOT_TOKEN "***********************************************"
#define ky_038 32
#define ky_018 33

const int count_mass = 5;
String hi_mass[count_mass] = {"Привет!", "Hello", "Прив", "Hi", "Салам"};
String how_mass[count_mass] = {"Нормально", "Норма, а у тебя?", "Нормас", "Бомба", "Бомба, а у тебя?"};

FastBot bot(BOT_TOKEN); 
void setup() { 
    connectWiFi(); 
    bot.attach(newMsg); 
    bot.showMenu("Привет! \t Как дела? \n Звук \t Свет");
    pinMode(ky_038, INPUT);
    pinMode(ky_018, INPUT);
} 
void loop() { 
    bot.tick(); 
} 
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

void newMsg(FB_msg& msg) { 
    String tem = "("+msg.chatID+", "+msg.username+", "+msg.text+")"; 
    if(msg.text == "Hello" || msg.text == "Hi" || msg.text == "Привет" || msg.text == "Привет!"){ 
      int i = random(count_mass);
      bot.sendMessage(hi_mass[i], msg.chatID); 
    }
    else if(msg.text == "Как дела?" || msg.text == "How are you?" || msg.text == "как дела?" || msg.text == "how u?"){
      int i = random(count_mass);
      bot.sendMessage(how_mass[i], msg.chatID);
    }
    else if(msg.text == "Звук"){
      String s = String(analogRead(ky_038));
      bot.sendMessage("Звук: "+s, msg.chatID);
    }
    else if(msg.text == "Свет"){
      String s = String(analogRead(ky_018));
      bot.sendMessage("Свет: "+s, msg.chatID);
    }
    else if(msg.text.substring(0, 12) == "Напоминание"){
      String s = msg.text.substring(12);
      String text_time[2] = {"", ""};
      for(int i = 0, j = 0; i < msg.text.length(); i++ ){
        if(msg.text[i] != '|'){
          text_time[j]+=msg.text[i];
        }
        else{
          j++;
        }
      }
      
      while(true){
        int delay_ = text_time[1].toInt();
        delay(delay_);
        bot.sendMessage(text_time[0], msg.chatID);
      }

    }
    Serial.println(tem); 
}
