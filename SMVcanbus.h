#ifndef _UCLA_SMV_CAN_BUS_
#define _UCLA_SMV_CAN_BUS_

#include <FlexCAN_T4.h>
#include <String>


//Preface: this was designed for the can2.0 protocol, this will not work for anything else
class CANBUS{
    public:
        CANBUS();
        void getEvents(); //This function must be present in the loop function to receive CAN messages
        //void parse();
        void parser(const CAN_message_t& mesg); //if there is a message, process it
        void send(uint8_t* message, uint16_t id); //sends a message (takes in an 8 element array of uint8_t)
        void setIDs(); //set the IDs based on the message
        uint32_t getFirst() { return first; } //get the first 4 bits
        uint32_t getLast() { return last; } //get the last 4 bits
        String getHardware(){ return hardware; } //returns what hardware
        String getDataType(){ return dataType; } //returns what datatype
        CAN_message_t getMessage() { return msg; } //returns the raw CAN message
        bool isThere(); //boolen to check if there is a new message
        void readHardware(); //use the first 4 bits to determine hardware
        void readDataType();//use the whole ID to determine data type
    private:
        FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can0; //initialize the CAN library
        CAN_message_t msg; //current message we are working with
        uint32_t first; //first 4 bits of the ID
        uint32_t last; //last 4 bits of the ID
        String hardware;
        String dataType;
};


#endif