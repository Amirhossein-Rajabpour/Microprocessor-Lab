#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'.','0','=','+'}
};
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#include <Servo.h>
Servo myServo;
String input;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(2,1000,2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();
  
  if (key){
    if (key == '='){
       
      myServo.write(input.toInt());
      input = "";
      delay(3000);
    }
    else {
      input += key;
    }
  }
}
