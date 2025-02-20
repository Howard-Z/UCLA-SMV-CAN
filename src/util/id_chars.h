#ifndef _ID_CHARS_
#define _ID_CHARS_

const char* devices[] = {
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


const char* motorMessage[] = {
    "Hall_velocity",
    "Torque_motor",
    "Current",
    "Board_Temp",
    "Motor_Temp",
};

const char* UIMessage[] = {
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

const char* HSMessage[] = {
    "Gyro_x",
    "Gyro_y",
    "Gyro_z",
    "Accel_x",
    "Accel_y",
    "Accel_z",
    "Pressure",
    "Torque_HS",
};

const char* FrontcenterMessage[] = {
    "Gas",
    "Brake",
};

const char* JoulemeterMessage[] = {
    "Power",
};

const char* DAQMessage[] = {
    "Longitude",
    "Latitude",
    "Speed"
};

const char* readHardware(int first) {
    return devices[first];
}

const char* readDataType(int first, int last)
{
    switch (first)
    {
    case 0:
        return motorMessage[last];
        break;
    case 1:
        return UIMessage[last];
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        return HSMessage[last];
        break;
    case 6:
        return FrontcenterMessage[last];
        break;
    case 7:
    case 8:
        return JoulemeterMessage[last];
        break;
    case 9:
        return "Safety";
        break;
    case 10:
        return DAQMessage[last];
        break;
    }
    return "";
}

#endif