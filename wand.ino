#include <intellecto.h>

//define commands for the mobile application
#define MAGIC_WAND 0xCC

Intellecto wand;// create an object from the library to use functions

const char *wifiName = "MAGIC_WAND"; //wifi name
const char *wifiPass = "12345678"; //wifi password
unsigned int localPort = 8888; //local port to listen on

WiFiUDP udp; //create UDP object

// Set your Static IP address
IPAddress remote_IP(192, 168, 4, 1);


#define MAX_BYTES_TO_RECEIVE 6
#define MAX_BYTES_TO_REPLY 6

byte receiveBuffer[MAX_BYTES_TO_RECEIVE];
byte replyBuffer[MAX_BYTES_TO_REPLY];

//variable to store acceleration value
int ay;

// initialise the hardware port connections
void setup() {
  Serial.begin(9600);
    Serial.print("Configuring Station point...");
  Serial.println(wifiName);
  WiFi.mode(WIFI_OFF); //turn off WIFI
  WiFi.mode(WIFI_AP);  //Put WIFI In Access Point Mode
  WiFi.softAP(wifiName, wifiPass, 11, 0); //Run the access point with the given ssid and password on channel 11 (do not interfere with others)
  IPAddress myIP = WiFi.softAPIP();
  udp.begin(localPort); // initialize udp
  wand.motionBegin(1); //connect motion sensor at port 1
}

void loop() {
  //if packet is received from dolls to get the servo value
  if (udp.parsePacket()) {
    //read the packet
    int len = udp.read(receiveBuffer, MAX_BYTES_TO_RECEIVE);
    byte command = receiveBuffer[0];
    if (command == MAGIC_WAND) {
      ay = wand.accYRead(); //read acceleration reading in y direction
      byte servo_angle = map(ay, -16000, 16000, 0, 180); //convert acceleration movement into servo angle
      servo_angle = constrain(servo_angle, 0, 180); //limit servo anglo within 0 to 180
      Serial.print("Servo angle:- ");
      Serial.print(servo_angle);
      Serial.println(" Send");
      replyBuffer[0] = servo_angle; //load value into reply packet
      udp.beginPacket(udp.remoteIP(), udp.remotePort()); //initialise communication with ip and port
      udp.write(replyBuffer, 1); //send acknowledgment packet of size 1 byte
      udp.endPacket(); //end communication
    }
    else;
  }
}
