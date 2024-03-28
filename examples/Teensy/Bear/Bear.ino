#include "ramping.h"
#include "Kalman.h"
#include "GLOBAL.h"
#include "SMVcanbus.h"

/* MOTOR SELECT */
bool selectMotorLeft = true; // Set true for left motor, false for right motor
CANBUS can(Bear_1); // Bear_1 for left, Bear_2 for right


/* Global Variables */
bool reverse; byte buttonPin = 4; // Variables which vary based on bool selectMotorLeft  
int speedIn = 0, filt_speed = 0, rampThr;
byte currentState; 
bool armed = false, cruise = false;
double rpm = 0., filt_rpm = 0., desiredRPM = 0.;
volatile long hall_value = 0;

/* Initialize timer, filters, and ramping */
IntervalTimer hallTimer;
Kalman RPMFilter(1.4,10,1023,0); 
Kalman throttleFilter(1.4,10,1023,0);
Ramping* rampThrottle;

void setup() {

  Serial.begin(115200);

  /* Motor Specific Settings */
  reverse = selectMotorLeft;
  if (selectMotorLeft){
    buttonPin = 5;
  }
  
  /* Configure GPIO pins */
  pinMode(HALL_A, INPUT_PULLUP);
  pinMode(HALL_B, INPUT_PULLUP);
  pinMode(HALL_C, INPUT_PULLUP);
  pinMode(IN_A, OUTPUT);
  pinMode(IN_B, OUTPUT);
  pinMode(IN_C, OUTPUT);
  pinMode(SD_A, OUTPUT);
  pinMode(SD_B, OUTPUT);
  pinMode(SD_C, OUTPUT);
  pinMode(THROTTLE, INPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(CRUISE, INPUT);

  /* Set PWM frequency */
  analogWriteFrequency(IN_A,PWM_FREQ);
  analogWriteFrequency(IN_B,PWM_FREQ);
  analogWriteFrequency(IN_C,PWM_FREQ);
  analogWriteFrequency(SD_A,PWM_FREQ);
  analogWriteFrequency(SD_B,PWM_FREQ);
  analogWriteFrequency(SD_C,PWM_FREQ);

  /* Ramping and basic hardware initializations */
  rampThrottle = new Linear;
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, LOW);
  controlPhases(0); // Shutdown gate drivers at boot-up
  
  /* Starting comditions: 
     Low starting speed, valid hall sensor position, manual press to start */
  while (!armed) {
    currentState = readState();
    cruise = digitalRead(CRUISE);
    speedIn = readThrottle();
    filt_speed = min((int)throttleFilter.getFilteredValue(speedIn)+1,MAX_SPEED);
    rampThr = rampThrottle->newSpd((int)filt_speed, millis());
    commInfo();

    if (currentState == 0 || currentState == 7) { // Hall error
      digitalWrite(LED_1, millis()%200 > 100); // Fast blink
    }
    else if (rampThr > MAX_START_SPEED) { // High start speed error
      digitalWrite(LED_1, millis()%800 > 400); // Slow blink
    }
    else if (digitalRead(buttonPin)) { // Button needs to be pressed to start
      digitalWrite(LED_1, HIGH); // Constant on
    }
    else {
      armed = true;
    }
    delay(20);
  }

  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  delay(750); // button deboucing time

  /* Attach interrupts */
  attachInterrupt(digitalPinToInterrupt(HALL_A), updateHall, RISING);
  attachInterrupt(digitalPinToInterrupt(HALL_B), updateHall, RISING);
  attachInterrupt(digitalPinToInterrupt(HALL_C), updateHall, RISING);
  hallTimer.begin(timerHandler, 1000*TIMER_INTERVAL_MS);
}

