#include "SMVcanbus.h"

CANBUS can;
void setup(void) {
  Serial.begin(115200); delay(400);
}

void loop() {
  can.getEvents();
  long long data = 348957398;
  uint16_t id = millis() % 10;
  Serial.println(id);
  can.send(data, id);
  delay(1003);
}