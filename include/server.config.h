#ifndef CONFIG
#define CONFIG

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>

// WiFi Manager IP          [ 192.168.4.1 ]
// WiFi Manager Password    [ 2-4-8-16-32-64 ]
const char* ssid = "lomboque";
const char* password = "12345678";
const int port = 80;
AsyncWebServer server(port);
DNSServer dns;

#endif