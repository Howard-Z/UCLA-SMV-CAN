#include "SMVcanbus.h"
#include "ids.h"
CANBUS can(Bear_1);
double data = 1.123;
void setup(void) {
  Serial.begin(115200); delay(400);
}

void loop() {
  can.send(data, RPM);
  Serial.println(data);
  data = data + 0.001;
  delay(20); //be careful with the speed that you send at, beware of out of order
}