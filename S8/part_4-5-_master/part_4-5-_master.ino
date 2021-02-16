#include <SPI.h>
#define SS1 45
#define SS2 46

int light, temperature, LDR_OUT, LM35_OUT;

void setup() {
  Serial.begin(9600);
  Serial.println("Master Arduino starts!");
  pinMode(SS1, OUTPUT);
  pinMode(SS2, OUTPUT);
  digitalWrite(SS1, HIGH);
  digitalWrite(SS2, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}

void loop() {
  Serial.print("Lights: ");
  LDR_OUT = analogRead(A0);
  light = map(LDR_OUT, 0, 684, 0, 101);
  Serial.println(light);
  send_data(light, SS1);
  delay(200);

  Serial.print("Temperature is: ");
  LM35_OUT = analogRead(A1);
  temperature = map(LM35_OUT, 0, 1023, 0, 500);
  Serial.println(temperature);
  send_data(temperature, SS2);
  delay(200);
}

void send_data(int data, int CS_pin){
  // put the CS_pin low to activate the connection
  digitalWrite(CS_pin, LOW);
  delay(100);
  SPI.transfer(data);
  delay(100);
  // put the CS_pin high to deactivate the connection
  digitalWrite(CS_pin, HIGH);
}
