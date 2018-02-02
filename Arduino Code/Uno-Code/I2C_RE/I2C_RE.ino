#include <Wire.h>
String data = "";
void setup() {
  // put your setup code here, to run once:
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(data);
}

void receiveEvent(int howMany){
  data = " ";
  while(Wire.available()){
      data += (char)Wire.read();
      }
}
