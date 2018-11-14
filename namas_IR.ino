#include "IRLibAll.h"
#include <IRLibRecvPCI.h>

//red
#define RED 0x52E9
#define GREEN 0x32E9
#define YELOW 0x72E9
#define BLUE 0x12E9

#define RIGHT 0
#define LEFT 1



#define STEPS_PER_REV 200

const static int IR_PIN = 3;      // PIN ir receiver
const static int LED_PIN = 13;      //PIN LED
const static int OUT_PIN = 4;     // PIN for relay control
const static int DIR = 9;         // PIN  3 = DIR
const static int STEP = 10;       // PIN  2 = STEP
const static int MS1 = 11;        // PIN 13 = MS
const static int MS2 = 8;         // PIN  9 = MS2
const static int SLEEP = 12;      // PIN 12 = SLP


// some globals
int dir = 0;
float Speed = 2.0;
int StepsPerSecond;    // speed converted to steps/second
int StepDelay;         // = delay in mS per step



int MS1_MODE(int MS1_StepMode);
int MS2_MODE(int MS2_StepMode);
void turnStepper(int direction);


IRrecvPCI myReceiver(IR_PIN); //Create a receiver object to listen on pin
IRdecode myDecoder; //Create a decoder object


//Create a decoder object
//IRdecode myDecoder;


void setup() {
  Serial.begin(9600);
  myReceiver.enableIRIn(); // Start the receiver
  pinMode(OUT_PIN, OUTPUT);
  digitalWrite(OUT_PIN, HIGH);

  pinMode(LED_PIN, OUTPUT);

  pinMode(DIR, OUTPUT);   // set pin to output
  pinMode(STEP, OUTPUT);  // set pin to output
  pinMode(MS1, OUTPUT);   // set pin to output
  pinMode(MS2, OUTPUT);   // set pin to output
  pinMode(SLEEP, OUTPUT); // set pin to output


  digitalWrite(MS1, LOW);  // Set state of MS1 based on the returned value from the MS1_MODE() switch statement.
  digitalWrite(MS2, LOW);  // Set state of MS2 based on the returned value from the MS2_MODE() switch statement.
  digitalWrite(SLEEP, LOW);              // Set the Sleep mode to AWAKE.
  digitalWrite(STEP, LOW);



  StepsPerSecond = Speed * STEPS_PER_REV * 8 / 60;
  StepDelay = 1000 / StepsPerSecond;



}

void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {

    myDecoder.decode();
    Serial.println(myDecoder.value, HEX);
    if (myDecoder.value == RED) {
      digitalWrite(OUT_PIN, HIGH);
      Serial.println("Red");
    }
    if (myDecoder.value == GREEN) {
      digitalWrite(OUT_PIN, LOW);
      Serial.println("Green");
    }
    if (myDecoder.value == YELOW){
      Serial.println("Yelow");
      turnStepper(RIGHT);
    }
    if (myDecoder.value == BLUE){
      Serial.println("Blue");
      turnStepper(LEFT);
    }
    myReceiver.enableIRIn();      //Restart receiver

  }


}

void turnStepper(int direction) {

  digitalWrite(SLEEP, HIGH);              // Set the Sleep mode to AWAKE.
  digitalWrite(LED_PIN, HIGH);

  digitalWrite(DIR, direction);

  int i = 0;                         
  while (i++ < 20)             
  {
    digitalWrite(STEP, HIGH);
    //delayMicroseconds(5);// This LOW to HIGH change is what creates the..
    digitalWrite(STEP, LOW);             // .."Rising Edge" so the easydriver knows to when to step.
    delay(StepDelay);     // This delay time determines the speed of the stepper motor.
  }

    digitalWrite(LED_PIN, LOW);
    digitalWrite(SLEEP, LOW);              // Set the Sleep mode to AWAKE.


}


int MS1_MODE(int MS1_StepMode) {             // A function that returns a High or Low state number for MS1 pin
  switch (MS1_StepMode) {                    // Switch statement for changing the MS1 pin state
    // Different input states allowed are 1,2,4 or 8
    case 1:
      MS1_StepMode = 0;
      Serial.println("Step Mode is Full...");
      break;
    case 2:
      MS1_StepMode = 1;
      Serial.println("Step Mode is Half...");
      break;
    case 4:
      MS1_StepMode = 0;
      Serial.println("Step Mode is Quarter...");
      break;
    case 8:
      MS1_StepMode = 1;
      Serial.println("Step Mode is Eighth...");
      break;
  }
  return MS1_StepMode;
}



int MS2_MODE(int MS2_StepMode) {             // A function that returns a High or Low state number for MS2 pin
  switch (MS2_StepMode) {                    // Switch statement for changing the MS2 pin state
    // Different input states allowed are 1,2,4 or 8
    case 1:
      MS2_StepMode = 0;
      break;
    case 2:
      MS2_StepMode = 0;
      break;
    case 4:
      MS2_StepMode = 1;
      break;
    case 8:
      MS2_StepMode = 1;
      break;
  }
  return MS2_StepMode;
}
