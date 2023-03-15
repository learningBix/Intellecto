#include <intellecto.h>

Intellecto lamp;// create an object from the library to use functions

int lightValue; // variable to store value of light sensor

// initialise the hardware port connections
void setup() {
  lamp.lightBegin(2); //connect light sensor at port 2
  lamp.rgbBegin(3, CC); //connect rgb at port 3
}

void loop() {
  lightValue = lamp.lightRead(2); //read light value from sensor

  //if light value gets below 50%,
  //then switch on the lamp
  if (lightValue <= 50) {
    lamp.rgbSetRed(3, HIGH); //generate red light
  }
  else {
    lamp.rgbSetRed(3, LOW); //switch off light
  }
}
