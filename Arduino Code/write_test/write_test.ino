#include <Event.h>
#include <Timer.h>

Timer timerSerial;

int data = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  timerSerial.every(500, serial);
  Serial.println('B');
}

void loop() {
  // put your main code here, to run repeatedly: 
  timerSerial.update();

  delay(10*data);
  digitalWrite(2, HIGH);
  delay(10*data);
  digitalWrite(2, LOW);
}

void serial(){
  Serial.println('A');
}

void serialEvent(){
  data = Serial.parseInt();
}

