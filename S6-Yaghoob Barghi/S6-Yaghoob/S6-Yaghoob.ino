const int ledPin5 = 53;
const int ledPin4 = 52;
const int ledPin3 = 51;
const int ledPin2 = 50;
const int ledPin1 = 49;

#include <LiquidCrystal.h> 
#define RS_PIN 13
#define EN_PIN 12
#define D4_PIN 8
#define D5_PIN 9
#define D6_PIN 10
#define D7_PIN 11
LiquidCrystal lcd(RS_PIN, EN_PIN,D4_PIN, D5_PIN,D6_PIN, D7_PIN );

#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'#','0','=','+'}
};
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

String password = "1234567";
String inputPass = "";

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
  pinMode(ledPin4,OUTPUT);
  pinMode(ledPin5,OUTPUT);

  digitalWrite(ledPin1,HIGH);
  digitalWrite(ledPin2,HIGH);
  digitalWrite(ledPin3,HIGH);
  digitalWrite(ledPin4,HIGH);
  digitalWrite(ledPin5,HIGH);
  
  lcd.begin(16,2);
  lcd.clear();
  Serial.begin(9600);
  
  servo1.attach(3,1000,2000);
  servo2.attach(4,1000,2000);
  servo3.attach(5,1000,2000);
  servo4.attach(6,1000,2000);
  servo5.attach(7,1000,2000);

}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.waitForKey();
  if(key == '*' && inputPass != '*'){
    if(inputPass == password){  
      lcd.setCursor(0,1);
      lcd.print("correct password");
      inputPass = "";
      turn0ffEverything();
      }
    else{
        lcd.setCursor(0,1);
        lcd.print(" wrong password! ");
        inputPass = "";
        }
    }
  else if(inputPass == '*' && key == '*'){
       turn0nEverything();
       lcd.clear();
       lcd.print("all set!");
       inputPass = "";
    }
  else if(key == '/'){
    pickFood(inputPass);
    lcd.clear();
    lcd.print(inputPass);
    inputPass = ""; 
    }
  else if(key == '#'){
    lcd.clear();
    inputPass = ""; 
    }
  else{
      inputPass += key;
      lcd.clear();
      lcd.print(inputPass);
    }

}

void turn0ffEverything(){
  
  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,LOW);
  digitalWrite(ledPin3,LOW);
  digitalWrite(ledPin4,LOW);
  digitalWrite(ledPin5,LOW);

  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  servo5.write(0);
  }
void turn0nEverything(){
  
  digitalWrite(ledPin1,HIGH);
  digitalWrite(ledPin2,HIGH);
  digitalWrite(ledPin3,HIGH);
  digitalWrite(ledPin4,HIGH);
  digitalWrite(ledPin5,HIGH);

  servo1.write(+90);
  servo2.write(+90);
  servo3.write(+90);
  servo4.write(+90);
  servo5.write(+90);
  }

void pickFood(String str){ 
    
  if(str == "01"){
    digitalWrite(ledPin1,LOW);
    servo1.write(+180);
    }
  else if(str == "02"){
    digitalWrite(ledPin2,LOW);
    servo2.write(+180);
    }
  else if(str == "03"){
    digitalWrite(ledPin3,LOW);
    servo3.write(+180);
    }
  else if(str == "04"){
    digitalWrite(ledPin4,LOW);
    servo4.write(+180);
    }
  else if(str == "05"){
    digitalWrite(ledPin5,LOW);
    servo5.write(+180);
    }
  }
