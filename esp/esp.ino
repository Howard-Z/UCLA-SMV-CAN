#include <WiFi.h>
#include <MQTT.h>
#include <CAN.h>
#include <String>
#include "smv_utils.h"

const char ssid[] = "2b||!2b";
const char pass[] = "UCLAengineering";
const int tx_pin = 17;
const int rx_pin = 16;

WiFiClient net;
MQTTClient client;


unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("arduino", "homeassistant", "gelaithah9ajiecohlahteigeizeeCuNeichoow5thaaquiPhaCh5quu6zoo0ael")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  //client.subscribe("/hello");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

// void onReceive(int packetSize) {
//   // received a packet
//   Serial.print("Received ");

//   // if (CAN.packetExtended()) {
//   //   Serial.print("extended ");
//   // }

//   // if (CAN.packetRtr()) {
//   //   // Remote transmission request, packet contains no data
//   //   Serial.print("RTR ");
//   // }

//   Serial.print("packet with id 0x");
//   Serial.print(CAN.packetId(), HEX);

//   if (CAN.packetRtr()) {
//     Serial.print(" and requested length ");
//     Serial.println(CAN.packetDlc());
//   } else {
//     Serial.print(" and length ");
//     Serial.println(packetSize);

//     // only print packet data for non-RTR packets
//     while (CAN.available()) {
//       Serial.print((char)CAN.read());
//     }
//     Serial.println();
//   }

//   Serial.println();
// }

void onReceive(int packetSize) {
  Serial.print("Received ");
  Serial.print("packet with id 0x");
  Serial.print(CAN.packetId(), HEX);
  Serial.print(" and length ");
  Serial.println(packetSize);
  DoubleCaster c;
  
  for(int i = 0; i < 8; i++)
  {
    if(CAN.available())
    {
      c.arr[i] = (char)CAN.read();
    }
    else
    {
      break;
    }
  }

  Serial.println();
  int first = getFirst(CAN.packetId());
  int last = getLast(CAN.packetId());
  String topic = "/";
  topic += readHardware(first) + "/";
  topic += readDataType(first, last);
  Serial.println("Topic is:" + topic);
  double data = c.num;
  char output[32];
  //dtostrf(data, 32, 8, output);
  //TODO Optimize the dtostrf() call
  client.publish(topic, "testing");
}

void setup() {
  CAN.setPins(rx_pin, tx_pin);
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  //WiFi.begin(ssid, NULL);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // by Arduino. You need to set the IP address directly.
  client.begin("192.168.1.130", net);
  client.onMessage(messageReceived);

  connect();

  Serial.print("Tx pin: ");
  Serial.println(tx_pin);
  Serial.print("Rx pin: ");
  Serial.println(rx_pin);

  if (!CAN.begin(1000000)) {
    Serial.println("Starting CAN failed!");
    while(1)
    {
      Serial.println("failing lmao");
    }
  }
  Serial.println("Started CAN!");

  // register the receive callback
  CAN.onReceive(onReceive);
}

void loop() {
  client.loop();

  if (!client.connected()) {
    connect();
  }
}