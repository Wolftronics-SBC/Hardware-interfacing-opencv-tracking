

#define dataIN 2

#define numSegs 16
#define duratLim 500

unsigned long prevmillis = 0; // To store time
unsigned long duration = 0; // To store time difference
unsigned long refresh = 0; // To store time for refresh of reading
unsigned long rpm = 0; // RPM value

boolean currentstate = false; // Current state of IR input scan
boolean prevstate = false; // State of IR sensor in previous scan

void setup()
{
  pinMode(dataIN,INPUT);       
  prevmillis = 0;
  prevstate = LOW;  
  Serial.begin(9600);
  currentstate = digitalRead(dataIN);
  prevstate = currentstate;
}

void loop()
{
 // RPM Measurement
  currentstate = digitalRead(dataIN); // Read IR sensor state
  if( prevstate != currentstate) // If there is change in input
   {
         duration = ( micros() - prevmillis ); // Time difference between revolution in microsecond
         prevmillis = micros(); // store time for nect revolution calculation
          
         if(duration <= duratLim){}
         else{        
           rpm = (60000000/duration)/numSegs; // rpm = (1/ time millis)*1000*1000*60;
           Serial.println(rpm);
           //Serial.print(", ");
           //Serial.println(micros());
         }
   }
  prevstate = currentstate; // store this scan (prev scan) data for next scan
   
}

