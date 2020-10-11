/* The telnet clients and server connection are established using esp8266 node mcu connnect in station mode. 
 * the telnet use port 23 by default
 * The class WiFiClient class is used the serverClients object  is created  
 * we can send and received b/w cl and sever
 *  
 */


#include <ESP8266WiFi.h>
//how many clients should be able to telnet to this ESP8266
#define MAX_SRV_CLIENTS 10    // define  the max client to be connected

const char *ssid = "SSC"; // The SSID (name) of the Wi-Fi network you want to connect to
const char *password = "XXXXXXXXXXXX23@"; // The password of the Wi-Fi network

WiFiServer server(23);
WiFiClient serverClients[MAX_SRV_CLIENTS]; // making array of object depend upon clients connected



char *Get_client_data(uint8_t h)
{
  uint8_t g=0;
  char str[255]={0},pt1;
  while(serverClients[h].available())
  {
 pt1=serverClients[h].read();
 if(pt1=='\r')
 {
   str[g]='\0';
     break;
 }
     str[g++]=pt1;
}
  return str;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);
WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
 // Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  server.begin();
  server.setNoDelay(true);
  Serial.print("Ready! Use 'telnet ");
Serial.print(WiFi.localIP());
Serial.println(" 23' to connect");
}

void loop() {
  char *recv;
  char *tr;
  uint8_t sbuf[255]={0};
  size_t len=0;
  uint8_t data=0;
  // put your main code here, to run repeatedly:
uint8_t i;
//check if there are any new upcoming clients
if (server.hasClient())
{
for(i = 0; i < MAX_SRV_CLIENTS; i++)
{
//find those free/disconnected spot
 if (!serverClients[i] || !serverClients[i].connected())
 {
    if(serverClients[i]) 
    serverClients[i].stop();
serverClients[i] = server.available();
Serial.print("New client: "); 
Serial.print(i);
continue;
 }
}


//no free/disconnected spot so reject
WiFiClient serverClient = server.available();
serverClient.stop();
}
for(i = 0; i < MAX_SRV_CLIENTS; i++)
{
if (serverClients[i] && serverClients[i].connected())
{
if(serverClients[i].available())
{
//get data from the telnet client and push it to the UART
recv=Get_client_data(i);

//String line=serverClient.readStringUntil('\r');
//Serial.println(line);
Serial.println(recv);
}
}
}

if(len=Serial.available())  // checking for data in serial buffer and send the data to telnet client connected to router
{
//Serial.println(len);
//uint8_t sbuf[255]={0};
Serial.readBytes(sbuf, len);  // reading byte by byte form buffer
}
//push UART data to all connected telnet clients
for(i = 0; i < MAX_SRV_CLIENTS; i++){
if (serverClients[i] && serverClients[i].connected()) // checking for telnet clients connecte or not
{
serverClients[i].write(sbuf, len);  // write an data to telnet clients form buffer stored memory
delay(1);  // small delay
}
}






}
