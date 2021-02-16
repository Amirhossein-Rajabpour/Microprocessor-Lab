#include <SPI.h>
#define SS1 45
#define SS2 46
#define SS3 47

int temperature1 = 10;
int temperature2 = 15;
int temperature3 = 20;

#include <Servo.h>
Servo myServo1;
Servo myServo2;

int degree1 = 180;  // for servu1. 180 means open and 0 means closed.
int degree2 = 180;  // for servu2. 180 means open and 0 means closed.

void setup() {
  Serial.begin(9600);
  Serial.println("Master Arduino starts!");
  
  pinMode(SS1, OUTPUT);
  pinMode(SS2, OUTPUT);
  pinMode(SS3, OUTPUT);
  
  digitalWrite(SS1, HIGH);
  digitalWrite(SS2, HIGH);
  digitalWrite(SS3, HIGH);
  
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  
  myServo1.attach(2,1000,2000);
  myServo2.attach(3,1000,2000);
}

void loop() {
  
  state_changer(0);
  state_changer(1);

  Serial.print("Temperature 1 is: ");
  Serial.println(temperature1);
  delay(200);

  Serial.print("Temperature 2 is: ");
  Serial.println(temperature2);
  delay(200);

  Serial.print("Temperature 3 is: ");
  Serial.println(temperature3);
  delay(200);
}


void state_changer(int tag){
  if (tag == 0){ // tag is 0. it means that we should manipulate first servu
      double factor = ((double)(degree1/180)) * 3;// generating energy
      temperature1 *= factor;
      temperature2 *= factor;

    if (temperature1 > 400 || temperature2 > 400){// temperatur passed the threshhold.  slaves should be informed!!
      inform_others();
//      delay(3000);
      cooling("reset", 0, 0);
      }
    else{
      degree1 -=  (int)(temperature1/10);
      if (degree1 < 0){
        inform_others();
//        delay(3000);
        cooling("reset", 0, 0);
        }
      else
        cooling("tmp", 10, 0);
      }
    }
  else{ // tag is 1. it means that we should manipulate second servu
      double factor = ((double)(degree2/180)) * 3; // generating energy
      temperature3 *= factor;

    if (temperature2 > 400 || temperature3 > 400){ // temperatur passed the threshhold.  slaves should be informed!!
      inform_others();
//      delay(3000);
      cooling("reset", 0, 1);
      }
    else{
      degree2 -=  (int)(temperature2/10);
      if (degree2 < 0){
        inform_others();
//        delay(3000);
        cooling("reset", 0, 1);
        }
      else
        cooling("tmp", 10, 1);
      }
    }
}

void cooling(String task, int deg, int tag){// releasing energy and make generator cool
  if (task == "reset"){// reset generator
    Serial.print("reseting ...!");
    temperature1 = 10;
    temperature2 = 15;
    temperature3 = 20;
    degree1 = 180;
    degree2 = 180;
    myServo1.write(degree1);
    myServo2.write(degree2);
    }
  else{// cooling tempretures and teurning servu
    temperature2 -= deg;
    if (tag == 0){
      temperature1 -= deg;
      degree1 += deg;
      if (degree1 > 180)
        degree1 = 180;
      myServo1.write(degree1);
      }
    else{
      temperature3 -= deg;
      degree2 += deg;
      if (degree2 > 180)
        degree2 = 180;
      myServo2.write(degree2);
      }
    }
  }

void inform_slaves(int data, int CS_pin){
  // put the CS_pin low to activate the connection
  digitalWrite(CS_pin, LOW);
  delay(100);
  SPI.transfer(data);
  delay(100);
  // put the CS_pin high to deactivate the connection
  digitalWrite(CS_pin, HIGH);
}

// this function informs all slaves to shut down quickly in order to be safe
void inform_others(){
  degree1 = 0;
  degree2 = 0;
  myServo1.write(degree1);
  myServo2.write(degree2);
  int total_temp = temperature1 + temperature2 + temperature3;
  inform_slaves(1, SS1);
  inform_slaves(1, SS2);
  inform_slaves(1, SS3);
  inform_slaves(0, SS1);
  inform_slaves(0, SS2);
  inform_slaves(0, SS3);
  
}
