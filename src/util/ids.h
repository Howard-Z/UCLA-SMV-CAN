#ifndef UCLASMVCANIDS
#define UCLASMVCANIDS

enum devices {
    Bear_1,
    Bear_2,
    UI,
    HS,
    DAQ_Board
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

enum UIMessage {
    Blink_Left,
    Blink_Right,
    Reverse,
    Headlights,
    Wipers,
    Hazard,
    Button,
    Switch,
    Motor,
    Horn,
    DAQ_Button
};

enum HSMessage {
    Gyro_x,
    Gyro_y,
    Gyro_z,
    Accel,
    Magnetometer,
    Temp
};

enum DAQMessage {
    Longitude,
    Latitude,
    Speed
};

#endif