#include "IntellisenseClang.h"
#include "Modules/WifiConnectModule.h"
#include "Modules/MDnsModule.h"
#include "PutsReqModule.h"
#include "WebServer.h"
#include "DhtReader.h"

DhtReader dhtReader;

std::array<BaseModule*, 3> modules{
    new WifiConnectModule(),
    new PutsReqModule(dhtReader),
    //new MDnsModule(),
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
