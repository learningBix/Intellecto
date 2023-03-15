#include <intellecto.h>

Intellecto dustbin;// create an object from the library to use functions

int distance; // variable to store value of distance sensed by sonar sensor

// initialise the hardware port connections
void setup() {
  dustbin.servoOneBegin(3); //connect servo driver at port 3
  dustbin.sonarBegin(1); //connect sonar sensor at port 1
}

void loop() {
  distance = dustbin.sonarRead(1); //read the distance value from sensor

  //if hand is placed under the sensor, under 10 cm
  //then open the lid
  if (distance <= 10) {
    dustbin.servoOneMove(180); //make servo move 180, to open the lid
    delay(5000); //keep it open for 5 sec 
    dustbin.servoOneMove(0); //move servo back to 0, to close the lid
  }
  else //else keep lid closed
  {
    dustbin.servoOneMove(0);
  }
}
