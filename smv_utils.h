#ifndef UCLASMVUTILS
#define UCLASMVUTILS

#include <String>

enum devices {
    Bear_1,
    Bear_2,
    Power_Control,
    Steering_Wheel,
    DAQ
};
const String devices[] = {
    "Bear_1",
    "Bear_2",
    "Power_Control",
    "Steering_Wheel"
};

enum motorMessage {
    RPM,
    Motor_State,
    Cruise,
    M_Error_Status,
    Throttle,
    Brake,
    Meter_Count
};
const String motorMessage[] = {
    "RPM",
    "Motor_State",
    "Cruise",
    "Error_Status",
    "Throttle",
    "Brake",
    "Meter_Count"
};

enum powerMessage {
    Current,
    Voltage,
    Power,
    Energy,
    Temp1,
    Temp2,
    Temp3,
    P_Error_Status
};
const String powerMessage[] = {
    "Current",
    "Voltage",
    "Power",
    "Energy",
    "Temp_Sensor_1",
    "Temp_Sensor_2",
    "Temp_Sensor_3",
    "Error_Status"
};

enum steeringMessage{
    Switch_Encoding,
    S_Error_Status
};
const String steeringMessage[] = {
    "Switch_Encoding",
    "Error_Status"
};

enum DAQMessage {
    Longitude,
    Latitude,
    Speed
};

const String DAQMessage[] = {
    "Longitude",
    "Latitude",
    "Speed"
};

union DoubleCaster//this is for type casting between double and int array
{
    double num;
    uint8_t arr[8];
};

// int setIDs(int first, int last)
// {
//     first = msg.id << 21 >> 28; //greab the first 4 bits
//     last = msg.id << 27 >> 27; //grab the last 4 bits
//     readHardware();
//     readDataType();
// }

int getIDField(int first, int last)
{
    return (first << 7) + last;
}

int getFirst(int id)
{
    return id << 21 >> 28; 
}

int getLast(int id)
{
    return id << 27 >> 27; 
}

String readHardware(int first) {
    return devices[first];
}

String readDataType(int first, int last)
{
    switch (first)
    {
    case 0:
    case 1:
        return motorMessage[last];
        break;
    case 2:
        return powerMessage[last];
        break;
    case 3:
        return steeringMessage[last];
        break;
    }
    return "";
}
/* deprecated test devices
const String devices[] = {"Motor 1", "Motor 2", "Joulemeter", "Steering"};
const String motorMessage[] = {"RPM", "Motor Current", "Braking", "Temperature Sensor", "Ratcheting", "Cruising", "Steering Reading", "Hall Sensor State", "Hall Sensor Value", "Bus Voltage", "Gate Drive High/in (a, b, c) input logic", "Gate drive lod / sd (a, b, c) input logic", "PID setpoint", "PID current value"};
const String jouleMessage[] = {"Total Current", "Total kWh", "Current Power"};
const String steeringMessage[] = {"Headlights", "Left", "Right", "Horn"};


enum devices {Motor1, Motor2, Joulemeter, Steering};

enum motorMessage {RPM, Motor_Current, Braking, Temperature_Sensor, Ratcheting, Cruising,
            Steering_Reading, Hall_Sensor_State, Hall_Sensor_Value, Bus_Voltage, Gate_Drive_High,
            Gate_drive_lod, PID_setpoint, PID_current_value};

enum jouleMessage {Joule_Current, Total_kWh, Current_Power};

enum steeringMessage {Headlights, Left, Right, Horn};
*/
#endif