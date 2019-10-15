#ifndef WIFI_CONNECT_MODULE /* guard */
#define WIFI_CONNECT_MODULE

// `<..>` - compiler searches in pre-defined locations first
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>

#include "BaseModule.h"

// launches wifi AP mode if no safed config or when D5 button is pressed
class WifiConnectModule: public BaseModule {
   
    int resetButtonPin = D5;    //TODO: configure button
    bool prevResetButtonState = false;  //TODO: button management

   public:
    WifiConnectModule(){}

    void setup() {
        pinMode(resetButtonPin, INPUT_PULLUP);
        autoConnect();
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
            Serial.println("Reset Buton Pressed - WiFi settings to be invalidated");
            WiFi.disconnect(true);
            delay(1000);
            //autoConnect();
            ESP.reset(); //TODO: temp hach not to occupy web server port.
        }
        prevResetButtonState = currButtonState;
    }

   private:
    void autoConnect() {
        AsyncWebServer server(80);
        DNSServer dns;
        AsyncWiFiManager wifiManager(&server, &dns);

        wifiManager.autoConnect();

        Serial.printf("\n Connection established! IP address:\t ");
        Serial.println(WiFi.localIP()); 
    }
};

#endif