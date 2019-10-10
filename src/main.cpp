// `<` - compiler searches first in pre-defined locations

#include <ESP8266WiFi.h>

#include "Wifi-Connect.h"
#include "http-putsReq.h"
#include "net-mDns.h"

int ledPin = D1;
int buttonPin = D3;
bool prevButtonState = false;
bool perfomOperation = false;

void setup() {
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  Serial.println();

  wifiConnect_start();
  mDns_Setup();

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  wifiConnect_loop();

  // flip state if button was pressed (changed from 0 -> 1)
  bool currButtonState = !digitalRead(buttonPin);
  if (!prevButtonState && currButtonState) {
    perfomOperation = !perfomOperation;
    Serial.printf("Perform Operation: %s\n", perfomOperation ?  "true" : "false");
  }
  prevButtonState = currButtonState;
  
  digitalWrite(ledPin, perfomOperation);

  if (perfomOperation && (millis() % 1000)) {
    putsReq_Write("test");
  }
}
