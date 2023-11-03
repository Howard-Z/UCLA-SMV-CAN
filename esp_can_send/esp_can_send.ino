// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>
#include "smv_utils.h"

double num = 239847.167;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("CAN Sender");

  // start the CAN bus at 500 kbps
  CAN.setPins(16, 17);
  if (!CAN.begin(1000E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending packet ... ");
  int id_field = getIDField(Bear_1, RPM);
  DoubleCaster c;
  c.num = num;
  CAN.beginPacket(id_field);
  //CAN.write('h');
  CAN.write(c.arr, 8);
  CAN.endPacket();

  //num += 1.5;
  Serial.println("done");

  delay(1000);
}