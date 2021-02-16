#include <Servo.h>

Servo servo;  
 
int deg;    
void setup() {
  servo.attach(2,1000,2000);  
}

void loop() {
  deg = analogRead(A0);           
  deg = map(deg, 0, 1023, 0, 180);
  servo.write(deg);              
  delay(1000);               
}
