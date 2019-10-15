#ifndef WEB_SERVER /* guard */
#define WEB_SERVER

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Modules\BaseModule.h"

AsyncWebServer server(80);

class WebServer : public BaseModule  {
    
   public:
    WebServer() {}

    void setup() {
        server.on("/", HTTP_GET, getRoot);

        // Send a GET request to <IP>/get?message=<message>
        server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
            String message;
            if (request->hasParam("message")) {
                message = request->getParam("message")->value();
            } else {
                message = "No message sent";
            }
            request->send(200, "text/plain", "Hello, GET: " + message);
        });

        // Send a POST request to <IP>/post with a form field message set to <message>
        server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){
            String message;
            if (request->hasParam("message", true)) {
                message = request->getParam("message", true)->value();
            } else {
                message = "No message sent";
            }
            request->send(200, "text/plain", "Hello, POST: " + message);
        });

        server.onNotFound(notFound);

        server.begin();
    }

    void loop() {}

   private:
    static void getRoot(AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello, world");
    }

    static void notFound(AsyncWebServerRequest *request) {
        request->send(404, "text/plain", "Not found");
    }

};
#endif

