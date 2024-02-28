#include "S_CAN_RP2040.h"
#include "ids.h"
#include <string.h>
#include "id_chars.h"

CANBUS can(Bear_1);

void setup(void){
  Serial.begin(115200);
  
  delay(400); //for printing
}

void loop(){
  can.looper();
  if(can.isThere())
  {
    Serial.print("The data is: ");
    Serial.println(can.getData());
    Serial.print("The Hardware Type is: ");
    Serial.println(can.getHardware());
    Serial.print("The Data Type is: ");
    Serial.println(can.getDataType());
  }
  delay(20);
}