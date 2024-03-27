#ifndef _ID_STRINGS_
#define _ID_STRINGS_
#include <String>

const String devices[] = {
    "Bear_1",
    "Bear_2",
    "UI",
    "HS",
    "DAQ_Board"
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

const String UIMessage[] = {
    "Blink_Left",
    "Blink_Right",
    "Reverse",
    "Headlights",
    "Wipers",
    "Hazard",
    "Button",
    "Switch",
    "Motor",
    "DAQ_Button"
};

const String HSMessage[] = {
    "Gyro_x",
    "Gyro_y",
    "Gyro_z",
    "Accel",
    "Magnetometer",
    "Temp",
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
        return UIMessage[last];
        break;
    case 3:
        return HSMessage[last];
        break;
    case 4:
        return DAQMessage[last];
        break;
    }
    return "";
}
#endif