#include "Modules\WifiConnectModule.h"
#include "Modules\MDnsModule.h"
#include "PutsReqModule.h"
#include "WebServer.h"

std::array<BaseModule*, 4> modules{
    new WifiConnectModule(),
    new MDnsModule(),
    new PutsReqModule(),
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
