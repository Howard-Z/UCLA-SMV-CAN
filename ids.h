#ifndef UCLASMVCANIDS
#define UCLASMVCANIDS

#include <String>

enum devices {
    Bear_1,
    Bear_2,
    Power_Control,
    Steering_Wheel,
    DAQ
};
const String devices[] = {
    "Bear 1",
    "Bear 2",
    "Power Control",
    "Steering Wheel"
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
    "Motor State",
    "Cruise",
    "Error Status",
    "Throttle",
    "Brake",
    "Meter Count"
};

enum powerMessage {
    Current,
    Voltage,
    Power,
    Energy,
    T1,
    T2,
    T3,
    P_Error_Status
};
const String powerMessage[] = {
    "Current",
    "Voltage",
    "Power",
    "Energy",
    "Temp Sensor 1",
    "Temp Sensor 2",
    "Temp Sensor 3",
    "Error Status"
};

enum steeringMessage{
    Switch_Encoding,
    S_Error_Status
};
const String steeringMessage[] = {
    "Switch Encoding",
    "Error Status"
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