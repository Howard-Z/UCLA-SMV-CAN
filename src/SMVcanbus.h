#include "util/ids.h"

#if defined(ARDUINO_ADAFRUIT_FEATHER_RP2040_CAN)
   #include "rp2040/S_CAN_RP2040.h"

#elif defined(ESP32)
   #include "lib/CAN.h"
   #include "util/smv_utils.h"
   #include "util/id_strings.h"
   #include "util/ids.h"

#else
    // Anything else, defaults!
   #include "teensy/S_CAN_Teensy.h"
#endif