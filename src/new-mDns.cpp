#include <ESP8266mDNS.h>


void mDns_Setup(){
    if (!MDNS.begin("esp8266")) { // Start the mDNS responder for esp8266.local
      Serial.println("Error setting up MDNS responder!");
  }

  Serial.println("mDNS responder started");
}