#include <intellecto.h>

//define commands for the mobile application
#define RELAY 0xA3
#define ACK_COMMAND 0xE3

Intellecto automation;// create an object from the library to use functions

const char *wifiName = "HOME_AUTOMATION"; //wifi name
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
  automation.relayBegin(1); //connect relay at port 1
}

void loop() {
  //if packet is sent from app
  if (udp.parsePacket()) {
    //read the packet
    int len = udp.read(receiveBuffer, MAX_BYTES_TO_RECEIVE);
    byte command = receiveBuffer[0];
    if (command == RELAY) {
      automation.relaySet(1, receiveBuffer[1]); //set relay on/off as per value received from app
      replyBuffer[0] = ACK_COMMAND; //load acknowledgmet command into packet
      udp.beginPacket(udp.remoteIP(), udp.remotePort()); //initialise communication with ip and port
      udp.write(replyBuffer, 1); //send acknowledgment packet of size 1 byte
      udp.endPacket(); //end communication

    }
    else;
  }
}
