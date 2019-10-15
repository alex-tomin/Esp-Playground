#include "Modules\WifiConnectModule.h"
#include "Modules\MDnsModule.h"
#include "PutsReqModule.h"
#include "WebServer.h"
#include "DhtReader.h"

DhtReader dhtReader;

std::array<BaseModule*, 4> modules{
    new WifiConnectModule(),
    new MDnsModule(),
    new PutsReqModule(dhtReader),
    new WebServer()
};

void setup() {
    Serial.begin(115200);

    for (BaseModule* module : modules) {
        module->setup();
  }
}

void loop() {
    for (BaseModule* module : modules) {
        module->loop();
    }
}
