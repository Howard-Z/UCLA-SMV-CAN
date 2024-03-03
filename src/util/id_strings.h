#ifndef _ID_STRINGS_
#define _ID_STRINGS_
#include <String>

const String devices[] = {
    "Bear_1",
    "Bear_2",
    "Power_Control",
    "Steering_Wheel"
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

const String steeringMessage[] = {
    "Switch_Encoding",
    "Error_Status"
};

const String DAQMessage[] = {
    "Longitude",
    "Latitude",
    "Speed"
};


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
#endif