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

String password = "1234";
String inputPass = "";

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly: 
  char key = keypad.waitForKey();
  if(key == '*'){
    if(inputPass == password){  
      lcd.setCursor(0,1);
      lcd.print("correct password");
      inputPass = "";
      }
      else{
        lcd.setCursor(0,1);
        lcd.print(" wrong password! ");
        inputPass = "";
        }
    }
    else{
      inputPass += key;
      lcd.clear();
      lcd.print(inputPass);
      }
}
