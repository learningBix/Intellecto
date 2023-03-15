#include <intellecto.h>

Intellecto doorbell;// create an object from the library to use functions

int proximityValue; // variable to store value of proximity sensor

void setup() {
  doorbell.buzzerBegin(3); //connect buzzer at port 3
  doorbell.proximityBegin(2); //connect proximity sensor at port 2
}

void loop() {
  proximityValue = doorbell.proximityRead(2); //read RLI(reflected light intensity) value from sensor

  //if value gets above 70%
  //then switch ON the buzzer
  if (proximityValue >= 70) {
    doorbell.buzzerSet(3, HIGH); //make buzzer ON
  }
  else //else switch OFF buzzer
  {
    doorbell.buzzerSet(3, LOW); //make buzzer OFF
  }
}
