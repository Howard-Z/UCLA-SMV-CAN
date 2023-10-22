#include <FlexCAN_T4.h>
#include <String>
#include "SMVcanbus.h"
#include "ids.h"

union DoubleCaster//this is for type casting between double and int array
{
    double num;
    uint8_t arr[8];
};

CANBUS::CANBUS(int id) //initialize the starting settings for CANBUS
{
    isMessage = false;
    Can0.begin();
    Can0.setBaudRate(1000000);
    Can0.setMaxMB(16);
    Can0.mailboxStatus();
    device_id = id;
    return;
}

void CANBUS::callback() //reads the message if there is one
{
    if(Can0.read(msg))
    {
        isMessage = true;
    }
}

void CANBUS::looper() //takes the message if there is a new one and processes it
{
    callback();
    if(isMessage) setIDs(); //sets the IDs
    return;
}

CAN_message_t CANBUS::getMessage() //tries to get the message is there is a new one else return the previous one
{
    if(isMessage) isMessage = false;
    return msg;
}


int CANBUS::getIDField(int DataType) //Bit shifting to get the ID Field
{
    return (device_id << 7) + DataType;
}

void CANBUS::send(double message, int dataType) //send message as float
{
    DoubleCaster c = {message}; //cast the message to byte array
    CAN_message_t mesg;
    mesg.id = getIDField(dataType); //set the id field
    for(int i = 0; i < 8; i++) //send the byte chunks
    {
        mesg.buf[i] = c.arr[i];
    }
    Can0.write(mesg);//send the message
}

double CANBUS::getData()
{
    CAN_message_t message = getMessage(); //get the received message
    DoubleCaster c; //convert back from an int array
    for(int i = 0; i < 8; i++)
    {
        c.arr[i] = message.buf[i];
    }
    return c.num;
}

// NOTE: When I discussed this with Kenson we agreed on this schema:
// The id field in a message contains 11 bits
// We are using ONLY the FIRST 4 and LAST 4 bits
// This leaves the middle 3 bits that are currently unused
// This is done because the payload is only 64 bytes and the double data type is 64 bytes

void CANBUS::setIDs()
{
    first = msg.id << 21 >> 28; //greab the first 4 bits
    last = msg.id << 27 >> 27; //grab the last 4 bits
    readHardware();
    readDataType();
}

bool CANBUS::isThere() //MUST BE USED TO CHECK FOR DUPLICATE MESSAGES
{
    return isMessage; //checks if there's a message available
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
        dataType = powerMessage[last];
        break;
    case 3:
        dataType = steeringMessage[last];
        break;
    }
}