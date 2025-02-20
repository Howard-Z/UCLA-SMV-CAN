#ifndef UCLASMVCANIDS
#define UCLASMVCANIDS

enum devices {
    Bear_1,
    UI,
    HS1,
    HS2,
    HS3,
    HS4,
    FC,
    Joule_H,
    Joule_L,
    Safety,
    DAQ_Board
};

enum motorMessage {
    Hall_velocity,
    Torque_motor,
    Current,
    Board_Temp,
    Motor_Temp,
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
    Accel_x,
    Accel_y,
    Accel_z,
    Pressure,
    Torque_HS
};

enum FCMessage {
    Gas,
    Brake
};

enum JouleMessage {
    Power
};

enum DAQMessage {
    Longitude,
    Latitude,
    Speed
};

#endif