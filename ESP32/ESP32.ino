#include <HardwareSerial.h>
#include <String>
#include "smv_utils.h"

HardwareSerial SerialPort(2); // use UART2
//giving the cast an initial value could cause bad data only for the first packet
DoubleCaster c = {0};
int first = 0;
int last = 0;
void setup()
{
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
 
}
void loop()
{
  bool write_flag = false;
  if (SerialPort.available())
  {
    write_flag = true;
    for(int i = 0; i < 8; i++)
    {
      c.arr[i] = SerialPort.read();
    }
    first = (int)SerialPort.read();
    last = (int)SerialPort.read();
  }
  if (write_flag)
  {
    Serial.println(c.num);
    Serial.println(first);
    Serial.println(last);
  }
}