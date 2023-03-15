#include <intellecto.h>

Intellecto alarm;// create an object from the library to use functions

int distance; // variable to store value of distance sensed by sonar sensor
int lightValue; // variable to store value of light sensor

// initialise the hardware port connections
void setup() {
  alarm.sonarBegin(1); //connect sonar sensor at port 1
  alarm.lightBegin(2); //connect light sensor at port 2
  alarm.buzzerBegin(3); //connect buzzer at port 3
}

void loop() {
  lightValue = alarm.lightRead(2); //read light value from sensor

  //if light value gets above 50%,
  //then raise the alarm
  if (lightValue >= 50) {
      distance = alarm.sonarRead(1); //read the distance value from sensor
      //if the person wakes up and gets near to sonar snesor, under 30 cm
      //then switch off the alarm
      if(distance <= 30){
        alarm.buzzerSet(3, LOW);
      }
      //else keep the alarm on
      else{
        alarm.buzzerSet(3, HIGH);
      }
  }
}
