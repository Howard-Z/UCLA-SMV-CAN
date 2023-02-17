#include "SMVcanbus.h"
CANBUS can;
void setup()
{
  
}

void loop()
{
  can.parse();
  can.send(4, 6);
  //can.looper();
  //can.setMsg();
}