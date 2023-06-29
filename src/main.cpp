#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>

#define FORMAT_SPIFFS_IF_FAILED true
#define OPEN_NETWORK true

#if OPEN_NETWORK == true
    const char* passwd = NULL;
#else
    char passwd[] = "password";
#endif



char ssid[] = "ALARM_BUDDY";
int WIFI_TIMEOUT_LENGTH = 10;
IPAddress local_IP(192,168,1,184);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
File webpage;


AsyncWebServer server(80);

void setup() { 
    Serial.begin(9600);
    
    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
        Serial.println("SPIFFS filesystem failed to mount! exiting...");
        return;
    } else {
        Serial.println("SPIFFS filesystem successfully mounted!");
    }

    webpage = SPIFFS.open("/index.html");
    if (!webpage) {
        Serial.println("Could not locate index.html file...exiting");
        return;
    }
    
    if(!WiFi.softAPConfig(local_IP, gateway, subnet)) {
        Serial.println("Failed to configure static network...exiting");
        return;
    }

    WiFi.softAP(ssid,passwd,1, 0, 1);   // Create soft access point that only allows one users at a time.
    IPAddress server_ip = WiFi.softAPIP();
    Serial.println("WiFi connection created, serving at: ");
    Serial.print(server_ip);

    server.begin();
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", "text/html");
    });
 
    server.begin();
    webpage.close();
}

void loop() {
    
}