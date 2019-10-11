#ifndef NET_MDNS /* guard */
#define NET_MDNS

#include <ESP8266mDNS.h>
#include "BaseModule.h"

class MDnsModule: public BaseModule {

    String moduleName = "esp8266";

   public:
    MDnsModule() {}

    void setup() {
        if (!MDNS.begin(moduleName)) { // Start the mDNS responder for esp8266.local
            Serial.println("Error setting up MDNS responder!");
        }
        Serial.println("mDNS responder started");
    }

    void loop() {}
};


#endif