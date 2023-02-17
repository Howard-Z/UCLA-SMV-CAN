#include "SMVcanbus.h"
CANBUS can;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  can.parse();
  //Serial.println(can.getHardware());
  Serial.println("test");
  CAN_message_t msg = can.getMessage();
  Serial.println(msg.buf[0], DEC);
}