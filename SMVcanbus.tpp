#include <FlexCAN_T4.h>
#include <String>
#include "SMVcanbus.h"

void callBack(const CAN_message_t &msg) //setting the global message var
{
    message = msg;
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
    this->msg = message;
}

void CANBUS::send(uint64_t message, uint16_t id) //send message
{
    CAN_message_t msg;
    msg.id = id;
    msg.buf = message;
    Can0.write(msg);
}

void CANBUS::setIDs()
{
    first = msg.id << 21 >> 28; //greab the first 4 bits
    last = msg.id << 28 >> 28; //grab the last 4 bits
}

void CANBUS::readHardware() {
    switch(first) //case statement for identification
    {
        case 1:
            hardware = "Motor";
            break;
        case 2:
            hardware= "b";
            break;
    }
}

void CANBUS::readDataType()
{
    switch (last)
    {
        case 1:
            dataType = "RPM";
            break;
    }
}