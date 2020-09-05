/*The esp8266 nodemcu scanning all the network in his range 
 * Ut display all sccess point names their MAC addr and signal strength received , and encryption type also  
 * it scan networks in range of RSSI_MIN and RSSI_MAX and displays after 5 sec continuously

 */


#include<ESP8266WiFi.h>

const int RSSI_MAX =-50;// define maximum strength of signal in dBm
const int RSSI_MIN =-100;// define minimum strength of signal in dBm

const int displayEnc=1;// set to 1 to display Encryption or 0 not to display




void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  Serial.println("user ESP Wifi Signal Scan");
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(2000);

  Serial.println("Setup done");
}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.println("Wifi scan started");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("Wifi scan ended");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(")    ");
      Serial.print(WiFi.SSID(i));// SSID
      Serial.print("     ");           
      Serial.print(WiFi.RSSI(i));//Signal strength in dBm  
      Serial.print("dBm (");

      
      Serial.print(dBmtoPercentage(WiFi.RSSI(i)));//Signal strength in %  
      Serial.print(" ");
     Serial.print("%) ");
     Serial.print("    MAC of AP: ");
     Serial.print(WiFi.BSSIDstr(i));//MAC address  (Basic Service Set Identification) 
     Serial.print("    Encryption: ");
     Serial.println(encType(i));
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
  WiFi.scanDelete(); 
}// end loop

int dBmtoPercentage(int dBm)
{
  int quality;
    if(dBm <= RSSI_MIN)
    {
        quality = 0;
    }
    else if(dBm >= RSSI_MAX)
    {  
        quality = 100;
    }
    else
    {
        quality = 2 * (dBm + 100);
   }

     return quality;
}//dBmtoPercentage

 
String encType(int id)
{

String type;
  if(WiFi.encryptionType(id) == ENC_TYPE_WEP){
    type=" WEP";
  }else if(WiFi.encryptionType(id) == ENC_TYPE_TKIP){
    type="WPA / PSK";    
  }else if(WiFi.encryptionType(id) == ENC_TYPE_CCMP){
    type="WPA2 / PSK";    
  }else if(WiFi.encryptionType(id) == ENC_TYPE_AUTO){
    type="WPA / WPA2 / PSK";    
  }else if(WiFi.encryptionType(id) == ENC_TYPE_NONE){
    type="<<OPEN>>";    
  }
  return type;
//1:  ENC_TYPE_WEP – WEP
//2 : ENC_TYPE_TKIP – WPA / PSK
//4 : ENC_TYPE_CCMP – WPA2 / PSK
//7 : ENC_TYPE_NONE – open network
//8 : ENC_TYPE_AUTO – WPA / WPA2 / PSK
}
