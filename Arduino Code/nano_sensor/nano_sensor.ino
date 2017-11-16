#include <Event.h>
#include <Timer.h>
 
 #define LED 4
 #define outputA 2 //green
 #define outputB 3 //blue
 
 Timer timerSerial;
 
 int counter = 0; 
 int aState;
 int aLastState;
 bool led = false;
 void setup() { 

   timerSerial.every(500, serial);
  
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   pinMode (LED,OUTPUT);
   
   Serial.begin (9600);
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA);   
 } 
 void loop() { 
  timerSerial.update();
  
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
     led = !led;
     digitalWrite(LED,led);
     
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
 }

void serial(){
  Serial.println(counter);
}

