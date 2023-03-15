#include <intellecto.h>

Intellecto hand;// create an object from the library to use functions

//variable to store motion sensor data
int ax;
int raise_ax_g_value = 9000;

// initialise the hardware port connections
void setup() {
  hand.motionBegin(1); //connect motion sensor at port 1
  hand.rgbBegin(3, CC); //connect rgb at port 3
}

void loop() {
  ax = hand.accXRead(); //read acceleration reading in x direction
  //if acceleration exceed raise value
  if (ax >= raise_ax_g_value) {
    hand.rgbSetRed(3, HIGH);  //switch on red light
  }
  else {
    hand.rgbSetRed(3, LOW);  //switch off red light
  }
}
