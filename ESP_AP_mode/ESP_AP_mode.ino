/*The ESp8266 is using Access point mode in this mode it's create it own server and with encryption
 * but internet is not provide to client whose connect to acces point 
 * WiFi.softAP(ssid,pass); to create network
 * we can also set default gateway , ip address , no of client to be connected 
 */


#include<ESP8266WiFi.h>

// we set ESP8266 as an AP using the command WIFI_AP with a custom name (SSID – Service Set IDentifier) and password
const char *ssid = "NIRAJ-ESP"; // The name of the Wi-Fi network that will be created
const char *password = "ESP@1234"; // The password required to connect to it, leave blank for an open network


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.mode(WIFI_AP);  // configure in AP mode
  boolean result = WiFi.softAP(ssid, password);  // It return the bool value 
                                                   //WiFi.softAP(ssid, password, channel, hidden, max_connection)
  if (result == true)
  {
    Serial.println("AP is created");
  }
  else
  {
    Serial.println("Failed to created");
  }
  Serial.print(ssid);
  Serial.println("\" started");
  Serial.print("IP address of AP:\t");
  Serial.println(WiFi.softAPIP()); // return string of IP address of AP  
  Serial.print("MAC address of AP:\t");
  Serial.println(WiFi.softAPmacAddress());  // return  string of MAC address of board

}

void loop()
{
  // put your main code here, to run repeatedly:
Serial.print("The stations connected to soft-AP: ");
Serial.println(WiFi.softAPgetStationNum()); // return count of stations connected to AP
delay(5000);
}
