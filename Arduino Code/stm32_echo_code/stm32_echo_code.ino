void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial1.available()) {
    
    Serial.println((char)Serial1.read());
    
    //if(inputString == "!") Serial.println("");
    //else Serial.print(Serial.read());
  }
}


