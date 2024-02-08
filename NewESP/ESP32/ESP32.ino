#include <HardwareSerial.h>
#include <String>
#include "smv_utils.h"
#include <WiFi.h>
#include <MQTT.h>
#include <CAN.h>
const char ssid[] = "Hphone";
const char pass[] = "bruinsmv123";

WiFiClient net;
MQTTClient client;
int first = 0;
int last = 0;
// Initialize a DoubleCaster union to hold the payload data
DoubleCaster caster;
bool write_flag = false;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("ESP32", "smv", "E07Y7LwX5z")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");
}

String getTopic(int first, int last)
{
  String output = "/";
  output += readHardware(first) + "/";
  output += readDataType(first, last);
  return output;
}

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  client.begin("smv.seas.ucla.edu", net);

  CAN.setPins(16, 17);
  // start the CAN bus at 500 kbps
  if (!CAN.begin(1000E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  // register the receive callback
  CAN.onReceive(onReceive);
}
void loop()
{
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
  if(write_flag)
  {
    client.publish(getTopic(first, last), (String)caster.num);
    write_flag = false;
  }
}

void onReceive(int packetSize) {
  // received a packet
  Serial.print("Received ");

  Serial.println();

  if (packetSize) {
    int packetId = CAN.packetId();
    first = getFirst(packetId);
    last = getLast(packetId);

    // Print the 'first' and 'last' fields
    Serial.print("First: ");
    Serial.print(readHardware(first)); // Using the readHardware function to get the hardware type
    Serial.print(", Last: ");
    Serial.println(readDataType(first, last)); // Using the readDataType function to get the message type

    // Read the payload byte by byte into the DoubleCaster array
    for (int i = 0; i < 8; i++) {
      caster.arr[i] = CAN.read();
    }

    // Now the double value is in caster.num
    Serial.print("Payload (as double): ");
    Serial.println(caster.num, 6); // Print the double value with 6 decimal places
    write_flag = true;
  }
  

}