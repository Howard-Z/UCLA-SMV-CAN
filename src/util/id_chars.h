#ifndef _ID_CHARS_
#define _ID_CHARS_

const char* devices[] = {
    "Bear_1",
    "Bear_2",
    "UI",
    "HS",
    "DAQ_Board"
};


const char* motorMessage[] = {
    "RPM",
    "Motor_State",
    "Cruise",
    "Error_Status",
    "Throttle",
    "Brake",
    "Meter_Count"
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
    "DAQ_Button"
};

const char* HSMessage[] = {
    "Gyro_x",
    "Gyro_y",
    "Gyro_z",
    "Accel",
    "Magnetometer",
    "Temp",
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