// Code freezing up - check this - FIXED: issue was analogRead inside of hardware timer
void loop() {
  /* Code for reading in speed and determining cruise condition */
  speedIn = readThrottle(); 
  filt_speed = min((int)throttleFilter.getFilteredValue(speedIn)+1,MAX_SPEED); // Kalman filter for throttle
  rampThr = rampThrottle->newSpd((int)filt_speed, millis()); // Ramping for throttle
  cruise = cruiseCondition(rampThr,filt_rpm); // TO DO: re-enable cruise / re-tune it
  //cruise = false; // TO DO: re-enable cruise / re-tune it

  /* Debug LEDs */
  digitalWrite(LED_1,!armed);
  //digitalWrite(LED_2,reverse);

  /* Code for start/stop the motor */
  if (!digitalRead(buttonPin)){
    if (armed){ // Disable motor whenever motor is armed as safety shutdown
      controlPhases(0);
      armed = false;
    }
    else{ // If not moving, make sure motor is below initial start speed before enabling
      if (rampThr < MAX_START_SPEED) // TO DO: make these error lights match up with setup code
        armed = true;
    }
    delay(750); // button deboucing time
  }
  
  /* Code for reading state and controlling gate drivers */
  for (int i = 0; i < 4000; i++){  
    currentState = readState();
    if (cruise){ // Cruising operation
      controlPhases(0); // Shutdown gate drivers to allow motor to freely spin
    }
    else{ // Normal operation
      if (armed){
        controlPhases(currentState); // Enable gate drive signals based on motor's current state
      }
      else{
        controlPhases(0); // Shutdown gate drivers
      }
    }
  }
  
}

/* Read and scale the throttle sensor */
int readThrottle(){
  return max(0,min(map(analogRead(THROTTLE), MIN_THROTTLE, MAX_THROTTLE, 0, MAX_SPEED),MAX_SPEED));
}

/* Encode the motor's state (1 through 6) by reading the hall sensor signals, 0 and 7 are error case
   Obtain a specific encoding depending on the rotation direction */
byte readState() { 
  if (reverse)
    return 7 - ((digitalRead(HALL_A) << 2) + (digitalRead(HALL_B) << 1) +  digitalRead(HALL_C));
  else
    return (digitalRead(HALL_A) << 2) + (digitalRead(HALL_B) << 1) +  digitalRead(HALL_C);   
}

/* Generate pulses that are sent to the input pins of the gate drivers */
void controlPhases(byte state){ 
  switch (state) {
    case 4:
      analogWrite(SD_A, 255);
      analogWrite(IN_A, rampThr);
      
      analogWrite(IN_B, 0);
      analogWrite(SD_B, 255);
      
      analogWrite(SD_C, 0);
      analogWrite(IN_C, 0);
      break;
    case 6:
      analogWrite(SD_A, 0);
      analogWrite(IN_A, 0);
      
      analogWrite(IN_B, 0);
      analogWrite(SD_B, 255);

      analogWrite(SD_C, 255);      
      analogWrite(IN_C, rampThr);
      break;
    case 2:
      analogWrite(IN_A, 0);
      analogWrite(SD_A, 255);
      
      analogWrite(SD_B, 0);
      analogWrite(IN_B, 0);
      
      analogWrite(SD_C, 255);      
      analogWrite(IN_C, rampThr);
      break;
    case 3:
      analogWrite(IN_A, 0);
      analogWrite(SD_A, 255);
      
      analogWrite(SD_B, 255);
      analogWrite(IN_B, rampThr);
      
      analogWrite(SD_C, 0);
      analogWrite(IN_C, 0);
      break;
    case 1:
      analogWrite(SD_A, 0);
      analogWrite(IN_A, 0);
      
      analogWrite(SD_B, 255);
      analogWrite(IN_B, rampThr);
      
      analogWrite(IN_C, 0);
      analogWrite(SD_C, 255);
      break;
    case 5:
      analogWrite(SD_A, 255);
      analogWrite(IN_A, rampThr);
            
      analogWrite(SD_B, 0);
      analogWrite(IN_B, 0);
      
      analogWrite(IN_C, 0);
      analogWrite(SD_C, 255);
      break;
    case 0: // Error states or cruise condition: shut off all gate drivers 
      analogWrite(SD_A, 0);
      analogWrite(SD_B, 0);
      analogWrite(SD_C, 0);
      analogWrite(IN_A, 0);
      analogWrite(IN_B, 0);
      analogWrite(IN_C, 0);
      break;
    case 7:
      analogWrite(SD_A, 0);
      analogWrite(SD_B, 0);
      analogWrite(SD_C, 0);
      analogWrite(IN_A, 0);
      analogWrite(IN_B, 0);
      analogWrite(IN_C, 0);
      break;
  }  
}

