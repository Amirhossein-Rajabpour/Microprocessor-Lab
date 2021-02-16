#include <Keypad.h>
#include <Servo.h>

Servo servo;
String degStr;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(2,1000,2000);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (Serial.available() > 0) {
    
    char input = Serial.read();
    Serial.print(input);
    if(input == '='){
      Serial.println("");
      servo.write(degStr.toInt());
      input = "";
      degStr = "";
      delay(1000);
      }
    else{
      degStr += input;
      }
  }
}
