#include "util/ids.h"
#if defined(ARDUINO_ADAFRUIT_FEATHER_RP2040_CAN)
   #include "rp2040/S_CAN_RP2040.h" //stupid 1
   
#else
    // Anything else, defaults!
   #include "teensy/S_CAN_Teensy.h"
#endif


