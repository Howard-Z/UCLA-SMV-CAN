//#include <FlexCAN_T4.h>
#include "SMVcanbus.h"
//FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can0;
CANBUS can;
void setup(void) {
  Serial.begin(115200); delay(400);

  // pinMode(6, OUTPUT); digitalWrite(6, LOW); /* optional tranceiver enable pin */
  // Can0.begin();
  // Can0.setBaudRate(1000000);
  // Can0.setMaxMB(16);
  // Can0.enableFIFO();
  // Can0.enableFIFOInterrupt();
  // Can0.onReceive(canSniff);
  // Can0.mailboxStatus();
}

// void canSniff(const CAN_message_t &msg) {
//   Serial.print("MB "); Serial.print(msg.mb);
//   Serial.print("  OVERRUN: "); Serial.print(msg.flags.overrun);
//   Serial.print("  LEN: "); Serial.print(msg.len);
//   Serial.print(" EXT: "); Serial.print(msg.flags.extended);
//   Serial.print(" TS: "); Serial.print(msg.timestamp);
//   Serial.print(" ID: "); Serial.print(msg.id, HEX);
//   Serial.print(" Buffer: ");
//   for ( uint8_t i = 0; i < msg.len; i++ ) {
//     Serial.print(msg.buf[i], HEX); Serial.print(" ");
//   } Serial.println();
// }

void loop() {
  //Can0.events();
  can.getEvents();
  static uint32_t timeout = millis();
  if ( millis() - timeout > 200 && can.isThere()) {
    can.parser();
    CAN_message_t mesg = can.getMessage();
    for ( uint8_t i = 0; i < 8; i++ )
    {
      Serial.print(mesg.buf[i], DEC);
      Serial.println();
    }
    timeout = millis();
  }

}