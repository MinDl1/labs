#include <WiFi.h>

const char* ssid     = "Lab_319_new";
const char* password = "rbcrbcrbc";

int httpPort = 6000; // This should not be changed
IPAddress host(10,215,3,74);
WiFiClient client;

void setup()
{
    Serial.begin(115200);
    while(!Serial){delay(100);}

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println("******************************************************");
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    client.connect(host, httpPort);
}

void loop(){
  // WRITE --------------------------------------------------------------------------------------------
  if(client.connected()){
    client.print("\nsomething");
    Serial.println("something");
  }
  // -------------------------------------------------------------------------------------------------

  delay(10000);
}