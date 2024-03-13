# UCLA SMV CAN Bus Library
This is the UCLA Bruin Racing SMV CAN Bus communication library for the ESP32, Teensy 4, and RP2040 CAN. This guide **DOES NOT** cover wiring guides.

## Hardware Overview
For this library we are using 3 different microcontrollers
* ESP32
    * The DAQ Specific board for uploading data to the cloud
* Teensy 4
    * Legacy code from the 2022-2023 year (see commit: `a04540d9ed8a43bf7a0ba898fdd3b3a5d62bfa2f`)
* RP2040 CAN
    * The newest edition of microcontrollers

**Note that: EACH controller has their own specific implementation** so follow the appropriate section of the guide depending on your hardware.

### Teensy 4
For the Teensy 4, we will be using the FlexCAN_T4 library

#### Installing Prerequisites

We rely on the FlexCAN_T4 library that should already be included when you set up Arduino IDE with the Teensy boards, but if you don't have it installed you can find it here:

If you don't have the FlexCAN_T4 library, you must install it by adding it into your library folder.

Go to https://github.com/tonton81/FlexCAN_T4 or click [here](https://github.com/tonton81/FlexCAN_T4) and clone the repository into Arduino IDE's library folder (see [Note 1](#1.-Location-of-Library-Folder) for help)

You must also install this current library into the libraries folder.

### RP2040 CAN
For the Adafruit RP2040 CAN Bus Feather MCP2515.

#### Installing Prerequisites

Following the Adafruit guide found [here](https://learn.adafruit.com/adafruit-rp2040-can-bus-feather/can-bus-test-2), you need to install the `Adafruit MCP2515` library from the library manager that is **built-in** to Arduino IDE.

Afterwards you must install this library by cloning it into Arduino IDE's library folder (see [Note 1](#1.-Location-of-Library-Folder) for help)

### ESP32
This is mainly for DAQ team members to develop since this is a one off board for the car. See the examples folder for actual implementation

## Using the Library

To include the library in your sketch you can add the following line:
`include "SMVcanbus.h"`

### Initializing the CANBUS object

To begin using the CAN Bus, you must initialize a canbus object

`CANBUS can(device_id);`

You can replace `device_id` with the enum name of your device from the [address book](#Address-Book), for example: `CANBUS can(Bear_1);`

### Sending Data:
Let's take a look at one of the example sketches
```
#include "SMVcanbus.h"

CANBUS can(Bear_1);
double data = 1.5;

void setup(void){
  Serial.begin(115200);
  can.begin(); //YOU ONLY NEED THIS LINE FOR RP2040
  
  delay(400); //for printing
}

void loop(){
  can.send(data, RPM);
  delay(500); //be aware of how fast you send as not to overwhelm the system
  data += 1.5;
  Serial.println("sent packet!");
}
```

* First we are including the library `#include "SMVcanbus.h`

* Then we initialize the CANBUS object with device id of the bear `CANBUS can(Bear_1);`

* **OBSERVE** that the `can.begin();` line is **ONLY** necessary if you are using an RP2040, you may omit this line if you are using a Teensy 4.

The send function has a function signature of `send(double data, int dataType);`

* In the example we are passing in the arbitrary data variable and the data type `RPM` which is also taken from the address book.

And that's it! You just send data over CAN


### Receiving Data:
Let's take a look at one of the receiving examples

```
#include "SMVcanbus.h"

CANBUS can(Bear_1);

void setup(void){
  Serial.begin(115200);
  can.begin(); //THIS IS FOR RP2040 ONLY, OMIT OTHERWISE
}

void loop(){
  can.looper();
  if(can.isThere())
  {
    Serial.print("The data is: ");
    Serial.println(can.getData());
    Serial.print("The Hardware Type is: ");
    Serial.println(can.getHardware());
    Serial.print("The Data Type is: ");
    Serial.println(can.getDataType());
  }
  delay(20);
}
```

* First we are including the library `#include "SMVcanbus.h`

* Then we initialize the CANBUS object with device id of the bear `CANBUS can(Bear_1);`

* From there in the `loop()` function we insert `can.looper();`
    * This **MUST BE INCLUDED** inside of the **loop** function if you want to receive data.

* Afterwards in an `if` statement we are checking `can.isThere()`
    * This function returns True if a **NEW** message was received after the previous call of `getData();`

* After checking if we have a new message we can get the contents of the message
    * `can.getData();` returns a double representing the payload of the packet.
    * `can.getHardware();` returns a const char* (if RP2040) or a string (if Teensy 4) that represents the device that sent the packet.
    * `can.getDataType();` returns a const char* (if RP2040) or a string (if Teensy 4) that represents the data type of the device that sent the packet.
    * **NOTE** that you can still call these data accessing functions without calling `isThere()`. It will just return the data from the last received packet.
        * you accept the fact that you might be looking at old data multiple times if you don't check for new messages with `can.isThere();`

And that's it for receiving data!

## Notes:
#### 1. Location of Library Folder
Windows: For windows, the library folder is usually found here:

`C:\Users\{username}\Documents\Arduino`

Mac OS: For Macs it's usually found here:

`/Users/{username}/Documents/Arduino`

Linux: If you're on linux, I don't think I need to write it here but:

`/home/{username}/Arduino`

#### 2. The can.begin() function
This function is only necessary for the RP2040 version **ONLY** it will not compile if you try it with the Teensy version.

## Address Book

```
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
```