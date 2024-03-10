#include "SMVcanbus.h"

CANBUS can(Bear_1);
double data = 1.5;

void setup(void){
  Serial.begin(115200);
  
  delay(400); //for printing
}

void loop(){
  can.send(data, RPM);
  delay(500);
  data += 1.5;
  Serial.println("sent packet!");
}
