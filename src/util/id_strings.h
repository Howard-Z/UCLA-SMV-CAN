#ifndef _ID_STRINGS_
#define _ID_STRINGS_
#include <String>

const String devices[] = {
    "Bear_1",
    "UI",
    "HS1",
    "HS2",
    "HS3",
    "HS4",
    "FC",
    "Joule_H",
    "Joule_L",
    "Safety",
    "DAQ_Board",
};


const String motorMessage[] = {
    "Hall_velocity",
    "Torque_motor",
    "Current",
    "Board_Temp",
    "Motor_Temp",
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
    "Horn",
    "DAQ_Button",
};

const String HSMessage[] = {
    "Gyro_x",
    "Gyro_y",
    "Gyro_z",
    "Accel_x",
    "Accel_y",
    "Accel_z",
    "Pressure",
    "Torque_HS",
};

const String FrontcenterMessage[] = {
    "Gas",
    "Brake",
};

const String JoulemeterMessage[] = {
    "Power",
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