#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>

#include "../lib/Clock/Clk.h"

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
Clk main_clock = Clk(11,24,30);

AsyncWebServer server(80);

void setup() { 
    Serial.begin(9600);
    
    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
        Serial.println("SPIFFS filesystem failed to mount! exiting...");
        return;
    } else {
        Serial.println("SPIFFS filesystem successfully mounted!");
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
        Serial.println("root was accessed");
        request->send(SPIFFS, "/index.html", "text/html");
    });

    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("Sending script.js to client...");
        request->send(SPIFFS, "/script.js", "text/javascript");
    });
    
    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
        String hours_str;
        String minutes_str;
        String seconds_str;

        String response_msg;

        Serial.println("REQEST RECIEVED ON /get ROUTE!");

        if (request->hasParam("time-set-hours")) {
            hours_str = request->getParam("time-set-hours")->value();
        }

        if (request->hasParam("time-set-minutes")) {
            minutes_str = request->getParam("time-set-minutes")->value();
        }

        if (request->hasParam("time-set-seconds")) {
            seconds_str = request->getParam("time-set-seconds")->value();
        }

        int hours = hours_str.toInt();
        int minutes = minutes_str.toInt();
        int seconds = seconds_str.toInt();

        if (main_clock.SetTime(hours, minutes, seconds)) {
            response_msg = "Time was set to " + hours_str + " : " + minutes_str + " : " + seconds_str;
            Serial.println(response_msg);
            request->send(200, "text/plain", response_msg);
        } else {
            response_msg = "400 Bad Request\nTime was not set due to invalid request data";
            request->send(400, "text/plain", response_msg);
            Serial.println(response_msg);

        }
    });
 
    server.begin();
}

void loop() {
    main_clock.Tick();
    Serial.println(main_clock.get_time_c_str());
}