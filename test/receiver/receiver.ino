#include "SMVcanbus.h"

CANBUS can;

void setup(void) {
  Serial.begin(115200); delay(400);
}

void loop() {
  can.getEvents();
  can.parser();
  CAN_message_t mesg = can.getMessage();
  Serial.print("The Buffer is: ");
  for ( uint8_t i = 0; i < 8; i++ )
  {
    
    Serial.print(mesg.buf[i], DEC);
  }
  Serial.print(" The ID is: ");
  Serial.print(mesg.id);
  Serial.println();
}