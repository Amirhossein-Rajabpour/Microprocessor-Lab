#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

//keypad
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'#', '0', '=', '+'}
};
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] {26, 27, 28, 29};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//lcd
#define RS_PIN 9
#define EN_PIN 8
#define D4_PIN 4
#define D5_PIN 5
#define D6_PIN 6
#define D7_PIN 7
LiquidCrystal lcd(RS_PIN, EN_PIN,D4_PIN, D5_PIN,D6_PIN, D7_PIN );

//functions
void timing();
void set_state(int state);
int eepromRead(uint16_t memoryAddress);
void eepromWrite(uint16_t memoryAddress, int data);
void show_status();

#define deviceAddress 0b1010000
String input = "";
int defaultTime = 20;
int defaultState = 1;
boolean is_ended = false;
boolean is_pause = false;
int milliSeconds, seconds;
unsigned long startMillis = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  //led
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  //lcd
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Washing Machine");
  delay(100);

  //read state from eeprom
  int readData = eepromRead(0x0000);
  if(readData != 1 && readData != 2 && readData != 3 && readData != 4){ //nothing was set previously
    eepromWrite(0x0000, defaultState);
    delay(1000);
    eepromWrite(0x0001, defaultTime);
  }
  
  delay(100);

  //read default state and time
  defaultState = eepromRead(0x0000);
  set_state(defaultState);
  defaultTime = eepromRead(0x0001);
}

void loop() {
  timing();
  show_status();
  char key = keypad.getKey();
  if(key){
    //change state
    if(key == '/'){
      is_ended = false;
      startMillis = millis();
      int state = input.toInt();
      set_state(state);
      input = "";
    }
    //change timer
    else if(key == '*'){
      is_ended = false;
      defaultTime = input.toInt();
      eepromWrite(0x0001, defaultTime);
      startMillis = millis();
      delay(100);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("default Time changed");    
      input = "";
    }
    //start timer
    else if(key == '+'){
      is_pause = false;
      startMillis = millis();
    }
    //pause timer
    else if(key == '-'){
      is_pause = true;
    }
    //reset
    else if(key == '='){
      defaultTime = 10;
      defaultState = 1;
      eepromWrite(0x0000, defaultState);
      eepromWrite(0x0001, defaultTime);
      input = "";
    }
    else{
      input += key;
    }
  }
}

void set_state(int state){
  defaultState = state;
  eepromWrite(0x0000, defaultState);
  delay(100);
}

//writing to EEPROM
void eepromWrite(uint16_t memoryAddress, int data){
  Wire.beginTransmission(deviceAddress);
  Wire.write((uint8_t)((memoryAddress & 0xFF00) >> 8)); //MSB
  Wire.write((uint8_t)((memoryAddress & 0x00FF) >> 0)); //LSB
  Wire.write(data);
  Wire.endTransmission(); 
}

//reading from EEPROM
int eepromRead(uint16_t memoryAddress){
  int readData;
  Wire.beginTransmission(deviceAddress);
  Wire.write((uint8_t)((memoryAddress & 0xFF00) >> 8)); //MSB
  Wire.write((uint8_t)((memoryAddress & 0x00FF) >> 0)); //LSB
  Wire.endTransmission();
  Wire.requestFrom(deviceAddress, 1);
  readData = Wire.read();

  return readData;
}

//timer
void timing(){
  unsigned long currentMillis = millis();
  if(!is_ended && !is_pause){
    if((currentMillis - startMillis) <= defaultTime*1000){
      milliSeconds = (defaultTime*1000 - (currentMillis - startMillis))%1000;
      seconds = ((defaultTime*1000 - (currentMillis - startMillis))/1000)%60;

      lcd.setCursor(8,1);
      lcd.print(seconds);
      lcd.print(" : ");
      lcd.print(milliSeconds);
      delay(100);
    }
    else{
      is_ended = true;
    }
  }
  else if(is_pause){
    lcd.clear();
    lcd.setCursor(8,1);
    lcd.print(seconds);
    lcd.print(" : ");
    lcd.print(milliSeconds);
  }
}

void show_status(){
  lcd.clear();
  lcd.setCursor(0, 0);

  if(is_ended){
    lcd.setCursor(0,0);
    lcd.print("state  finished!");
    digitalWrite(19, HIGH);
    digitalWrite(18, HIGH);
    digitalWrite(17, HIGH);
    digitalWrite(16, HIGH);
  }
  else{
  
  if(defaultState == 1){
    digitalWrite(19, HIGH);
    digitalWrite(18, LOW);
    digitalWrite(17, LOW);
    digitalWrite(16, LOW);
    lcd.print("MODE 1:Pre Wash");
  }
  else if(defaultState == 2){
    digitalWrite(19, LOW);
    digitalWrite(18, HIGH);
    digitalWrite(17, LOW);
    digitalWrite(16, LOW);
    lcd.print("MODE 2:Washing");
  }
  else if(defaultState == 3){
    digitalWrite(19, LOW);
    digitalWrite(18, LOW);
    digitalWrite(17, HIGH);
    digitalWrite(16, LOW);
    lcd.print("MODE 3:WaterWash");
  }
  else if(defaultState == 4){
    digitalWrite(19, LOW);
    digitalWrite(18, LOW);
    digitalWrite(17, LOW);
    digitalWrite(16, HIGH);
    lcd.print("MODE 4:Drying");
  }
  }// end of else
}
