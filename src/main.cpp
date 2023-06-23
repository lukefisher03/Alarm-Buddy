#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>

#define FORMAT_SPIFFS_IF_FAILED true
#define OPEN_NETWORK true

#if OPEN_NETWORK == true
    const char* passwd = NULL;
#else
    char passwd[] = "password";
#endif



char ssid[] = "ALARM_BUDDY";
int WIFI_TIMEOUT_LENGTH = 10;
File webpage;


WiFiServer server(80);

void setup() { 
    Serial.begin(9600);
    
    WiFi.softAP(ssid,passwd,1, 0, 1);   // Create soft access point that only allows one users at a time.
    IPAddress server_ip = WiFi.softAPIP();
    Serial.println("WiFi connection created, serving at: ");
    Serial.print(server_ip);

    server.begin();

    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
        Serial.println("SPIFFS filesystem failed to mount!");
        return;
    } else {
        Serial.println("SPIFFS filesystem successfully mounted!");
    }

    webpage = SPIFFS.open("/index.html");
    if (!webpage) {
        Serial.println("ERROR OPENING FILE!");
        return;
    }

    Serial.println("FILE CONTENTS:");
    while(webpage.available()) {
        Serial.write(webpage.read());
    }

    webpage.close();
}

void loop() {
    WiFiClient client = server.available();

    if (client) {
        Serial.println("New client just connected....");
        String client_data = "";
        
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();

                Serial.write(c);

                if (c == '\n') {
                    if (client_data.length() == 0) {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();

                        client.write(webpage.read());
                        client.println();
                        break;
                    } else {
                        client_data = "";
                    }
                } else if (c != '\r') {
                    client_data += c;
                }
            }
        }

        client.stop();
        Serial.println("Client disconnected");
    }



}