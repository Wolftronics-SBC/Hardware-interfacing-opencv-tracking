#include <X113647Stepper.h>
#include <PID_v1.h>
#include <Event.h>
#include <Timer.h>

//timers
Timer timerSerial;
Timer timerDrive;
Timer timerControl;

//pins
// solinoids
#define sol4inf 2
#define sol4def 3
#define sol3inf 4
#define sol3def 5
#define sol2inf 6
#define sol2def 7
#define sol1inf 8
#define sol1def 9
// stepper flow valves
#define step1A1 10
#define step1B2 11
#define step1C3 12
#define step1D4 13
#define step2A1 22
#define step2B2 23
#define step2C3 24
#define step2D4 25
#define step3A1 26
#define step3B2 27
#define step3C3 28
#define step3D4 29
#define step4A1 30
#define step4B2 31
#define step4C3 32
#define step4D4 33

//buttons
#define butt1 34
#define butt2 35

#define sensor1Pin A1
#define sensor2Pin A2

int sensor1Value = 0;
int sensor2Value = 0;


//button variables
bool butt1State = false;
bool butt1LastState = false;

//control variables
volatile double target = 0;
volatile double current = 0;
double output = 0;
double Kp = 5;
double Ki = 0;
double Kd = 0;
PID PID1(&current,&output,&target,Kp,Ki,Kd,DIRECT);
double reverseConst1 = 1;

//serial variables
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

//drive variables
volatile bool inf1 = false;
volatile bool def1 = false;
volatile bool inf2 = false;
volatile bool def2 = false;
volatile bool inf3 = false;
volatile bool def3 = false;
volatile bool inf4 = false;
volatile bool def4 = false;

// steppers
#define Resolution 10 //22 for fully open to fully closed 1-100
int defultPos = -180; // harry's -180
int motorSpeed = 6;
int stepsPerRevolution =  64 * 32;
X113647Stepper flowStep1(stepsPerRevolution, step1A1, step1B2, step1C3, step1D4);
X113647Stepper flowStep2(stepsPerRevolution, step2A1, step2B2, step2C3, step2D4);
X113647Stepper flowStep3(stepsPerRevolution, step3A1, step3B2, step3C3, step3D4);
X113647Stepper flowStep4(stepsPerRevolution, step4A1, step4B2, step4C3, step4D4);
int flowStep1Curent = 0;
int flowStep1Target = 0;
int flowStep2Curent = 0;
int flowStep2Target = 0;
int flowStep3Curent = 0;
int flowStep3Target = 0;
int flowStep4Curent = 0;
int flowStep4Target = 0;

void setup() {
  // put your setup code here, to run once:
  //setup pins
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode (sol1inf,OUTPUT);
  pinMode (sol1def,OUTPUT);
  pinMode (sol2inf,OUTPUT);
  pinMode (sol2def,OUTPUT);
  pinMode (sol3inf,OUTPUT);
  pinMode (sol3def,OUTPUT);
  pinMode (sol4inf,OUTPUT);
  pinMode (sol4def,OUTPUT);
  pinMode (butt1,INPUT_PULLUP);
  pinMode (butt2,INPUT_PULLUP);

  
  //set stepper speed
  flowStep1.setSpeed(motorSpeed);
  flowStep2.setSpeed(motorSpeed);
  flowStep3.setSpeed(motorSpeed);
  flowStep4.setSpeed(motorSpeed);

  //setup timers
  timerSerial.every(10, serial);
  timerDrive.every(50, drive);
  timerControl.every(400, control);

  //setup serial
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);

  //pid
  PID1.SetMode(AUTOMATIC);
  PID1.SetOutputLimits(0,100);

  //button reading setup
  butt1State = digitalRead(butt1);
  butt1LastState = butt1State;

  }

