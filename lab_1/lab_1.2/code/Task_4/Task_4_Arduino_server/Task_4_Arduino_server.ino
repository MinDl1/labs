#include <WiFi.h>

const char* ssid     = "Lab_319_new";
const char* password = "rbcrbcrbc";
int port = 6000;

WiFiServer server(port);

void setup()
{
    Serial.begin(115200);

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";     
    char c;           // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {
        c = client.read();             // read a byte, then
        Serial.print(c);                    // print it out the serial monitor
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
