#include <intellecto.h>

Intellecto lamp;// create an object from the library to use functions

int proximityValue; // variable to store value of proximity sensor
int lampState = 0; //variable to store lamp state, initially set to 0(off)

// initialise the hardware port connections
void setup() {
  lamp.proximityBegin(2); //connect proximity sensor at port 2
  lamp.rgbBegin(3, CC); //connect rgb at port 3
}

void loop() {
  proximityValue = lamp.proximityRead(2); //read RLI(reflected light intensity) value from sensor

  //if value gets above 70%, when person waves hand
  if (proximityValue >= 70) {
    delay(2000); // wait for 2 sec, for hand to be removed

    //if lamp is off then make it on
    if (lampState == 0) {
      lamp.rgbSetRed(3, HIGH); //generate red light
      lampState = 1; //update variable with present state
    }
    //else lamp is on, then make it off
    else {
      lamp.rgbSetRed(3, LOW); //generate red light
      lampState = 0; //update variable with present state
    }
  }
  else;
}
