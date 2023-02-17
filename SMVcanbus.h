#ifndef _UCLA_SMV_CAN_BUS_
#define _UCLA_SMV_CAN_BUS_

#include <FlexCAN_T4.h>
#include <String>


//Preface: this was designed for the can2.0 protocol, this will not work for anything else
class CANBUS{
    public:
    CANBUS();
    void readFirst();
    void readLast();
    void parse();
    void setMsg();
    void send(uint8_t message, uint16_t id);
    void setIDs();
    String getHardware(){ return hardware; }
    String getDataType(){ return dataType; }
    CAN_message_t getMessage() { return msg; }
    void readHardware();
    void readDataType();
    private:
    CAN_message_t msg;
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can0;
    uint32_t first;
    uint32_t last;
    String hardware;
    String dataType;
};


#endif