//serial variables
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  Serial1.begin(9600);
  Serial2.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:

if(Serial2.available()){
  char charin = Serial2.read();
  if(charin == '\n'){
    Serial.print(",");
    Serial.println(micros());
    }
    else{
      Serial.print(charin);}
  
  }


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
if (stringComplete) {
    inputString.remove(inputString.indexOf('!'));

    int sense1 = inputString.substring(0,inputString.indexOf(',')).toInt();
    inputString.remove(0,inputString.indexOf(',')+1);

    int sense2 = inputString.substring(0,inputString.indexOf(',')).toInt();
    inputString.remove(0,inputString.indexOf(',')+1);

    int current = inputString.substring(0,inputString.indexOf(',')).toInt();
    inputString.remove(0,inputString.indexOf(',')+1);

    int target = inputString.toInt();
    
              Serial.print(sense1);
              Serial.print(",");
              Serial.print(sense2);
              Serial.print(",");
              Serial.print(current);
              Serial.print(",");
              Serial.print(current);
              Serial.print(",");
              Serial.println(micros());
    // clear the string:
    inputString = "";
    stringComplete = false;
  }


}
