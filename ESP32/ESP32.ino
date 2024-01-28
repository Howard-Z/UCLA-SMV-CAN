// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>

void setup() {
  Serial.begin(9600);
  CAN.setPins(16, 17);
  while (!Serial);

  Serial.println("CAN Receiver Callback");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(1000000)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  // register the receive callback
  CAN.onReceive(onReceive);
}

void loop() {
  delay(10);
  // do nothing
  // Serial.print("Running");
}

void onReceive(int packetSize) {
  // received a packet
  Serial.print("Received ");

  Serial.println();
}

