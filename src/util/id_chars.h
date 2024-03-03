#ifndef _ID_CHARS_
#define _ID_CHARS_

const char* devices[] = {
    "Bear_1",
    "Bear_2",
    "Power_Control",
    "Steering_Wheel"
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

const char* powerMessage[] = {
    "Current",
    "Voltage",
    "Power",
    "Energy",
    "Temp_Sensor_1",
    "Temp_Sensor_2",
    "Temp_Sensor_3",
    "Error_Status"
};

const char* steeringMessage[] = {
    "Switch_Encoding",
    "Error_Status"
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
        return powerMessage[last];
        break;
    case 3:
        return steeringMessage[last];
        break;
    }
    return "";
}

#endif