/* Reutrns true if cruise is desired and gate drivers need to be shutdown */
bool cruiseCondition(int throttle, double currentRPM){ 
  desiredRPM = map(throttle,0.,MAX_SPEED,0.,MAX_RPM);
  return (desiredRPM < currentRPM) || (throttle < MOTOR_OFF_THROTTLE);
  //return ((desiredRPM < currentRPM) || (throttle < MOTOR_OFF_THROTTLE)) || digitalRead(CRUISE); // If using 3rd teensy input
  return ((throttle < MOTOR_OFF_THROTTLE) || digitalRead(CRUISE)); // ratcheting off
}

/* Use for doing computations for RPM after a fixed measurement interval*/
void timerHandler() { 
  /* RPM Calculation */

  // hall_value: [pulses*TIMER_INTERVAL_MS/ms]
  // Multiply by [1/TIMER_INTERVAL_MS] to get [pulses/ms]
  // Multiply by 1000 to get [pulses/s]
  // Multiply by 60 to get [pulses/min]
  // Multiply by 1/POLE_COUNT = (1/(pulses/revolution)) to get [rev/min] (with 1 hall sensor using rise condition, interrupt triggers POLE_COUNT times in a revolution) 

  //rpm = (double)hall_value / POLE_COUNT * (1000./TIMER_INTERVAL_MS) * 60. / 3. *2.;
  rpm = (double)hall_value / POLE_COUNT * (40000./TIMER_INTERVAL_MS);
  filt_rpm = RPMFilter.getFilteredValue(rpm); // Apply Kalman filter on RPM calculation     
  commInfo();
  hall_value = 0; // Reset hall values 
}

/* ISR function increments hall count when hall interrupt is triggered */
void updateHall() {
  hall_value++;
}

/* Info for UART communication and debugging, to be printed out periodically within timerHandler() */
void commInfo(){
  Serial.print("Armed: "); Serial.print(armed); Serial.print(" | ");
  Serial.print("RawThr: "); Serial.print(speedIn); Serial.print(" | ");
  Serial.print("DrvThr: "); Serial.print(rampThr); Serial.print(" | ");
  Serial.print("State: "); Serial.print(currentState); Serial.print(" | ");
  Serial.print("EstRPM: "); Serial.print(desiredRPM); Serial.print(" | ");
  Serial.print("CurrRPM: "); Serial.print(filt_rpm); Serial.print(" | ");
  Serial.print("Cruise: "); Serial.print(cruise); 
  Serial.println("");  

  can.looper();
  can.send(rampThr, Throttle);
  can.send(currentState, Motor_State);
  can.send(filt_rpm, RPM);
  can.send(armed, M_Error_Status);
  can.send(cruise, Cruise);
  can.send(rpmToMPH(filt_rpm), Meter_Count);
  //throttle- ramp throttle
  //motor state- currentState
  //rpm- filt_rpm
  //error_status- armed
  //cruise- cruise
  
}

/* Tests out low voltage electronics on PCB */
void tester() {
  byte throttleVal = analogRead(THROTTLE);
  bool buttonVal1 = digitalRead(buttonPin);
  bool cruise = digitalRead(CRUISE);
  byte motorState = readState();
  analogWrite(LED_1,throttleVal);
  analogWrite(LED_2,255-throttleVal);
  Serial.print(throttleVal); Serial.print(", "); Serial.print(buttonVal1); Serial.print(", "); Serial.print(cruise); Serial.print(", "); Serial.println(motorState);
}

double rpmToMPH(double rpm){
  double rph = rpm * 60.;
  double dph = 2.*3.14*rph*10.; // inches/hour
  return dph * 0.00001578; //unit of miles/hour 
}
