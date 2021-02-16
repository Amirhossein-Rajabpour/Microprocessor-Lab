#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'c','0','=','+'}
};
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const byte ledPin1 = A0;
const byte ledPin2 = A1;
const byte ledPin3 = A2;
const byte ledPin4 = A3;
const byte ledPin5 = A4;
const byte ledPin6 = A5;
const byte ledPin7 = A6;
const byte ledPin8 = A7;
const byte ledPin9 = A8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
  pinMode(ledPin4,OUTPUT);
  pinMode(ledPin5,OUTPUT);
  pinMode(ledPin6,OUTPUT);
  pinMode(ledPin7,OUTPUT);
  pinMode(ledPin8,OUTPUT);
  pinMode(ledPin9,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();
  if (key){
    Serial.println(key);
    switch(key){
      case '1':
        digitalWrite(ledPin1,HIGH);
        break;
      case '2':
        digitalWrite(ledPin2,HIGH);
        break;
      case '3':
        digitalWrite(ledPin3,HIGH);
        break;
      case '4':
        digitalWrite(ledPin4,HIGH);
        break;
      case '5':
        digitalWrite(ledPin5,HIGH);
        break;
      case '6':
        digitalWrite(ledPin6,HIGH);
        break;
      case '7':
        digitalWrite(ledPin7,HIGH);
        break;
      case '8':
        digitalWrite(ledPin8,HIGH);
        break;
      case '9':
        digitalWrite(ledPin9,HIGH);
        break;
      case 'c':
        digitalWrite(ledPin1,LOW);
        digitalWrite(ledPin2,LOW);
        digitalWrite(ledPin3,LOW);
        digitalWrite(ledPin4,LOW);
        digitalWrite(ledPin5,LOW);
        digitalWrite(ledPin6,LOW);
        digitalWrite(ledPin7,LOW);
        digitalWrite(ledPin8,LOW);
        digitalWrite(ledPin9,LOW);
        break;
    }
    }
    if (Serial.available() > 0){
      char input = Serial.read();
      Serial.println(input);
      switch(input){
      case '1':
        digitalWrite(ledPin1,HIGH);
        break;
      case '2':
        digitalWrite(ledPin2,HIGH);
        break;
      case '3':
        digitalWrite(ledPin3,HIGH);
        break;
      case '4':
        digitalWrite(ledPin4,HIGH);
        break;
      case '5':
        digitalWrite(ledPin5,HIGH);
        break;
      case '6':
        digitalWrite(ledPin6,HIGH);
        break;
      case '7':
        digitalWrite(ledPin7,HIGH);
        break;
      case '8':
        digitalWrite(ledPin8,HIGH);
        break;
      case '9':
        digitalWrite(ledPin9,HIGH);
        break;
      case 'c':
        digitalWrite(ledPin1,LOW);
        digitalWrite(ledPin2,LOW);
        digitalWrite(ledPin3,LOW);
        digitalWrite(ledPin4,LOW);
        digitalWrite(ledPin5,LOW);
        digitalWrite(ledPin6,LOW);
        digitalWrite(ledPin7,LOW);
        digitalWrite(ledPin8,LOW);
        digitalWrite(ledPin9,LOW);
        break;
    }
      }
    
  
}
