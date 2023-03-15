#include <intellecto.h>

//define commands for the communication
#define MAGIC_WAND 0xCC //command to be sent to magic wand

Intellecto dolls;// create an object from the library to use functions

//wifi details of magic wand cpu
const char *wifiName = "MAGIC_WAND"; //wifi name
const char *wifiPass = "12345678"; //wifi password
unsigned int localPort = 8888; //local port to listen on

//Static IP address of Wand
IPAddress remote_IP(192, 168, 4, 1);

WiFiUDP udp; //create UDP object


#define MAX_BYTES_TO_RECEIVE 6
#define MAX_BYTES_TO_REPLY 6

byte receiveBuffer[MAX_BYTES_TO_RECEIVE];
byte replyBuffer[MAX_BYTES_TO_REPLY];

// initialise the hardware port connections
void setup() {
  Serial.begin(115200);
    Serial.print("Configuring access point...");
  Serial.println(wifiName);
  WiFi.mode(WIFI_OFF); //turn off WIFI
  // Begin WiFi as client
  WiFi.begin(wifiName, wifiPass);
  WiFi.mode(WIFI_STA);// connect to wand cpu
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
  }
  udp.begin(localPort); // initialize udp
  dolls.servoOneBegin(3); //connect servo motor one at port 3
  dolls.servoTwoBegin(3); //connect servo motor two at port 3
}

void loop() {
  //send command to magic wand to get servo angle
  replyBuffer[0] = MAGIC_WAND; //load command value into packet
  udp.beginPacket(remote_IP, udp.localPort()); //set ip and port number
  udp.write(replyBuffer, 1); //transmit packet
  udp.endPacket(); //close transmission process

  delay(100); //wait for the packet to be received by wand

  while (udp.parsePacket() <= 0); //wait for the reply packet send by wand
  udp.read(receiveBuffer, MAX_BYTES_TO_RECEIVE); //read the packet
  uint8_t servo_angle = receiveBuffer[0]; //get servo angle from first byte of the packet
  Serial.print("Servo angle:- ");
  Serial.print(servo_angle);
 Serial.println(" Received");
  dolls.servoOneMove(servo_angle);
  dolls.servoTwoMove(servo_angle);
}