void loop() {
  // put your main code here, to run repeatedly:
  timerSerial.update();
  timerDrive.update();
  timerControl.update();

    if (stringComplete) {
      inputString.remove(inputString.indexOf('!'));
      
      current = inputString.substring(0,inputString.indexOf(',')).toInt();
      inputString.remove(0,inputString.indexOf(',')+1);
      
      target = inputString.substring(0,inputString.indexOf(',')).toInt();
      inputString.remove(0,inputString.indexOf(',')+1);
      
      int tempKp = inputString.substring(0,inputString.indexOf(',')).toInt();
      inputString.remove(0,inputString.indexOf(',')+1);
      
      int tempKi = inputString.substring(0,inputString.indexOf(',')).toInt();
      inputString.remove(0,inputString.indexOf(',')+1);
      
      int tempKd = inputString.substring(0,inputString.indexOf(',')).toInt();
      inputString.remove(0,inputString.indexOf(',')+1);
      
      int tempReverseConst1 = inputString.toInt();
      
      Kp = (double)tempKp/10;
      Ki = (double)tempKi/10;
      Kd = (double)tempKd/10;
      reverseConst1 = (double)tempReverseConst1/10;
      
      //Serial1.print("current ");
      //Serial1.println(current);
      //Serial1.print("target ");
      //Serial1.println(target);
      //Serial1.print("tempKp ");
     // Serial1.println(tempKp);
      //Serial1.print("tempKi ");
      //Serial1.println(tempKi);
      //Serial1.print("tempKd ");
      //Serial1.println(tempKd);
      //Serial1.print("output ");
      //Serial1.println(output);
      //Serial1.print("reverseConst1 ");
     // Serial1.println(reverseConst1);
      //Serial1.println(9999999);
      
      // clear the string:
      inputString = "";
      stringComplete = false;
    }
    PID1.SetTunings(Kp, Ki, Kd);
    PID1.Compute();
    //Serial.println(output);

    //get steppers to inital positions
    butt1State = digitalRead(butt1);

    
    if(!butt1State){
      flowStep1.setSpeed(motorSpeed+2);
      flowStep1.step(-Resolution);

      flowStep2.setSpeed(motorSpeed+2);
      flowStep2.step(-Resolution);

      flowStep3.setSpeed(motorSpeed+2);
      flowStep3.step(-Resolution);

      flowStep4.setSpeed(motorSpeed+2);
      flowStep4.step(-Resolution);
    }
    if(butt1State != butt1LastState){
      if(butt1State && !butt1LastState){
        flowStep1.setSpeed(motorSpeed);
        flowStep1Curent = defultPos;
        flowStep1Target = defultPos;
        
        flowStep2.setSpeed(motorSpeed);
        flowStep2Curent = defultPos;
        flowStep2Target = defultPos;
        
        flowStep3.setSpeed(motorSpeed);
        flowStep3Curent = defultPos;
        flowStep3Target = defultPos;
        
        flowStep4.setSpeed(motorSpeed);
        flowStep4Curent = defultPos;
        flowStep4Target = defultPos;
      }
      butt1LastState = butt1State;
    }
    if(digitalRead(butt2) == 0){
        digitalWrite(sol1def, 1);
        digitalWrite(sol1inf, 1);
        delay(50);
        digitalWrite(sol1def, 0);
        digitalWrite(sol1inf, 0);
        delay(50);

        digitalWrite(sol2def, 1);
        digitalWrite(sol2inf, 1);
        delay(50);
        digitalWrite(sol2def, 0);
        digitalWrite(sol2inf, 0);
        delay(50);

        digitalWrite(sol3def, 1);
        digitalWrite(sol3inf, 1);
        delay(50);
        digitalWrite(sol3def, 0);
        digitalWrite(sol3inf, 0);
        delay(50);

        digitalWrite(sol4def, 1);
        digitalWrite(sol4inf, 1);
        delay(50);
        digitalWrite(sol4def, 0);
        digitalWrite(sol4inf, 0);
        delay(50);
    }
      sensor1Value = analogRead(sensor1Pin);
  sensor2Value = analogRead(sensor2Pin);
  Serial1.println(sensor1Value);
    Serial1.println(sensor2Value);
  Serial1.println(current);
  Serial1.println(999);

  }

//get serial data for target and current position
void serial(){
  
  Serial.println("A");
  
//  if (Serial1.available()) {
//    current = Serial1.parseInt();
//    Serial.println(current);
//  }
//  if (Serial.available()) {
//   target = Serial.parseInt();
//   Serial.println("target: "+String(target));
// }
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

//set output pins to current values
void drive(){
  //Serial.println("drive");
  //drive solinoids
  digitalWrite(sol1inf, inf1);
  digitalWrite(sol1def, def1);
  digitalWrite(sol2inf, inf2);
  digitalWrite(sol2def, def2);
  digitalWrite(sol3inf, inf3);
  digitalWrite(sol3def, def3);
  digitalWrite(sol4inf, inf4);
  digitalWrite(sol4def, def4);
  //drive steppers
  if(flowStep1Curent > flowStep1Target){
    flowStep1.step(-Resolution);
    flowStep1Curent-=1;
  }
  else if(flowStep1Curent < flowStep1Target){
    flowStep1.step(Resolution);
    flowStep1Curent+=1;
  }
  
  if(flowStep2Curent > flowStep2Target){
    flowStep2.step(-Resolution);
    flowStep2Curent-=1;
  }
  else if(flowStep2Curent < flowStep2Target){
    flowStep2.step(Resolution);
    flowStep2Curent+=1;
  }
  
  if(flowStep3Curent > flowStep3Target){
    flowStep3.step(-Resolution);
    flowStep3Curent-=1;
  }
  else if(flowStep3Curent < flowStep3Target){
    flowStep3.step(Resolution);
    flowStep3Curent+=1;
  }
  
  if(flowStep4Curent > flowStep4Target){
    flowStep4.step(-Resolution);
    flowStep4Curent-=1;
  }
  else if(flowStep4Curent < flowStep4Target){
    flowStep4.step(Resolution);
    flowStep4Curent+=1;
  }
  
}

//PID control system
void control(){
  //Serial.println("control");
  
   int range = 1;
   if(current <= target+range && current >= target-range){
    inf1 = false;
    def1 = false;
   }
   else if(current <= target-range){
    inf1 = true;
    def1 = false;
   }
   else if(current >= target+range){
    inf1 = false;
    def1 = true;
   }

   if(current <= target+range && current >= target-range){
    inf2 = false;
    def2 = false;
   }
   else if(current <= target-range){
    inf2 = false;
    def2 = true;
   }
   else if(current >= target+range){
    inf2 = true;
    def2 = false;
   }
   
   flowStep1Target = (int)(output);//abs(current - target));
   flowStep2Target = (int)(output);
   //flowStep1Target = (int)(Kp*(double)(abs(current - target)));
   //Serial2.println((int)(Kp*(double)(abs(current - target))));

}

