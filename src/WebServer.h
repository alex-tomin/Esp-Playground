#ifndef WEB_SERVER /* guard */
#define WEB_SERVER

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Modules\BaseModule.h"

AsyncWebServer server(80); //TODO: move inside class

class WebServer : public BaseModule  {

    //DhtReader dhtReader;

   public:
    WebServer() {
        //dhtReader = dht;
    }

    void setup() {
        server.on("/", HTTP_GET, getRoot);
        server.on("/message", HTTP_GET, getMessage);
        server.on("/message", HTTP_POST, postMessage); 

        server.on("/temp", HTTP_GET, std::bind(&WebServer::getTemperature, this, std::placeholders::_1)); 
        server.onNotFound(notFound);
        server.begin();
    }

    void loop() {}

   private:

    void getTemperature(AsyncWebServerRequest *request){
        DhtReader dhtReader;
        dhtReader.printSensorDetails();
        delay(2000);
        float temp = dhtReader.readTemperature();
        String body = "Temperature:\t" + String(temp);
        request->send(200, "text/plain", body);
    }

    static void getRoot(AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello, world");
    }

    // Send a GET request to <IP>/get?message=<message>
    static void getMessage(AsyncWebServerRequest *request) {
        String message;
        if (request->hasParam("message")) {
            message = request->getParam("message")->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, GET: " + message);
    }

    // Send a POST request to <IP>/post with a form field message set to <message>
    static void postMessage(AsyncWebServerRequest *request) {
        String message;
        if (request->hasParam("message", true)) {
            message = request->getParam("message", true)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message);
    }

    static void notFound(AsyncWebServerRequest *request) {
        request->send(404, "text/plain", "Not found");
    }

};
#endif

