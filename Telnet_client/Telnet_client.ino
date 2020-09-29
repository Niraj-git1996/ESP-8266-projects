/*The Telnet protocol use the port number 23, by default
 * The esp8266 is connected to same network as the other device 
* the other device send through there telnet port to the esp8266 
* the received data is displayed in serial terminal....
*/

#include <ESP8266WiFi.h>

//how many clients should be able to telnet to this ESP8266
#define MAX_SRV_CLIENTS 2
const char *ssid = "SSC"; // The SSID (name) of the Wi-Fi network you want to connect to
const char *password = "XXXXXXXXX123@"; // The password of the Wi-Fi network
WiFiServer server(23);
WiFiClient serverClients[MAX_SRV_CLIENTS];


char *Get_client_data(uint8_t h)
{
  uint8_t g = 0;
  char str[255] = {0}, pt1;
  while (serverClients[h].available())
  {
    pt1 = serverClients[h].read();
    if (pt1 == '\r')
    {
      str[g] = '\0';
      break;
    }
    str[g++] = pt1;
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
  // put your main code here, to run repeatedly:
  uint8_t i;
  //check if there are any new upcoming clients
  if (server.hasClient())
  {
    for (i = 0; i < MAX_SRV_CLIENTS; i++)
    {
      //find those free/disconnected spot
      if (!serverClients[i] || !serverClients[i].connected())
      {
        if (serverClients[i])
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
  for (i = 0; i < MAX_SRV_CLIENTS; i++)
  {
    if (serverClients[i] && serverClients[i].connected())
    {
      if (serverClients[i].available())
      {
        //get data from the telnet client and push it to the UART
        recv = Get_client_data(i);
        //String line=serverClient.readStringUntil('\r');
        //Serial.println(line);
        Serial.println(recv);
      }
    }
  }
}
