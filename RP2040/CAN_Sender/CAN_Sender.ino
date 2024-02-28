#include "S_CAN_RP2040.h"
#include "ids.h"
#include <string.h>

#include <Adafruit_MCP2515.h>
// Adafruit_MCP2515 mcp(PIN_CAN_CS);

CANBUS can(Bear_1);
double data = 1.5;

void setup(void){
  Serial.begin(115200);
  can.begin();
  
  delay(400); //for printing
}

void loop(){
  can.send(data, RPM);
  delay(500);
  data += 1.5;
}