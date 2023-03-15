#include <intellecto.h>

Intellecto dispenser;// create an object from the library to use functions

int distance; // variable to store value of distance sensed by sonar sensor

void setup() {
  dispenser.pumpBegin(3); //connect pump at port 3
  dispenser.sonarBegin(1); //connect sonar sensor at port 1
}

void loop() {
  distance = dispenser.sonarRead(1); //read the distance value from sensor

  //if hand is placed under the sensor, under 10 cm
  //then switch ON the PUMP
  if (distance <= 10) {
    dispenser.pumpSet(3, HIGH); //make pump ON
    delay(1000); //keep the pump ON for 1 sec
    dispenser.pumpSet(3, LOW); //make pump OFF
    delay(1000); //wait for 1 sec, for the hand to be removed
  }
  else //else keep the pump OFF
  {
    dispenser.pumpSet(3, LOW);
  }
}
