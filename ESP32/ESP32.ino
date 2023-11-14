#include <HardwareSerial.h>
HardwareSerial SerialPort(2); // use UART2
char number  = ' ';
void setup()
{
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
 
}
void loop()
{
  if (SerialPort.available())
  {
    char number = SerialPort.read();
    Serial.println(number);
 
  }
}