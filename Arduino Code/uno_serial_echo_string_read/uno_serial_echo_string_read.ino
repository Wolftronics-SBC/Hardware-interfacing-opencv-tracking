
#define dataIN 2

#define numSegs 2
#define duratLim 500

unsigned long prevmillis = 0; // To store time
unsigned long duration = 0; // To store time difference
unsigned long refresh = 0; // To store time for refresh of reading
unsigned long rpm = 0; // RPM value

boolean currentstate = false; // Current state of IR input scan
boolean prevstate = false; // State of IR sensor in previous scan

//serial variables
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int y0 = 0;
int y1 = 0;
int y2 = 0;
int x0 = 0;
int x1 = 0;
int x2 = 0;

void setup() {
  //setup serial
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  
  pinMode(dataIN,INPUT);       
  prevmillis = 0;
  prevstate = LOW;  
  currentstate = digitalRead(dataIN);
  prevstate = currentstate;
}

void loop() {
   // RPM Measurement
  currentstate = digitalRead(dataIN); // Read IR sensor state
  if( prevstate != currentstate) // If there is change in input
   {
         duration = ( micros() - prevmillis ); // Time difference between revolution in microsecond
         prevmillis = micros(); // store time for nect revolution calculation
         rpm = (60000000/duration)/numSegs; // rpm = (1/ time millis)*1000*1000*60;
           

              Serial.print(",");
              Serial.println(duration);
   }
  prevstate = currentstate; // store this scan (prev scan) data for next scan
  
  if (stringComplete) {
    inputString.remove(inputString.indexOf('!'));

    y0 = inputString.substring(0,inputString.indexOf(',')).toInt();
    inputString.remove(0,inputString.indexOf(',')+1);

    y1 = inputString.substring(0,inputString.indexOf(',')).toInt();
    inputString.remove(0,inputString.indexOf(',')+1);

    y2 = inputString.substring(0,inputString.indexOf(',')).toInt();
    inputString.remove(0,inputString.indexOf(',')+1);

    x0 = inputString.substring(0,inputString.indexOf(',')).toInt();
    inputString.remove(0,inputString.indexOf(',')+1);

    x1 = inputString.substring(0,inputString.indexOf(',')).toInt();
    inputString.remove(0,inputString.indexOf(',')+1);
      
    x2 = inputString.toInt();
    
              Serial.print(y0);
              Serial.print(",");
              Serial.print(x0);
              Serial.print(",");
              Serial.print(y1);
              Serial.print(",");
              Serial.print(x1);
              Serial.print(",");
              Serial.print(y2);
              Serial.print(",");
              Serial.print(x2);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void serial1Event() {
  if (!stringComplete){
    if (Serial1.available()) {
      // get the new byte:
      char inChar = (char)Serial1.read();
      // add it to the inputString:
      inputString += inChar;
      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
      if (inChar == '!') {
        stringComplete = true;
      }
    }
  }
}

void serial2Event(){
  int duration = Serial2.read();
  
}

