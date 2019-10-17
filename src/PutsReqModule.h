#ifndef HTTP_PUTSREQ_WRITER /* guard */
#define HTTP_PUTSREQ_WRITER

#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <DhtReader.h>
#include "Modules\BaseModule.h"

class PutsReqModule : public BaseModule  {
    
    const uint8_t fingerprint[20] = {0x14, 0xe1, 0x0e, 0x30, 0x31, 0x9b, 0x12, 0xf3, 0xa0, 0x91, 0xe3, 0x61, 0xf2, 0x32, 0x39, 0x2a, 0xf2, 0xc6, 0x31, 0x33};
    
    int ledPin = D1;
    int buttonPin = D3;

    bool prevButtonState = false;
    bool perfomOperation = false;

    DhtReader dhtReader;

   public:
    PutsReqModule(DhtReader dht) : dhtReader(dht) {}

    void setup() {
        pinMode(ledPin, OUTPUT);
        pinMode(buttonPin, INPUT_PULLUP);
    }

    void loop() {
        
        // flip state if button was pressed (changed from 0 -> 1)
        bool currButtonState = !digitalRead(buttonPin);

        if (!prevButtonState && currButtonState) {
            perfomOperation = !perfomOperation;
            Serial.printf("Perform Operation: %s\n", perfomOperation ? "true" : "false");
        }

        prevButtonState = currButtonState;

        digitalWrite(ledPin, perfomOperation);

        if (perfomOperation && (millis() % 2000)) {

            float temp = dhtReader.readTemperature();
            String message = "temperature:" + String(temp);
            SendReq(message);
        }
    }

   private:
    void SendReq(String message) {
        std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
        client->setFingerprint(fingerprint);

        HTTPClient https;

        String url = "https://putsreq.com/Alex?from=ESP&Today=9.Oct_9.50&time=";
        url += millis();
        url += "$message=" + message;

        Serial.println("[HTTP] begin..." + url);

        if (https.begin(*client, url)) {
            // start connection and send HTTP header
            int httpCode = https.GET();

            // httpCode will be negative on error
            if (httpCode < 0) {
                Serial.printf("[HTTP] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
            } else {
                Serial.printf("[HTTP] GET... code: %d\n", httpCode);

                // file found at server
                if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                    String payload = https.getString();
                    Serial.println(payload);
                }
            }

            https.end();
        } else {
            Serial.printf("[HTTP} Unable to connect\n");
        }
    }
};
#endif