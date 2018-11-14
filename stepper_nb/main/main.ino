////// ED_v4  Step Mode Chart //////
//                                //
//   MS1 MS2 Resolution           //
//   L   L   Full step (2 phase)  //
//   H   L   Half step            //
//   L   H   Quarter step         //
//   H   H   Eighth step          //
//                                //
////////////////////////////////////
#include <Arduino.h>

#define STEPS_PER_REV 200

int DIR = 9;          // PIN  3 = DIR
int STEP = 10;        // PIN  2 = STEP
int MS1 = 11;        // PIN 13 = MS
int MS2 = 8;         // PIN  9 = MS2
int SLEEP = 12;      // PIN 12 = SLP
int dir=0;

//=============================
float Speed = 10.0;

// some globals
//=============
int StepsPerSecond;    // speed converted to steps/second
int StepDelay;         // = delay in mS per step

int MS1_MODE(int MS1_StepMode);
int MS2_MODE(int MS2_StepMode);

void setup() {
  Serial.begin(9600);     // open the serial connection at 9600bps
  pinMode(DIR, OUTPUT);   // set pin 3 to output
  pinMode(STEP, OUTPUT);  // set pin 2 to output
  pinMode(MS1, OUTPUT);   // set pin 13 to output
  pinMode(MS2, OUTPUT);   // set pin 9 to output
  pinMode(SLEEP, OUTPUT); // set pin 12 to output
  
  digitalWrite(MS1, LOW);  // Set state of MS1 based on the returned value from the MS1_MODE() switch statement.
    digitalWrite(MS2, LOW);  // Set state of MS2 based on the returned value from the MS2_MODE() switch statement.
    digitalWrite(SLEEP, HIGH);              // Set the Sleep mode to AWAKE.
    
  StepsPerSecond = Speed * STEPS_PER_REV * 8 / 60;
  StepDelay = 1000 / StepsPerSecond;
    
}



void loop()
{                                         // ..to identify our step mode type.                                            
                      // loops the following block of code 4 times before repeating .
    if(dir == 0){
    digitalWrite(DIR, LOW); 
    dir = 1;}
    else {digitalWrite(DIR, HIGH);
    dir = 0;}// Set the direction change LOW to HIGH to go in opposite direction
    
    int i = 0;                              // Set the counter variable.     
    while(i<15000)                 // Iterate for 200, then 400, then 800, then 1600 steps. 
                                            // Then reset to 200 and start again.
    {
      digitalWrite(STEP, HIGH);
      //delayMicroseconds(5);// This LOW to HIGH change is what creates the..
      digitalWrite(STEP, LOW);             // .."Rising Edge" so the easydriver knows to when to step.
      delay(StepDelay);     // This delay time determines the speed of the stepper motor. 
                                            // Delay shortens from 1600 to 800 to 400 to 200 then resets  
                                                 
      i++;                      
    }                              
               // Multiply the current modeType value by 2 and make the result the new value for modeType.
                                            // This will make the modeType variable count 1,2,4,8 each time we pass though the while loop.
   
    delay(500);
  
//  digitalWrite(SLEEP, LOW);                 // switch off the power to stepper
  Serial.print("SLEEPING..");
//  digitalWrite(SLEEP, HIGH);
//  Serial.println("AWAKE!!!");                // Switch on the power to stepper
//  delay(1000);
}








