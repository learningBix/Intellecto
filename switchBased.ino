#include <intellecto.h>

Intellecto lamp;// create an object from the library to use functions

int switchValue; // variable to store value of push switch
int lampState = 0; //variable to store lamp state, initially set to 0(off)

// initialise the hardware port connections
void setup() {
  lamp.switchBegin(1); //connect push switch at port 2
  lamp.rgbBegin(3, CC); //connect rgb at port 3
}

void loop() {
  switchValue = lamp.switchRead(2); //read switch value, pressed - 1, unpressed - 0

  //if perseon presses switch
  if (switchValue == 1) {
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
