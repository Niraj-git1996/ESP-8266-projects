/*the DNS(Domain name system) used to replace ip address with name of server it became easily of user to remember of name . 
 * the esp8266 uses same by mDNS server to replace station ip address by domain name we set on that
 * here MDNS.begin("name_domain"); begin to used.
 */

#include<ESP8266WiFi.h>
#include<ESP8266mDNS.h>


const char* ssid = "SSC"; // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "XXXXXXXXXXX123@"; // The password of the Wi-Fi network




void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); // Start the Serial communication to send messages to the computer
delay(10);
Serial.println('\n');
WiFi.mode(WIFI_STA);    /// select mode to configure the esp8266 in station mode and connect to AP
WiFi.begin(ssid, password); // Connect to the network
Serial.print("Connecting to ");
Serial.print(ssid); Serial.println(" ...");
int i = 0;
while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
delay(1000);
Serial.print(++i); Serial.print(' ');
}
Serial.println('\n');
Serial.println("Connection established!");
Serial.print("IP address of ESP:\t");
Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer
if(!MDNS.begin("esp8266"))
{
  Serial.println("Error setting up the mDNS responder ");
}
else
   Serial.println("mDNS responder started ");
   
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print("the Signal strength: ");
Serial.print(WiFi.RSSI()); Serial.print("dBm\n");
delay(3000);
}
