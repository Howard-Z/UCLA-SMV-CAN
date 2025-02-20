#ifndef _UCLA_CAN_BUS_TEENSY_
#define _UCLA_CAN_BUS_TEENSY_

#include <FlexCAN_T4.h>
#include <String>
// #include "ids.h"


//Preface: this was designed for the can2.0 protocol, this will not work for anything else
class CANBUS{
    public:
        CANBUS(int id);
        void looper(); //if there is a message, process it
        void send(double message, int dataType);
        double getData(); //returns the data field
        String getHardware(){ return hardware; } //returns what hardware
        String getDataType(){ return dataType; } //returns what datatype
        bool isThere(); //boolen to check if there is a new message

    private:
        void callback(); //get message and set IDs
        int getID() {return msg.id;}
        CAN_message_t getMessage();//returns the raw CAN message
        uint32_t getFirst() { return first; } //get the first 4 bits
        uint32_t getLast() { return last; } //get the last 4 bits
        void setIDs(); //set the IDs based on the message
        int getIDField(int dataType); //calculates the ID field of the message to send
        FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can0; //initialize the CAN library
        CAN_message_t msg; //current message we are working with
        uint32_t first; //first 4 bits of the incoming ID
        uint32_t last; //last 4 bits of the incoming ID
        String hardware; //hardware type from the incoming message
        String dataType; //datatype from the incoming
        int device_id; //id of the device this is operating on
        bool isMessage; //flag for if there's a new message
};


#endif