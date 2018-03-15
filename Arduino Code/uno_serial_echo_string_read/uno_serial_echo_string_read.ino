
//serial variables
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  //setup serial
  Serial.begin(9600);
}

void loop() {
  if (stringComplete) {
    inputString.remove(inputString.indexOf('!'));

    int sensor1Value = inputString.substring(0,inputString.indexOf(',')).toInt();
    inputString.remove(0,inputString.indexOf(',')+1);

    int sensor2Value = inputString.substring(0,inputString.indexOf(',')).toInt();
    inputString.remove(0,inputString.indexOf(',')+1);
      
    int current = inputString.toInt();

    Serial.print(sensor1Value);
    Serial.print(",");
    Serial.print(sensor2Value);
    Serial.print(",");
    Serial.println(current);
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  if (!stringComplete){
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
}
