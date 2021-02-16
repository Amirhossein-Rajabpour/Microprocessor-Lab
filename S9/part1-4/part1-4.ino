#include "pitches.h"
//#include "OdetoJoy.h"
//#include "jingleBells.h"
#include "ey_iran.h"
//#include "TheImperialMarch.h"

float scale = 0;

void setup() {
    pinMode(20, OUTPUT);
}

void loop() {
  if(digitalRead(20) == HIGH) {
    for(int i=0; i<sizeof(melody)/sizeof(int); ++i) {
      if(digitalRead(20) == LOW) {
        noTone(10);
      } else {
        scale = analogRead(A3)/512.0;
        int noteDuration = 1000/noteDurations[i];
        tone(10, (int)(melody[i]*scale), noteDuration);
        delay((int)(noteDuration*1.3));  
      }
    }
  } else{
      noTone(10);
  }
}
