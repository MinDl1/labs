#include <WiFi.h>

const char* ssid     = "your-ssid"; // Change this to your WiFi SSID
const char* password = "your-password"; // Change this to your WiFi password

int httpPort = 6000; // This should not be changed
IPAddress host(10,0,2,10);
WiFiClient client;

void setup()
{
    pinMode(5, OUTPUT);
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
  if (client.available()) {
    client.write("something\n");
    digitalWrite(5, HIGH);
    client.stop();
  }
  else{
    digitalWrite(5, LOW);
  }
  // -------------------------------------------------------------------------------------------------

  delay(10000);
}