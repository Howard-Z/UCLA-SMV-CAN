// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>

void setup() {
  Serial.begin(9600);
<<<<<<< Updated upstream
  CAN.setPins(16, 17);
=======
>>>>>>> Stashed changes
  while (!Serial);

  Serial.println("CAN Receiver Callback");

  // start the CAN bus at 500 kbps
<<<<<<< Updated upstream
  if (!CAN.begin(500000)) {
=======
  if (!CAN.begin(500E3)) {
>>>>>>> Stashed changes
    Serial.println("Starting CAN failed!");
    while (1);
  }

  // register the receive callback
  CAN.onReceive(onReceive);
}

void loop() {
<<<<<<< Updated upstream
  delay(10);
=======
>>>>>>> Stashed changes
  // do nothing
}

void onReceive(int packetSize) {
  // received a packet
  Serial.print("Received ");

<<<<<<< Updated upstream
  Serial.println();
}

=======
  if (CAN.packetExtended()) {
    Serial.print("extended ");
  }

  if (CAN.packetRtr()) {
    // Remote transmission request, packet contains no data
    Serial.print("RTR ");
  }

  Serial.print("packet with id 0x");
  Serial.print(CAN.packetId(), HEX);

  if (CAN.packetRtr()) {
    Serial.print(" and requested length ");
    Serial.println(CAN.packetDlc());
  } else {
    Serial.print(" and length ");
    Serial.println(packetSize);

    // only print packet data for non-RTR packets
    while (CAN.available()) {
      Serial.print((char)CAN.read());
    }
    Serial.println();
  }

  Serial.println();
}
>>>>>>> Stashed changes
