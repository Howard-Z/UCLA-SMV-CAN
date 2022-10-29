#ifndef _UCLA_SMV_CAN_BUS_
#define _UCLA_SMV_CAN_BUS_

#include <FlexCAN_T4.h> //this needs to be replaced at some point
#include <String> //might not be needed in arduino ide
using namespace std; //also should take out this line

//Preface: this was designed for the can2.0 protocol, this will not work for anything else
class SMVCAN{
    SMVCAN()
    {
        FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can0;
    }
    public:
        void canSniff(const CAN_message_t &msg);

};


void canSniff(const CAN_message_t &msg) {
    uint32_t first = msg.id << 21 >> 28;
    uint32_t last = msg.id << 28 >> 28;
    Serial.println("First: " + String(first));
    Serial.println("Last: " + String(last));

    switch(first)
    {
        case 1:
        Serial.print("Motor");
        switch (last)
        {
            case 1:
            Serial.println("RPM");
            break;
        }
        break;
        case 2:
        Serial.println("b");
        break;
    }
}

#endif