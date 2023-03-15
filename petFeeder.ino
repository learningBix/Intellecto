#include <intellecto.h>

Intellecto feeder;// create an object from the library to use functions

int distance; // variable to store value of distance sensed by sonar sensor

// initialise the hardware port connections
void setup() {
  feeder.servoOneBegin(3); //connect servo driver at port 3
  feeder.sonarBegin(1); //connect sonar sensor at port 1
}

void loop() {
  distance = feeder.sonarRead(1); //read the distance value from sensor

  //if pet is detected by sensor, under 10 cm
  //then open the lid
  if (distance <= 10) {
    feeder.servoOneMove(180); //make servo move 180, to open the lid
    delay(2000); //keep it open for 2 sec
    feeder.servoOneMove(0); //move servo back to 0, to close the lid
  }
  else //else keep lid closed
  {
    feeder.servoOneMove(0);
  }
}
