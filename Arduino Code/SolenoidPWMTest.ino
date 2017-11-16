//Harry Thorpe PWM
#include <Event.h>
#include <Timer.h>
 #define outputA 3
 #define outputB 4
 #define outputC 6
 #define outputD 7
Timer timer;
 int aState;
 int aLastState; 
  int counter = 0; 
   int aState1;
 int aLastState1; 
  int counter1 = 0; 

volatile int pwmtick =0;//counter
volatile int DutyCycle = 0;
volatile int cycleTime = 1000;
volatile int toggle = 0;

void doSomething() {
  
  // check pwmtick is no greater than 1000 for a 50Hz Cycle
   if (pwmtick > cycleTime){
    pwmtick = 0;}
    
   //Done every 1000ms
  int onTicks = (int)(  (float)(DutyCycle)/100 * cycleTime);
  if(pwmtick < onTicks){
    //turn on
    digitalWrite(5,HIGH);
     digitalWrite(8,LOW);
    }
  else{
    //turn off
    digitalWrite(8,HIGH);
 digitalWrite(5,LOW);
    }

  //increase pwmtick
  pwmtick += 1;
}


void setup() {
  pinMode(5, OUTPUT);
   pinMode (8,OUTPUT);
  // put your setup code here, to run once:
  timer.every(1, doSomething);
  Serial.begin(9600);
     pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);

     pinMode (outputC,INPUT);
   pinMode (outputD,INPUT);
     aLastState = digitalRead(outputA); 
   aLastState1= digitalRead(outputC);   
}

void loop() {
  // put your main code here, to run repeatedly:
  timer.update();

   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
     if(counter > 100){counter =100;}
     if(counter < 0)  {counter =0;}
     DutyCycle = counter;
      Serial.print("DutyCycle: ");
   Serial.println(DutyCycle);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state



aState1 = digitalRead(outputC); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState1 != aLastState1){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputD) != aState1) { 
       counter1 += 10;
     } else {
       counter1 -= 10;
     }
     if(counter1 > 1000){counter1 =1000;}
     if(counter1 < 0)  {counter1 =0;}
      cycleTime = counter1;
         Serial.print("CycleTime: ");
   Serial.println(cycleTime);
    }
   aLastState1 = aState1; // Updates the previous state of the outputA with the current state


   
}