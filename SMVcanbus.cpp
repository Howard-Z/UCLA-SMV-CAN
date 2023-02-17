#include <FlexCAN_T4.h>
#include <String>
#include "SMVcanbus.h"
#include "ids.h"

CAN_message_t globalMessage;

void callBack(const CAN_message_t &msg) //setting the global message var
{
    globalMessage = msg;
}

CANBUS::CANBUS() //initialize the starting settings for CANBUS
{
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can0;
    Can0.begin();
    Can0.setBaudRate(1000000);
    Can0.setMaxMB(16);
    Can0.enableFIFO();
    Can0.enableFIFOInterrupt();
    Can0.mailboxStatus();
    return;
}

void CANBUS::parse() //gets the mail and sets the global var to the message
{
    Can0.events();
    Can0.onReceive(callBack);
    this->setMsg();
    this->setIDs();
    this->readHardware();
    this->readDataType();
}

void CANBUS::setMsg() //sets the message
{
    this->msg = globalMessage;
}

void CANBUS::send(uint8_t message, uint16_t id) //send message
{
    CAN_message_t msg;
    msg.id = id;
    msg.buf[0] = message;
    Can0.write(msg);
}

void CANBUS::setIDs()
{
    first = msg.id << 21 >> 28; //greab the first 4 bits
    last = msg.id << 27 >> 27; //grab the last 4 bits
}

void CANBUS::readHardware() {
    hardware = devices[first];
}

void CANBUS::readDataType()
{
    switch (first)
    {
        case 0:
        case 1:
            dataType = motorMessage[last];
            break;
        case 2:
            dataType = jouleMessage[last];
            break;
        case 3:
            dataType = steeringMessage[last];
            break;
    }
}