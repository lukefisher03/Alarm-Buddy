#include <Arduino.h>
#include <WiFi.h>

char ssid[] = "SSID";
char passwd[] = "PASSWORD";
int WIFI_TIMEOUT_LENGTH = 10;
WiFiServer server(80);

bool wifiConnect(char [], char []);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bool wifi_status = wifiConnect(ssid, passwd);

  if(wifi_status) {
    Serial.println("Starting web server...");
    server.begin();
    IPAddress ip = WiFi.localIP();
    Serial.println("Web server started at: ");
    Serial.print(ip);
  } else {
    Serial.println("Web server not started, not connected to the internet!");
  }

  Serial.println();
}

void loop() {
  WiFiClient client = server.available();
  if(client) {
    Serial.println("CLIENT CONNECTED!");

    bool currentLineIsBlank = true;

    while(client.connected()) {
      if(client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<h1>Welcome to the esp32 webpage</h1>");
          client.println("</html>");

        }

        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }        

      }
    }

    delay(1);
    client.stop();
    Serial.println("Client connection completed!");
  }
}

bool wifiConnect(char ssid[], char passwd[]) {
  /***
   * Connect to a wifi network
   * 
   * Params: ssid, passwd
   * Returns: Boolean indicating connection status
  */
  bool connected = false;
  Serial.println("Attempting to connect to network: ");
  Serial.print(ssid);

  WiFi.begin(ssid, passwd);
  for(int i = 0; i < WIFI_TIMEOUT_LENGTH; i++) {
    delay(1000);
    Serial.println("Connection in progress...");
    Serial.print(i);
    Serial.print(" seconds passed");
    Serial.println();
    if(WiFi.status() == WL_CONNECTED) {
      connected = true;
      break;
    }
  }

  (connected == true) ? Serial.println("Connection successful!") : Serial.println("Connection failed!");

  return connected;
}

