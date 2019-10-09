#include "Wifi-Connect.h"
#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

const uint8_t fingerprint[20] = {0x14, 0xe1, 0x0e, 0x30, 0x31, 0x9b, 0x12, 0xf3, 0xa0, 0x91, 0xe3, 0x61, 0xf2, 0x32, 0x39, 0x2a, 0xf2, 0xc6, 0x31, 0x33};

void putsReq_Write(String message){
    
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
        }
        else {
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