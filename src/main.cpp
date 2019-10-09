// `<` - compiler searches first in pre-defined locations

#include <ESP8266WiFi.h>
#include <WiFiClientSecureBearSSL.h>
#include "Wifi-Connect.h"
#include "http-putsReq.h"

int ledPin = D1;
int buttonPin = D3;

void setup()
{
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  Serial.println();

  wifiConnect_start();

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
    // wait for WiFi connection
    if ((WiFi.status() != WL_CONNECTED)) {
        delay(10000);
        return;
    }

    delay(500);

    int buttonPressed = digitalRead(buttonPin) == LOW;
    digitalWrite(ledPin, buttonPressed);

    if(buttonPressed)
    {
        Serial.println("Pressed");
        putsReq_Write("test");
    }
}
