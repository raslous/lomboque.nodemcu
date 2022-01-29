#ifndef RESTAPI
#define RESTAPI

#include <ArduinoJson.h>
#include <server.config.h>
#include <webserver.h>

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

        }

};

#endif