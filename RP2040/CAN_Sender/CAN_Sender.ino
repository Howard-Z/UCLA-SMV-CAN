//This is all of our include stuff
//Feel free to ignore this! It's not important for us
#include <Adafruit_MCP2515.h>
#ifdef ESP8266
   #define CS_PIN    2
#elif defined(ESP32) && !defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2) && !defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S3)
   #define CS_PIN    14
#elif defined(TEENSYDUINO)
   #define CS_PIN    8
#elif defined(ARDUINO_STM32_FEATHER)
   #define CS_PIN    PC5
#elif defined(ARDUINO_NRF52832_FEATHER)
   #define CS_PIN    27
#elif defined(ARDUINO_MAX32620FTHR) || defined(ARDUINO_MAX32630FTHR)
   #define CS_PIN    P3_2
#elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040)
   #define CS_PIN    7
#elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040_CAN)
   #define CS_PIN    PIN_CAN_CS
#elif defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_RASPBERRY_PI_PICO_W) // PiCowbell CAN Bus
   #define CS_PIN    20
#else
   #define CS_PIN    5
#endif
#define CAN_BAUDRATE (500000)
Adafruit_MCP2515 mcp(CS_PIN);
//

#include "smv_utils.h"
DoubleCaster c = {0};
int led = LED_BUILTIN;
bool led_status = false;
//CODE BEGINS HERE
//Setup, also ignore!
void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  while(!Serial) delay(10);

  Serial.println("MCP2515 Sender test!");

  if (!mcp.begin(CAN_BAUDRATE)) {
    Serial.println("Error initializing MCP2515.");
    while(1) delay(10);
  }
  Serial.println("MCP2515 chip found");
}

void loop() {
  digitalWrite(led, led_status);
  led_status = !led_status;
  //Let's create a packet!
  int first = DAQ;
  int last = Speed;
  mcp.beginPacket(getIDField(first, last)); //Our ID
  for(int i = 0; i < 8; i++)
  {
    mcp.write(c.arr[i]);
  }
  // mcp.write('H'); //Add first byte of data (one char = one byte)
  // mcp.write('e'); //Second byte
  // mcp.write('l'); //Third byte
  // mcp.write('l'); //Fourth byte
  // mcp.write('o'); //Fifth byte
  mcp.endPacket(); //End and send our packet!

  Serial.println("Sent packet!");
  c.num += 1.5;

  //Add a delay of 1 second (so a message every second)
  delay(1000);
}

