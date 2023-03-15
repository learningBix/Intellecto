#include <intellecto.h>

Intellecto guitar;// create an object from the library to use functions

int distance; // variable to store value of distance sensed by sonar sensor

int e4 = 622; //frequency of e4 node
int b3 = 247; //frequency of b3 node
int g3 = 293; //frequency of g3 node
int d3 = 147; //frequency of d3 node
int a2 = 110; //frequency of a2 node
int e2 = 82; //frequency of e2 node


// initialise the hardware port connections
void setup() {
  guitar.buzzerBegin(3); //connect buzzer at port 3
  guitar.sonarBegin(1); //connect sonar sensor at port 1
}

void loop() {
  distance = guitar.sonarRead(1); //read the distance value from sensor

  //if distance is less than or equals to 4, generate tone e4
  if (distance <= 4) {
    guitar.buzzerSet(3, HIGH, e4); //generate e4 node
  }
  //else if distance is less than or equals to 8, generate tone b3
  else if (distance <= 8) {
    guitar.buzzerSet(3, HIGH, b3); //generate b3 node
  }
  //else if distance is less than or equals to 12, generate tone g3
  else if (distance <= 12) {
    guitar.buzzerSet(3, HIGH, g3); //generate g3 node
  }
  //else if distance is less than or equals to 16, generate tone d3
  else if (distance <= 16) {
    guitar.buzzerSet(3, HIGH, d3); //generate d3 node
  }
  //else if distance is less than or equals to 20, generate tone a2
  else if (distance <= 20) {
    guitar.buzzerSet(3, HIGH, a2); //generate a2 node
  }
  //else if distance is less than or equals to 20, generate tone a2
  else if (distance <= 24) {
    guitar.buzzerSet(3, HIGH, e2); //generate e2 node
  }
  //else make it off
  else
  {
    guitar.buzzerSet(3, LOW); //no tone
  }
}
