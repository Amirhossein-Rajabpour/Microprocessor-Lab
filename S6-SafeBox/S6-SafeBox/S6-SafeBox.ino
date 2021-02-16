const int ledPin1 = 49;
const int ledPin2 = 50;
//const int buzzer = 53;

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
Servo servo;

String password = "1234";
String inputPass = "";
bool safeClose = true;

int milliSeconds, seconds;
unsigned long startMillis = 0;
int tiemr_close = 10;

void setup() {
  
  // led1 turns on when the door is open
  pinMode(ledPin1,OUTPUT);
  // led2 turns on when the door is closed
  pinMode(ledPin2,OUTPUT);

  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,HIGH);
  
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("close");
  
  pinMode(53, OUTPUT);
  servo.attach(3,1000,2000);
}

void loop(){

  timing();
  show_status();
  
  char key = keypad.getKey();
  if(key){
  
  // for checking password
  if(key == '*' and safeClose){
    if(inputPass == password){  
      
      safeClose = false;
      make_sound();
      startMillis = millis();
  
      lcd.setCursor(0,0);
      lcd.print("correct password");
      delay(1000);
      lcd.print("                ");
      inputPass = "";
      }
    else{
        lcd.setCursor(0,0);
        lcd.print(" wrong password! ");
        inputPass = "";
        }
    }
    
  // for changing password
  else if(key == '+' and !safeClose){
    lcd.clear();
    lcd.print(inputPass);
    password = inputPass;
    inputPass = "";
    lcd.setCursor(0,0);
    lcd.print("pass changed!");
    }
    
  // for changing timer
  else if(key == '/' and !safeClose){
    tiemr_close = inputPass.toInt();
    inputPass = "";
    lcd.setCursor(0,0);
    lcd.print("timer changed!");
    }
    
  // clear and close safe
  else if(key == '#'){
    lcd.clear();
    inputPass = ""; 
    safeClose = true;
    make_sound();
    }
  else{
      lcd.setCursor(0,0);
      inputPass += key;
      lcd.clear();
      lcd.print(inputPass);
    }
  }
}

void timing(){

  unsigned long currentMillis = millis();
  
  if(!safeClose){
    if((currentMillis - startMillis) <= tiemr_close*1000){
      milliSeconds = (tiemr_close*1000 - (currentMillis - startMillis))%1000;
      seconds = ((tiemr_close*1000 - (currentMillis - startMillis))/1000)%60;

      lcd.setCursor(8,1);
      lcd.print(seconds);
      lcd.print(" : ");
      lcd.print(milliSeconds);
      delay(100);
    }
    else{
      safeClose = true;
      inputPass = "";
      lcd.setCursor(0,0);
      lcd.print("                ");
      make_sound(); 
    }
  }
}

void show_status(){
     if(safeClose){
         lcd.setCursor(0,1);
         lcd.print("close");
         digitalWrite(ledPin1,LOW);
         digitalWrite(ledPin2,HIGH);
         servo.write(180);
      }
      else{
         lcd.setCursor(0,1);
         lcd.print("open ");
         digitalWrite(ledPin1,HIGH);
         digitalWrite(ledPin2,LOW);
         servo.write(0);
      }
}
void make_sound(){
  tone(53, 1000, 300);
}
