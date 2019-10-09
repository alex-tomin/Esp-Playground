// `<` - compiler searches first in pre-defined locations

#include <ESP8266WiFi.h>
#include <WiFiClientSecureBearSSL.h>
#include "Wifi-Connect.h"
#include "http-putsReq.h"

void setup()
{
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  Serial.println();

  wifiConnect_start();
}

void loop() {
    // wait for WiFi connection
    if ((WiFi.status() != WL_CONNECTED)) {
        delay(10000);
        return;
    }

    putsReq_Write("test");

    delay(10000);
}
