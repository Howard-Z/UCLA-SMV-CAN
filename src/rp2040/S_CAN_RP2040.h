#ifndef _UCLA_SMV_CAN_BUS_RP2040_
#define _UCLA_SMV_CAN_BUS_RP2040_

#include <Adafruit_MCP2515.h>

//Preface: this was designed for the can2.0 protocol, this will not work for anything else
class CANBUS{
    public:
        // CANBUS(int id, Adafruit_MCP2515* mcp);
        CANBUS(int id);
        void begin();
        void looper(); //if there is a message, process it
        void send(double message, int dataType);
        double getData(); //returns the data field
        char* getHardware(){ return hardware; } //returns what hardware (of the last message)
        char* getDataType(){ return dataType; } //returns what datatype (of the last message)
        bool isThere(){ return isMessage; } //boolen to check if there is a new message
    private:
        void setIDs(int id_field); //set the IDs based on the message
        uint32_t first; //first 4 bits of the incoming ID
        uint32_t last; //last 4 bits of the incoming ID
        double data; //the data field of the last message
        char hardware[20]; //hardware type from the incoming message
        char dataType[20]; //datatype from the incoming
        int device_id; //id of the device this is operating on
        bool isMessage; //flag for if there's a new message
        Adafruit_MCP2515 mcp;
};

#endif