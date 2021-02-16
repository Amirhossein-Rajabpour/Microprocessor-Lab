#include <SPI.h>
#define SS1 45
#define SS2 46

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
  Serial.println(" 'Hello World!' from master to Arduino2");
  send_data("Hello World!", SS1);
  delay(200);
}


void send_data(String data, int CS_pin){
  // put the CS_pin low to activate the connection
  digitalWrite(CS_pin, LOW);
  delay(100);

  char data_array[data.length() + 1];
  data.toCharArray(data_array, data.length() + 1);
  for (int i = 0; i < data.length() + 1; i++){
    SPI.transfer(data_array[i]);
    delay(100);
  }
  // put the CS_pin high to deactivate the connection
  digitalWrite(CS_pin, HIGH);
  delay(100);
}
