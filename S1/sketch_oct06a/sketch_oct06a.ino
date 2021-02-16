const int ledPin1 = 6;
const int ledPin2 = 5;
const int ledPin3 = 4;
const int ledPin4 = 3;
const int ledPin5 = 2;
const int ledPin6 = 1;
const int ledPin7 = 0;

const int input1_pin = 10;
const int input2_pin = 11;
const int input3_pin = 12;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
  pinMode(ledPin4,OUTPUT);
  pinMode(ledPin5,OUTPUT);
  pinMode(ledPin6,OUTPUT);
  pinMode(ledPin7,OUTPUT);

  pinMode(input1_pin,INPUT);
  pinMode(input2_pin,INPUT);
  pinMode(input3_pin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(input1_pin)==HIGH){
    digitalWrite(ledPin1,HIGH);
    delay(1000);
    digitalWrite(ledPin2,HIGH);
    delay(1000);
    digitalWrite(ledPin3,HIGH);
    delay(1000);
    digitalWrite(ledPin4,HIGH);
    delay(1000);
    digitalWrite(ledPin5,HIGH);
    delay(1000);
    digitalWrite(ledPin6,HIGH);
    delay(1000);
    digitalWrite(ledPin7,HIGH);
    delay(1000);
    }
    if(digitalRead(input2_pin)==HIGH){
    digitalWrite(ledPin7,HIGH);
    delay(1000);
    digitalWrite(ledPin6,HIGH);
    delay(1000);
    digitalWrite(ledPin5,HIGH);
    delay(1000);
    digitalWrite(ledPin4,HIGH);
    delay(1000);
    digitalWrite(ledPin3,HIGH);
    delay(1000);
    digitalWrite(ledPin2,HIGH);
    delay(1000);
    digitalWrite(ledPin1,HIGH);
    delay(1000);
    }
    if(digitalRead(input3_pin)==HIGH){
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin2,LOW);
    digitalWrite(ledPin3,LOW);
    digitalWrite(ledPin4,LOW);
    digitalWrite(ledPin5,LOW);
    digitalWrite(ledPin6,LOW);
    digitalWrite(ledPin7,LOW);
    }
}
