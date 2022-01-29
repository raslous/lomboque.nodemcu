#ifndef WEBSERVER
#define WEBSERVER

#include <ESPAsyncWiFiManager.h>
#include <server.config.h>

class WebServer
{
    public:
    static void Setup()
    {
        AsyncWiFiManager wifiManager(&server,&dns);
        wifiManager.autoConnect(ssid, password);

        Serial.print("Stand By: ");
        Serial.println(WiFi.localIP());
    }
};

#endif