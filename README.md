# UCLA-SMV-CAN

This is the UCLA Bruin Racing SMV implementation of the FlexCAN Library for Teensy 4

https://github.com/tonton81/FlexCAN_T4

Designed for the Teensy 4.0 and 4.1 (at least that's what I tested it on, other Teensy models may be compatible - see FlexCAN_T4). This library takes advantage of the CAN2.0 protocol. NOT CANFD

## Installing

Clone the repository into the Arduino libraries folder

Import the library by inserting in your code:
```
#include "SMVcanbus.h"
```

## Running

In order to use the library, declare an object of type CANBUS and pass in the enum of the hardware device (defined in ids.h). For example:
```
CANBUS can(Bear_1);
```
### Sending

If we break down the example Sender.ino:
```
#include "SMVcanbus.h"
CANBUS can(Bear_1);
double data = 1.123;
void setup(void) {
  Serial.begin(115200); delay(400); //just for printing
}

void loop() {
  can.send(data, RPM);
  Serial.println(data);
  data = data + 0.001;
  delay(20); //be careful with the speed that you send at, beware of out of order messages
}
```

First we include the header `#include "SMVcanbus.h"`

From there we declare an object of the CANBUS type `CNABUS can(Bear_1)` This is found as enum 0 in the devices enum in "ids.h".

To send data, simply call the `.send(data, DATATYPE)` function. The first field MUST be a double with the last field being another enum of the data type of the corresponding hardware that was initially set.

In the case above, we chose `Bear_1` to be our enum and a valid corresponding datatype enum is `RPM` (again, this can be found in the address book)

That's all that it takes to send a CAN bus message.

### Receiving

Now let's take a look at the example receiver.ino
```
#include "SMVcanbus.h"
CANBUS can(Bear_1);

void setup(void) {
  Serial.begin(115200); delay(400); //just for printing
}

void loop() {
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
  //delay(20); //be careful with the speed that you send at, beware of out of order messages
}
```

The setup of the receiver is similar to the sender with the include and object declaration. The difference is the presence of the `looper()` function.
#### `looper()` MUST BE PRESENT IN THE `loop()` FUNCTION IF YOU WANT TO RECEIVE MESSAGES

From there the logic is as follows:
 1. Ask the `can` object if there are any new messages, if there are,
 2. Get the data

The `can.isThere()` function is there if you only want to grab new messages, otherwise you can ignore it and the data will be from the most recent message.

The `getData()` function returns the message buffer as a double

The `getHardware()` function returns a string of what device the data is coming from

The `getDataType()` function returns a string of the data type that was sent

Those are all the functions available to use. The exact implementations are documented in the source code

## Address Book

Devices:
```
enum devices {
    Bear_1,
    Bear_2,
    Power_Control,
    Steering_Wheel,
    DAQ
};

enum motorMessage { //this is really just bear messages
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
    T1,
    T2,
    T3,
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

## Potential Upgrades
* Maybe we can implement a sequence number to mitigate out of order packets

* Use mailboxes and filters
  * Allows us to use the Ids field only for Ids
  * Potential efficiency savings because every teensy gets every message but only cares about the one meant for itself
    * Right now I am implementing the packet discarding based on ID, really should use the built in functionality for mailboxes

* Find something better than an enum address book

* Consider CANFD for higher bandwidth