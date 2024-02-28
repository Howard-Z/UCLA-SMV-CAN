#ifndef UCLASMVCANIDS
#define UCLASMVCANIDS

enum devices {
    Bear_1,
    Bear_2,
    Power_Control,
    Steering_Wheel,
    DAQ
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


enum steeringMessage{
    Switch_Encoding,
    S_Error_Status
};


enum DAQMessage {
    Longitude,
    Latitude,
    Speed
};

#endif