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
#define sol1inf 2
#define sol1def 3
#define sol2inf 4
#define sol2def 5
#define sol3inf 6
#define sol3def 7
#define sol4inf 8
#define sol4def 9
// stepper flow valves
#define step1A1 10
#define step1B2 11
#define step1C3 12
#define step1D4 13
#define step2A1 14
#define step2B2 15
#define step2C3 16
#define step2D4 17
#define step3A1 18
#define step3B2 19
#define step3C3 20
#define step3D4 21
#define step4A1 22
#define step4B2 23
#define step4C3 24
#define step4D4 25

// sensors
#define sens1A 26//GREEN
#define sens1B 27//BLUE
 int aState;
 int aLastState;  

//control variables
volatile double target = 0;
volatile double current = 0;
double output = 0;
int Kp = 5;
int Ki = 0;
int Kd = 0;
PID PID1(&current,&output,&target,Kp,Ki,Kd,DIRECT);

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
int motorSpeed = 7;
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
  pinMode (sens1A,INPUT);
  pinMode (sens1B,INPUT);

  //set stepper speed
  flowStep1.setSpeed(motorSpeed);
  flowStep2.setSpeed(motorSpeed);
  flowStep3.setSpeed(motorSpeed);
  flowStep4.setSpeed(motorSpeed);

  //setup timers
  timerSerial.every(10, serial);
  timerDrive.every(100, drive);
  timerControl.every(400, control);

  //setup serial
  Serial.begin(9600);
  Serial1.begin(9600);

  //pid
  PID1.SetMode(AUTOMATIC);
  PID1.SetOutputLimits(0,100);

  //get steppers to inital positions
  //flowStep1.step(-6*stepsPerRevolution);
  //flowStep2.step(-6*stepsPerRevolution);
  //flowStep3.step(-6*stepsPerRevolution);
  //flowStep4.step(-6*stepsPerRevolution);
  digitalWrite(LED_BUILTIN, HIGH);

  //sensor setup
  aLastState = digitalRead(sens1A); 
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
      target = inputString.toInt();
      // clear the string:
      inputString = "";
      stringComplete = false;
    }
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
    flowStep1.step(-22);
    flowStep1Curent-=1;
  }
  else if(flowStep1Curent < flowStep1Target){
    flowStep1.step(22);
    flowStep1Curent+=1;
  }
  
  if(flowStep2Curent > flowStep2Target){
    flowStep2.step(-22);
    flowStep2Curent-=1;
  }
  else if(flowStep2Curent < flowStep2Target){
    flowStep2.step(22);
    flowStep2Curent+=1;
  }
  
  if(flowStep3Curent > flowStep3Target){
    flowStep3.step(-22);
    flowStep3Curent-=1;
  }
  else if(flowStep3Curent < flowStep3Target){
    flowStep3.step(22);
    flowStep3Curent+=1;
  }
  
  if(flowStep4Curent > flowStep4Target){
    flowStep4.step(-22);
    flowStep4Curent-=1;
  }
  else if(flowStep4Curent < flowStep4Target){
    flowStep4.step(22);
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
   PID1.Compute();
   flowStep1Target = (int)(output);//abs(current - target));
}

