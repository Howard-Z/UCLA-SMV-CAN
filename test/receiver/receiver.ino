#include "SMVcanbus.h"

CANBUS can;

void setup(void) {
  Serial.begin(115200); delay(400);
}

void loop() {
  can.getEvents();
  can.parse();
  if(can.isThere())
  {
    Serial.print("The data is: ");
    Serial.println(can.getData());
    Serial.print(" The ID is: ");
    Serial.print(can.getID());
    Serial.println();
  }
}