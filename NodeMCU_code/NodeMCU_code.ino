#include <ESP8266WiFi.h>
#include<SoftwareSerial.h>
#include<SPI.h>

SoftwareSerial s(12, 14); //RX & TX

const char* ssid     = "Agraj Khare";
const char* password = "rishit@2104";
const char* host = "192.168.43.156";


void setup() {
  Serial.begin(9600);
  s.begin(9600);
  delay(10);
  pinMode(A0, INPUT);
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
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  delay(5000);

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 3000;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/";

  Serial.print("Requesting URL: ");
  Serial.println(url);

  
  if (s.available() > 0) {
    
      double gpsx = s.read();
      double gpsy = s.read();
      int level = s.read();

      String data = "gps_coordinate_la=" + String(gpsx) + "&gps_coordinate_lo=" + String(gpsy) + "&pollution_level=" + String(level);

      Serial.print("Requesting POST: ");
      // Send request to the server:
      client.println("POST / HTTP/1.1");
      client.println("Host: server_name");
      client.println("Accept: */*");
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.print("Content-Length: ");
      client.println(data.length());
      client.println();
      client.print(data);
    
  }

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");

}
