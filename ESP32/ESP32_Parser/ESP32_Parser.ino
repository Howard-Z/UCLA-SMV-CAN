// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>
#include "smv_utils.h"

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

  if (packetSize) {
    int packetId = CAN.packetId();
    int first = getFirst(packetId);
    int last = getLast(packetId);

    // Print the 'first' and 'last' fields
    Serial.print("First: ");
    Serial.print(readHardware(first)); // Using the readHardware function to get the hardware type
    Serial.print(", Last: ");
    Serial.println(readDataType(first, last)); // Using the readDataType function to get the message type

    // Initialize a DoubleCaster union to hold the payload data
    DoubleCaster caster;

    // Read the payload byte by byte into the DoubleCaster array
    for (int i = 0; i < 8; i++) {
      caster.arr[i] = CAN.read();
    }

    // Now the double value is in caster.num
    Serial.print("Payload (as double): ");
    Serial.println(caster.num, 6); // Print the double value with 6 decimal places
  }
}

