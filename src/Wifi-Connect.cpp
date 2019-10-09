#include "Wifi-Connect.h"
#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>

const char* ssid     = "Sashko";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "12345679";     // The password of the Wi-Fi network

void wifiConnect_start()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password); // Connect to the network

    Serial.printf("Connecting to: %s ...\n", ssid);

    int i = 0;
    while (WiFi.status() != WL_CONNECTED) {  // Wait for the Wi-Fi to connect
        delay(1000);
        Serial.print(++i);
        Serial.print(' ');
    }

    Serial.printf("\n Connection established! IP address:\t ");
    Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer
}

void wifiConnect_loop()
{

}