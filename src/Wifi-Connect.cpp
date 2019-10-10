#include <Arduino.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

int resetButtonPin = D5;
bool prevResetButtonState = false;

WiFiManager wifiManager;

void wifiConnect_autoConnect();

void wifiConnect_start()
{
    pinMode(resetButtonPin, INPUT_PULLUP);
    wifiConnect_autoConnect();
}

void wifiConnect_loop() {
  
  // wait for WiFi connection
  if ((WiFi.status() != WL_CONNECTED)) {
    delay(10000);
    return;
  }
  
  // flip state if button was pressed (changed from 0 -> 1)
  bool currButtonState = !digitalRead(resetButtonPin);

  Serial.printf("curr button: %s\n", currButtonState ?  "true" : "false");
  delay(1000);

  if (!prevResetButtonState && currButtonState) {
    Serial.println("Reset Buton Pressed");

    wifiManager.resetSettings();
    delay(1000);
    wifiConnect_autoConnect();
  }
  prevResetButtonState = currButtonState;
}

void wifiConnect_autoConnect()
{
  wifiManager.autoConnect("Sashko_Esp");

  Serial.printf("\n Connection established! IP address:\t ");
  Serial.println(WiFi.localIP());  // Send the IP address of the ESP8266 to the computer
}