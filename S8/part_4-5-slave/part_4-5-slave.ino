#include <SPI.h>

uint8_t transfer_data;
boolean received;

void setup() {
  Serial.begin(9600);
  pinMode(MISO, OUTPUT);
  digitalWrite(MISO,LOW);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
  received = false;
}

void loop() {
    if (received){
      Serial.println(transfer_data);
      Serial.println("*  *  *  *");
    }
    delay(100);
}

ISR (SPI_STC_vect){
  transfer_data = SPDR; 
  received = true;
}
