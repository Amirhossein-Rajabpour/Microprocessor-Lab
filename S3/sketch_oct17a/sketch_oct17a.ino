#include <LiquidCrystal.h> 
#define RS_PIN 13
#define EN_PIN 12
#define D4_PIN 8
#define D5_PIN 9
#define D6_PIN 10
#define D7_PIN 11
LiquidCrystal lcd(RS_PIN, EN_PIN,D4_PIN, D5_PIN,D6_PIN, D7_PIN );

int row = 0;
int column = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(column,row);
  lcd.print("Amirhosein");
  column++;
  if(column == 6){
    column = 0;
    if(row == 1)
    {row =0;}
      else
      {row = 1;}
    }
  delay(300);

}
