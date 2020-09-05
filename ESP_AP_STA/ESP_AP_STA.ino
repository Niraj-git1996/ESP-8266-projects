/*In this code esp8266 is used in mode 3 as station and access point mode
 * for connecting station mode ssid and password is given
 * for AP mode ssid and pass is given 
 * the client connect to AP of esp8266 can acces the internet.
 */





#include<ESP8266WiFi.h>

const char *STA_ssid = "SSC"; // The SSID (name) of the Wi-Fi network you want to connect to
const char *STA_password = "XXXXXXXXXX123@"; // The password of the Wi-Fi network

const char *AP_ssid="ESP-NIRAJ";
const char *AP_password="MYESP8266";

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); // Start the Serial communication to send messages to the computer
delay(10);
Serial.println('\n');
WiFi.mode(WIFI_AP_STA);// mode station and acess point mode
boolean result=WiFi.softAP(AP_ssid, AP_password);// access point begin
WiFi.begin(STA_ssid, STA_password);// station begin
 Serial.print("Connecting to AP ");
Serial.print(STA_ssid); Serial.println(" ...");
int i = 0;
while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
delay(1000);
Serial.print(++i); Serial.print(' ');
}
Serial.println('\n');
Serial.println(" station Connection established to  AP!");
  Serial.print("IP address of ESP:\t");
Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer
Serial.print("the MAC addr of station AP: ");
Serial.println(WiFi.BSSIDstr());
if (result == true)
  {
    Serial.println("AP is created");
  }
  else
  {
    Serial.println("Failed to created AP");
  }
  Serial.print(AP_ssid);
  Serial.println("\" started");
  Serial.print("IP address of soft AP:\t");
Serial.println(WiFi.softAPIP()); // return string of IP address of AP
  Serial.print("MAC address of soft AP:\t");
  Serial.println(WiFi.softAPmacAddress());  // return  string of MAC address of board
  
}


void loop() 
{
  // put your main code here, to run repeatedly:
Serial.print("the Signal strength station: ");
Serial.print(WiFi.RSSI()); Serial.print("dBm\n");
Serial.print("The stations connected to soft-AP: ");
Serial.println(WiFi.softAPgetStationNum()); // return count of stations connected to AP
delay(5000);
}
