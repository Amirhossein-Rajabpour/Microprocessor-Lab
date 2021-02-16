#include <SPI.h>

uint8_t transfer_data;
boolean received;

const int ledPin = 2;

void setup() {
  Serial.begin(9600);
  Serial.println("Slave Arduino starts!");
  pinMode(MISO, OUTPUT);
  digitalWrite(MISO,LOW);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
  received = false;

  pinMode(ledPin,OUTPUT);
}

void loop() {
    if (received){
      if (transfer_data != 0){
          digitalWrite(ledPin,HIGH);
          make_sound();
          Serial.println("All devices are shuting down ...");
          Serial.println("Repository is cooling ...");
//      delay(3000);

        }
      else if (transfer_data == 0){
          digitalWrite(ledPin,LOW);
      }
    }

    delay(100);
}

ISR (SPI_STC_vect){
  transfer_data = SPDR; 
  received = true;
}
void make_sound(){
  tone(47, 1000, 300);
}
