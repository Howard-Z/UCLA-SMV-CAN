#ifndef _UCLA_SMV_CAN_BUS_
#define _UCLA_SMV_CAN_BUS_

#include <FlexCAN_T4.h>
#include <String>

CAN_message_t message;

void callBack(const CAN_message_t &msg) //setting the global message var
{
    message = msg;
}
//Preface: this was designed for the can2.0 protocol, this will not work for anything else
class CANBUS{
    public:
    CANBUS() //initialize the starting settings for CANBUS
    {
        FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can0;
        //Serial.begin(115200); delay(400);
        //pinMode(6, OUTPUT); digitalWrite(6, LOW); /* optional tranceiver enable pin */
        Can0.begin();
        Can0.setBaudRate(1000000);
        Can0.setMaxMB(16);
        Can0.enableFIFO();
        Can0.enableFIFOInterrupt();
        //Can0.onReceive(callBack);
        Can0.mailboxStatus();
        return;
    }
    void parse() //gets the mail and sets the global var to the message
    {
        Can0.events();
        Can0.onReceive(callBack);
        this->setMsg();
    }
    String read();
    void setMsg() //sets the message
    {
        this->msg = message;
    }
    void looper() //MANDATORY CALL In the loop: One Can0.events() needs to be in the loop
    {
        Can0.events();
    }
    void send(int message, int id) //send message
    {
        CAN_message_t msg;
        msg.id = id;
        for ( uint8_t i = 0; i < 8; i++ ) msg.buf[i] = i + 1; //currently set to giberish, fix later
        Can0.write(msg);
    }
    private:
    CAN_message_t msg;
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can0;
};

String CANBUS::read() {
    uint32_t first = msg.id << 21 >> 28; //greab the first 4 bits
    uint32_t last = msg.id << 28 >> 28; //grab the last 4 bits
    Serial.println("First: " + String(first));
    Serial.println("Last: " + String(last));

    switch(first) //case statement for identification
    {
        case 1:
        return "Motor";
        switch (last)
        {
            case 1:
            return "RPM";
            break;
        }
        break;
        case 2:
        return "b";
        break;
    }
    return "c";
}



#endif