#if defined(ARDUINO_ADAFRUIT_FEATHER_RP2040_CAN)
#include "S_CAN_RP2040.h"
#include "../util/smv_utils.h"
#include <string.h>
#include "../util/id_chars.h"
#define CAN_BAUDRATE (500000)

#include <Adafruit_MCP2515.h>

CANBUS::CANBUS(int id) : mcp(PIN_CAN_CS)//initialize the starting settings for CANBUS
{
    isMessage = false;
    device_id = id;
    return;
}


void CANBUS::begin()
{
    mcp.begin(CAN_BAUDRATE);
    return;
}

void CANBUS::setIDs(int id_field)
{
    first = id_field << 21 >> 28; //greab the first 4 bits
    last = id_field << 27 >> 27; //grab the last 4 bits
    strcpy(hardware, readHardware(first));
    strcpy(dataType, readDataType(first, last));
    // hardware = readHardware(first);
    // dataType = readDataType(first, last);
}

void CANBUS::looper()
{
    if(mcp.parsePacket())
    {
        DoubleCaster c;
        setIDs(mcp.packetId());
        for(int i = 0; i < 8; i++)
        {
            c.arr[i] = (char)mcp.read();
        }
        isMessage = true;
        data = c.num;
    }
}


void CANBUS::send(double message, int dataType) //send message as float
{
    DoubleCaster c = {message}; //cast the message to byte array
    mcp.beginPacket(getIDField(device_id, dataType)); //Our ID
    for(int i = 0; i < 8; i++)
    {
        mcp.write(c.arr[i]);
    }
    mcp.endPacket();
    return;
}

double CANBUS::getData()
{
    isMessage = false;
    return data;
}

#endif