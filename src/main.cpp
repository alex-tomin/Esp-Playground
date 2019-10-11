#include "Modules\WifiConnectModule.h"
#include "Modules\MDnsModule.h"
#include "PutsReqModule.h"

std::array<BaseModule*, 3> modules{
    new WifiConnectModule(),
    new MDnsModule(),
    new PutsReqModule(),
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
