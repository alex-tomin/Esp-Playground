#include "Modules\WifiConnectModule.h"
#include "Modules\MDnsModule.h"
#include "PutsReqModule.h"

const int ModulesCount = 3;
BaseModule *modules[ModulesCount];  //TODO: list?
WifiConnectModule wifiConnect;
MDnsModule mDnsModule;
PutsReqModule putsReqModule;

void setup() {
  modules[0] = &wifiConnect;
  modules[1] = &mDnsModule;
  modules[2] = &putsReqModule;

  Serial.begin(115200);

  for (int i = 0; i < ModulesCount; i++) {
      modules[i]->setup();
  }
}

void loop() {
    for (int i = 0; i < ModulesCount; i++) {
        modules[i]->loop();
    }
}
