#include <SPI.h>

char transfer_data[30] = {'1'};
boolean received;
int end_index = 0;

void setup() {
  Serial.begin(9600);
  pinMode(MISO, OUTPUT);
  digitalWrite(MISO,LOW);
  received = false;
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
}

void loop() {
  if (transfer_data[end_index - 1] == '\0' && end_index != 0){
    Serial.println(transfer_data);
    Serial.println("*  *  *  *");
    end_index = 0;
    delay(100);
  }
}

ISR (SPI_STC_vect){
  transfer_data[end_index++] = (char) SPDR; 
  received = true;
}
