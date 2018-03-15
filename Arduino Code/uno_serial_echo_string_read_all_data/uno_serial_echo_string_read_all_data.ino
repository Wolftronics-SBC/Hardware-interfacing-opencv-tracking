
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

    int current = inputString.substring(0,inputString.indexOf(',')).toInt();
    inputString.remove(0,inputString.indexOf(',')+1);

    int target = inputString.substring(0,inputString.indexOf(',')).toInt();
    inputString.remove(0,inputString.indexOf(',')+1);

    int tempKp = inputString.substring(0,inputString.indexOf(',')).toInt();
    inputString.remove(0,inputString.indexOf(',')+1);
    
    int tempKi = inputString.substring(0,inputString.indexOf(',')).toInt();
    inputString.remove(0,inputString.indexOf(',')+1);

    int tempKd = inputString.substring(0,inputString.indexOf(',')).toInt();
    inputString.remove(0,inputString.indexOf(',')+1);

    int output = inputString.substring(0,inputString.indexOf(',')).toInt();
    inputString.remove(0,inputString.indexOf(',')+1);
    
    int reverseConst1 = inputString.toInt();

    Serial.print(current);
    Serial.print(",");
    Serial.print(target);
    Serial.print(",");
    Serial.print(tempKp);
    Serial.print(",");
    Serial.print(tempKi);
    Serial.print(",");
    Serial.print(tempKd);
    Serial.print(",");
    Serial.print(output);
    Serial.print(",");
    Serial.println(reverseConst1);
    
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
