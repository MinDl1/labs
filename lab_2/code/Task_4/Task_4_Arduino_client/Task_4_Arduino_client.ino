#include <Wifi.h>

const char* ssid = "yourNetworkName";
const char* password =  "yourNetworkPass";

WiFiClient wificlient(80);

void setup() {
 
  Serial.begin(115200);
 
  delay(5000);
  
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
 
  Serial.print("Connected to WiFi. IP:");
  Serial.println(WiFi.localIP());
 
  wificlient.begin();
}

void loop() {

IPAddress remoteHost(xxx,xxx,xxx,xxx);  // IP address of the remote service
int portNumber = 21;               // FTP standard port number
WiFiClient client = wificlient.available();
    if (client.connect(remoteHost, portNumber)) {
           // here you are connected, you can use the documented FTP protocol to discuss with the service
           client.write("some");
    }
}