#include <String>

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

//const String all[]= {devices, motorMessage, jouleMessage, steeringMessage};