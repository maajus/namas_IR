#include "IRLibAll.h"
#include <IRLibRecvPCI.h>
//Create a receiver object to listen on pin 2
IRrecvPCI myReceiver(2);
//Create a decoder object
IRdecode myDecoder;

//Create a decoder object
//IRdecode myDecoder;

//red
#define RED 0x52E9
#define GREEN 0x32E9
#define YELOW 0x72E9
#define BLUE 0x12E9

#define OUT_PIN 4


void setup() {
  Serial.begin(9600);
  myReceiver.enableIRIn(); // Start the receiver
  pinMode(OUT_PIN, OUTPUT);
  digitalWrite(OUT_PIN, HIGH);
}

void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {

    myDecoder.decode();
    //Serial.println(myDecoder.value, HEX);
    if (myDecoder.value == RED) {
      digitalWrite(OUT_PIN, HIGH);
      Serial.println("Red");
    }
    if (myDecoder.value == GREEN) {
      digitalWrite(OUT_PIN, LOW);
      Serial.println("Green");
    }
    if (myDecoder.value == YELOW)
      Serial.println("Yelow");
    if (myDecoder.value == BLUE)
      Serial.println("Blue");

    delay(300);
    myReceiver.enableIRIn();      //Restart receiver
  }


}




