#include <intellecto.h>

Intellecto lamp;// create an object from the library to use functions

int soundValue; // variable to store value of sound sensor

// initialise the hardware port connections
void setup() {
  lamp.soundBegin(2); //connect light sensor at port 2
  lamp.rgbBegin(3, CC); //connect rgb at port 3
}

void loop() {
  soundValue = lamp.soundRead(2); //read sound value from sensor

  //if sound value gets above 50%,
  //then switch on the lamp
  if (soundValue >= 50) {
    lamp.rgbSetRed(3, HIGH); //generate red light
  }
  else {
    lamp.rgbSetRed(3, LOW); //switch off light
  }
}
