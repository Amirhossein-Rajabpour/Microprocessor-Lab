
#include <Servo.h>

Servo myServo;
int deg = 0;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(2);

}

void loop() {
  // put your main code here, to run repeatedly:
    for (deg = 0; deg <= 180; deg += 1) {
    myServo.write(deg);
    delay(10);
  }
  for (deg = 180; deg >= 0; deg -= 1) { 
    myServo.write(deg);
    delay(10);
  }

}
