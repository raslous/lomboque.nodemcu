#ifndef RESTAPI
#define RESTAPI

#include <ArduinoJson.h>
#include <server.config.h>
#include <webserver.h>
#include <nodemcu.h>

DynamicJsonDocument doc(256);
char json_string[256];

class API
{
    private:
        static void NotFound(AsyncWebServerRequest *request)
        {
            request->send(404, "text/plain", "not found");
        }

    public:

        static void Setup()
        {
            WebServer::Setup();
        }

        static void Start()
        {

            server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
                request->send(200, "application/json", json_string);
            });

            server.onNotFound(NotFound);
            server.begin();
        }

        static void Loop()
        {
            doc["temperature"] = temperature;
            doc["humidities"][0] = percentageValue1;
            doc["humidities"][1] = percentageValue2;

            serializeJson(doc, json_string);

            Serial.print("suhu: ");
            Serial.print(temperature);
            Serial.print(" °C");
            Serial.print(" | ");

            Serial.print("ch.1: ");
            Serial.print(rawValue1);
            Serial.print(" (");
            Serial.print(percentageValue1);
            Serial.print("%");
            Serial.print(")");
            Serial.print(" | ");
            Serial.print("ch.2: ");
            Serial.print(rawValue2);
            Serial.print(" (");
            Serial.print(percentageValue2);
            Serial.print("%");
            Serial.print(")");
            Serial.print("\n");
        }

};

#endif