#include <FlexCAN_T4.h>
#include <String>
#include "SMVcanbus.h"
#include "ids.h"


namespace SMVcanbus //we use a name space to keep track of the message that the global callback function produces.
{
    CAN_message_t msg; //the global message variable
    bool isMessage = false; //is there a new message available

    void callback(const CAN_message_t& mesg)
    {
        msg = mesg; //setting the message
        isMessage = true; //setting the flag that there is a message available
        //Serial.println("calling back"); //debugging
    }
}

void testCallback(const CAN_message_t& mesg) //debugging test callback function
{
    Serial.println("there is an event");
}


CANBUS::CANBUS() //initialize the starting settings for CANBUS
{
    //FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can0; //not actually needed bc it's taken care of in the constructor
    Can0.begin();
    Can0.setBaudRate(1000000);
    Can0.setMaxMB(16);
    Can0.enableFIFO();
    Can0.enableFIFOInterrupt();
    Can0.onReceive(SMVcanbus::callback);
    //Can0.onReceive(testCallback); //debugging
    Can0.mailboxStatus();
    return;
}

void CANBUS::getEvents() //see's if there's a new message, if there is, run the call back function
{
    Can0.events();
}

void CANBUS::parser() //takes the message if there is a new one and processes it
{
    if (SMVcanbus::isMessage)
    {
        this->msg = SMVcanbus::msg; //sets the current message we are working with
        SMVcanbus::isMessage = false; //changes the boolean to say that there is no new message anymore
        setIDs(); //sets the IDs
    }
    return;
}
/* //old parse function
void CANBUS::parse() //gets the mail and sets the global var to the message
{
    Can0.events();
    this->setMsg();
    this->setIDs();
    this->readHardware();
    this->readDataType();
}*/


void CANBUS::send(uint8_t* message, uint16_t id) //send message (potential problem if you try and send faster than 1 per 200 ms
{
    CAN_message_t mesg;
    mesg.id = id; //set the id field
    for (int i = 0; i < 8; i++) //buffer is broken down into 8 uint8_t sections, ,loop through them and set it
    {
        mesg.buf[i] = message[i];
    }
    Can0.write(mesg);//send the message
}

void CANBUS::setIDs()
{
    first = msg.id << 21 >> 28; //greab the first 4 bits
    last = msg.id << 27 >> 27; //grab the last 4 bits
}

bool CANBUS::isThere()
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