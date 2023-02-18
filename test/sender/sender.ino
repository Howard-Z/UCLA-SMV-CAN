#include "SMVcanbus.h"

CANBUS can;
void setup(void) {
  Serial.begin(115200); delay(400);
}

void loop() {
  can.getEvents();
  uint8_t arr[8] = {42, 69, 72, 18, 34, 56, 64, 92};
  uint16_t id = millis() % 10;
  Serial.println(id);
  can.send(arr, id);
  delay(1003);
}