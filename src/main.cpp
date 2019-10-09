#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecureBearSSL.h>

const char* ssid     = "Sashko";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "12345679";     // The password of the Wi-Fi network

const uint8_t fingerprint[20] = {0x14, 0xe1, 0x0e, 0x30, 0x31, 0x9b, 0x12, 0xf3, 0xa0, 0x91, 0xe3, 0x61, 0xf2, 0x32, 0x39, 0x2a, 0xf2, 0xc6, 0x31, 0x33};
 
void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);             // Connect to the network

  Serial.printf("Connecting to: %s ...\n", ssid);

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.printf("\n Connection established! IP address:\t ");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

void loop() {
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setFingerprint(fingerprint);

    HTTPClient https;

    Serial.print("[HTTP] begin...\n");

    String urlBase = "https://putsreq.com/Alex?from=ESP&Today=9.Oct_9.50&time=";
    String url = urlBase+ millis();

    Serial.print(url);

    if (https.begin(*client, url)) {  // HTTP

      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(10000);
}
