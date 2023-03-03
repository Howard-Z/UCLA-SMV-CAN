#include "SMVcanbus.h"
#include "ids.h"
CANBUS can(Motor1);
void setup(void) {
  Serial.begin(115200); delay(400);
}

void loop() {
  can.getEvents();
  long long data = millis() % 7;
  can.send(data, Motor_Current);
  delay(1003);
}