// `<` - compiler searches first in pre-defined locations

#include <ESP8266WiFi.h>
#include <WiFiClientSecureBearSSL.h>
#include "Wifi-Connect.h"
#include "http-putsReq.h"

int ledPin = D1;
int buttonPin = D3;
bool prevButtonState = false;
bool perfomOperation = false;

void setup() {
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

  // flip state if button was pressed (changed from 1 -> 0)
  bool currButtonState = !digitalRead(buttonPin);
  if (!prevButtonState && currButtonState) {
    Serial.println("Pressed");
    perfomOperation = !perfomOperation;
  }
  prevButtonState = currButtonState;
  
  digitalWrite(ledPin, perfomOperation);

  if (perfomOperation && (millis() % 1000)) {
    putsReq_Write("test");
  }

}
