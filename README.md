# Welcome to the ESP32-Code branch

This branch is for the 2023-2024 year where we have transitioned to using RP2040s and ESP32s

## Setup
First clone the repo into the library folder of Arduino IDE on your device

Look at the example code in the folders for how it all works
NOTE: needs optimization and better data safety

## Wiring guide
From RP2040 to RP2040
* L goes to L
* H goes to H
* GND goes to GND

From RP2040 to ESP32
* THEY MUST SHARE A COMMON GROUND
* RP2040 TX to ESP32 RX
* RP2040 RX to ESP32 TX

NOTE: Each RP2040 and ESP32 needs their own power supply, for some reason they do not like sharing the same 5v rail.