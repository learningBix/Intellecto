#include <intellecto.h>

Intellecto irrigation;// create an object from the library to use functions

int moistValue; // variable to store value of moisture sensor

void setup() {
  irrigation.pumpBegin(3); //connect pump at port 3
  irrigation.moistBegin(2); //connect moist sensor at port 2
}

void loop() {
  moistValue = irrigation.moistRead(2); //read moist value from sensor

  //if soil gets below 30% moist value,
  //then switch ON the PUMP
  if (moistValue <= 30) {
    irrigation.pumpSet(3, HIGH); //make pump ON
    delay(2000); //keep the pump ON for 2 sec
    irrigation.pumpSet(3, LOW); //make pump OFF
  }
  else //else keep the pump OFF
  {
    irrigation.pumpSet(3, LOW);
  }
}
