#include <intellecto.h>

//define commands for the mobile application
#define RGB_LED 0xA5
#define ACK_COMMAND 0xE3

Intellecto lamp;// create an object from the library to use functions

const char *wifiName = "SMART_LAMP"; //wifi name
const char *wifiPass = "12345678"; //wifi password
unsigned int localPort = 8888; //local port to listen on

WiFiUDP udp; //create UDP object

// Set your Static IP address
IPAddress remote_IP(192, 168, 4, 1);


#define MAX_BYTES_TO_RECEIVE 6
#define MAX_BYTES_TO_REPLY 6

byte receiveBuffer[MAX_BYTES_TO_RECEIVE];
byte replyBuffer[MAX_BYTES_TO_REPLY];

// initialise the hardware port connections
void setup() {
  WiFi.mode(WIFI_OFF); //turn off WIFI
  WiFi.mode(WIFI_AP);  //Put WIFI In Access Point Mode
  WiFi.softAP(wifiName, wifiPass, 11, 0); //Run the access point with the given ssid and password on channel 11 (do not interfere with others)
  IPAddress myIP = WiFi.softAPIP();
  udp.begin(localPort); // initialize udp
  lamp.rgbBegin(3, CC); //connect rgb at port 3
}

void loop() {
  //if packet is sent from app
  if (udp.parsePacket()) {
    //read the packet
    int len = udp.read(receiveBuffer, MAX_BYTES_TO_RECEIVE);
    byte command = receiveBuffer[0];
    if (command == RGB_LED) {
      int red_colour = receiveBuffer[1]; //read red colour value
      int green_colour = receiveBuffer[2]; //read green colour value
      int blue_colour = receiveBuffer[3]; //read blue colour value
      red_colour = map(red_colour, 0, 255, 0, 100); //convert value into 0-100%
      green_colour = map(green_colour, 0, 255, 0, 100);
      blue_colour = map(blue_colour, 0, 255, 0, 100);
      lamp.rgbSetRed(3, HIGH, red_colour); //set red colour
      lamp.rgbSetGreen(3, HIGH, green_colour); //set green colour
      lamp.rgbSetBlue(3, HIGH, blue_colour); //set blue
      replyBuffer[0] = ACK_COMMAND; //load acknowledgmet command into packet
      udp.beginPacket(udp.remoteIP(), udp.remotePort()); //initialise communication with ip and port
      udp.write(replyBuffer, 1); //send acknowledgment packet of size 1 byte
      udp.endPacket(); //end communication
    }
    else;
  }
}
