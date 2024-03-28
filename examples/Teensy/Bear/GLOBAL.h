/* Code Parameters */
#define PWM_FREQ 24000
#define MIN_THROTTLE 0
#define MAX_THROTTLE 1013
#define MOTOR_OFF_THROTTLE 5
#define MAX_START_SPEED 10
#define MIN_SPEED 0
#define MAX_SPEED 240
// TO DO: why it so jerky above 252?  - this is cause of low bootstrap voltage, see sim and use vcc=14 (test 15)
#define MAX_RPM 500//450
#define TIMER_INTERVAL_MS 50
#define POLE_COUNT 46 // TO DO: CHECK this with motor spec sheet
#define RAMP_SPEED 1
// TO DO: make MAX_RPM dependent on battery system

/* Pin Assignments */
#define HALL_A A1
#define HALL_B A2
#define HALL_C A3
//#define THROTTLE A0 // Throttle from dual controller
#define THROTTLE A4 // Throttle directly from sensor
#define LED_1 13 // On-teensy LED
#define LED_2 3 // Controllable LED
#define CRUISE 12
#define IN_A 6
#define IN_B 8
#define IN_C 10
#define SD_A 7
#define SD_B 9
#define SD_C 11
