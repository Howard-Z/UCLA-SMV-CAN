#include <FlexCAN_T4.h>
#include <String>
#include "SMVcanbus.h"
#include "ids.h"


namespace SMVcanbus //we use a name space to keep track of the message that the global callback function produces.
{
    CAN_message_t msg; //the global message variable
    static bool isMessage = false; //is there a new message available

    void callback(const CAN_message_t& mesg)
    {
        msg = mesg; //setting the message
        isMessage = true; //setting the flag that there is a message available
        //Serial.println(msg.timestamp); //debugging
    }
}

void testCallback(const CAN_message_t& mesg) //debugging test callback function
{
    Serial.println("there is an event");
}

union DoubleCaster//this is for type casting between double and int array
{
    double num;
    uint8_t arr[8];
};

CANBUS::CANBUS(int id) //initialize the starting settings for CANBUS
{
    //FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can0; //not actually needed bc it's taken care of in the constructor
    Can0.begin();
    Can0.setBaudRate(1000000);
    Can0.setMaxMB(16);
    //Can0.enableFIFO();
    //Can0.enableFIFOInterrupt();
    Can0.onReceive(SMVcanbus::callback);
    //Can0.onReceive(testCallback); //debugging
    Can0.mailboxStatus();
    device_id = id;
    return;
}

void CANBUS::getEvents() //see's if there's a new message, if there is, run the call back function
{
    Can0.events();
}

void CANBUS::parse() //takes the message if there is a new one and processes it
{
    this->msg = SMVcanbus::msg; //sets the current message we are working with
    setIDs(); //sets the IDs
    return;
}

CAN_message_t CANBUS::getMessage() //tries to get the message is there is a new one else return the previous one
{
    if(SMVcanbus::isMessage)
    {
        SMVcanbus::isMessage = false;
        return SMVcanbus::msg;
    }
    else{
        return msg;
    }
}

long long CANBUS::ArrToInt(uint8_t* arr) //converting btye array to integer
{
    long long output = 0;
    for (int i = 0; i < 8; i++)
    {
        output <<= 8;
        output += arr[i];
    }
    return output;
}


void CANBUS::IntToArr(long long num, uint8_t* arr) //converting integer to byte array
{
    for (int i = 0; i < 8; i++)
    {
        arr[8 - i - 1] = (uint8_t)(num & 0xFF);
        num >>= 8;
    }
}

int CANBUS::getIDField(int DataType)
{
    return (device_id << 7) + DataType;
}
// void CANBUS::send(long long message, int dataType) //send message as int
// {
//     CAN_message_t mesg;
//     mesg.id = getIDField(dataType); //set the id field
//     uint8_t arr[8];
//     IntToArr(message, arr);
//     for(int i = 0; i < 8; i++)
//     {
//         mesg.buf[i] = arr[i];
//     }
//     Can0.write(mesg);//send the message
// }

void CANBUS::send(double message, int dataType) //send message as float
{
    DoubleCaster c = {message};
    CAN_message_t mesg;
    mesg.id = getIDField(dataType); //set the id field
    for(int i = 0; i < 8; i++)
    {
        mesg.buf[i] = c.arr[i];
    }
    Can0.write(mesg);//send the message
}

// long long CANBUS::getData() //return the buffer in long long form
// {
//     CAN_message_t message = getMessage();
//     return ArrToInt(message.buf);
// }

double CANBUS::getData()
{
    CAN_message_t message = getMessage();
    DoubleCaster c;
    for(int i = 0; i < 8; i++)
    {
        c.arr[i] = message.buf[i];
    }
    return c.num;
}
void CANBUS::setIDs()
{
    first = msg.id << 21 >> 28; //greab the first 4 bits
    last = msg.id << 27 >> 27; //grab the last 4 bits
    readHardware();
    readDataType();
}

bool CANBUS::isThere() //MUST BE USED TO CHECK FOR DUPLICATE MESSAGES
{
    return SMVcanbus::isMessage; //checks if there's a message available
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