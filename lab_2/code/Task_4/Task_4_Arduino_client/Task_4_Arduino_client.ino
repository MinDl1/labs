#include <WiFi.h>

const char* ssid     = "your-ssid"; // Change this to your WiFi SSID
const char* password = "your-password"; // Change this to your WiFi password

const int httpPort = 6000; // This should not be changed

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
}

void readResponse(WiFiClient *client){
  unsigned long timeout = millis();
  while(client->available() == 0){
    if(millis() - timeout > 5000){
      Serial.println(">>> Client Timeout !");
      client->stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while(client->available()) {
    String line = client->readStringUntil('\r');
    Serial.print(line);
  }

  Serial.printf("\nClosing connection\n\n");
}

void loop(){
  WiFiClient client;

  // WRITE --------------------------------------------------------------------------------------------
  if (client.connect(host, httpPort)) {
    client.write("something\n");
    digitalWrite(5, HIGH);
  }
  else{
    digitalWrite(5, LOW);
  }
  // -------------------------------------------------------------------------------------------------

  delay(10000);
}