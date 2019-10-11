#ifndef WIFI_CONNECT_MODULE /* guard */
#define WIFI_CONNECT_MODULE

// `<..>` - compiler searches in pre-defined locations first
#include <Arduino.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include "BaseModule.h"

class WifiConnectModule: public BaseModule {
   
    int resetButtonPin = D5;
    bool prevResetButtonState = false;
    WiFiManager wifiManager;

    void wifiConnect_autoConnect() {
        wifiManager.autoConnect("Sashko_Esp");

        Serial.printf("\n Connection established! IP address:\t ");
        Serial.println(WiFi.localIP());  // Send the IP address of the ESP8266 to the computer
    }

   public:
    WifiConnectModule(){}

    void setup() {
        pinMode(resetButtonPin, INPUT_PULLUP);
        wifiConnect_autoConnect();
    }

    void loop() {
        // wait for WiFi connection
        if ((WiFi.status() != WL_CONNECTED)) {
            Serial.println("Wifi not connected, will wait 10 sec...");
            delay(10000);
        }

        // flip state if button was pressed (changed from 0 -> 1)
        bool currButtonState = !digitalRead(resetButtonPin);
        if (!prevResetButtonState && currButtonState) {
            Serial.println("Reset Buton Pressed");

            wifiManager.resetSettings();
            delay(1000);
            wifiConnect_autoConnect();
        }
        prevResetButtonState = currButtonState;
    }
};

#endif