/*the ESP8266WiFi.h library included 
 * which help to call API of wifi processs.
 * In below code the various function are called and called get displayed
 * wifi.begin() func used the ssid_name and it password to connect
 */



#include<ESP8266WiFi.h>
const char* ssid = "SSC"; // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "XXXXXXX123@"; // The password of the Wi-Fi network


void setup()
{
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
Serial.print("Subnet mask: ");
Serial.println(WiFi.subnetMask());
Serial.print("the default gateway: ");
Serial.println(WiFi.gatewayIP());
Serial.print("the host name: ");
Serial.println(WiFi.hostname());
Serial.print("the SSID pass key: ");
Serial.println(WiFi.psk());
Serial.print("the MAC addr of AP: ");
Serial.println(WiFi.BSSIDstr());

}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print("the Signal strength: ");
Serial.print(WiFi.RSSI()); Serial.print("dBm\n");
delay(3000);
}
