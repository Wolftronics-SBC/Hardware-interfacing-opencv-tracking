#include <Event.h>
#include <Timer.h>

Timer t1;
/*
  Serial Event example
 
 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and 
 clears it.
 
 A good test for this is to try it with a GPS receiver 
 that sends out NMEA 0183 sentences. 
 
 Created 9 May 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/SerialEvent
 
 */

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int toggle = 1;

void ask(){
//Ask computer for a value
Serial.println("A");

}

void setup() {
  pinMode(8,OUTPUT);
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  t1.every(1000,ask);
}

void loop() {
  t1.update();
 
  // print the string when a newline arrives:
  if (stringComplete) {
    //Serial.println(inputString); 
    // clear the string:
    if(inputString == "B!"){
      if(toggle == 1){
    
    digitalWrite(8,HIGH);
    toggle = 0;
    }
    else{
      digitalWrite(8,LOW);
      toggle = 1;
    
    }
  }
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
   
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
        if (inChar == '!') {
      stringComplete = true;
        }
  }
}

