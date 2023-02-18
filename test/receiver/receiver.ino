#include "SMVcanbus.h"

CANBUS can;

void setup(void) {
  Serial.begin(115200); delay(400);
}

void loop() {
  can.getEvents();
  can.parser();
}