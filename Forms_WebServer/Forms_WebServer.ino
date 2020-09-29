/*this code create a simple forms in webpage using esp8266 
 * the forms arguments such as name and password are  pass to url handler
 * it gets display in Serial monitor 
 * 
*/


#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include<ESP8266mDNS.h>


const char *ssid = "SSC"; // The SSID (name) of the Wi-Fi network you want to connect to
const char *password = "XXXXXXXXXX123@"; // The password of the Wi-Fi network

ESP8266WebServer server(80); //Server on port 80 default port of HTTP protocols

const String main_page="<!DOCTYPE html>\
<html>\
<body>\
<h2>my first forms<h2>\
<h3> HTML Form ESP8266</h3>\
<form action=\"/action_page\" method=\"GET\">\
  <label for=\"fname\">First name:</label><br>\
  <input type=\"text\" name=\"fname\" value=\"\">\
  <br>\
  <label for=\"lname\">Last name:</label><br>\
  <input type=\"text\" name=\"lname\" value=\"\">\
  <br><br>\
  <input type=\"submit\" value=\"Submit\">\
</form>\
</body>\
</html>";

const String action_page="<!DOCTYPE html>\
<html>\
<body>\
<h1>Form action submitted<h1>\
<h3> submission succesfully......</h3>\
</body>\
</html>";

void handleRoot()
{
  Serial.println("the root called");
  server.send(200, "text/html", main_page); //Send web page
}
void handleForm()
{
  Serial.println("the submit handler");
  String firstName = server.arg("fname"); 
 String lastName = server.arg("lname"); 
 Serial.print("First Name:");
 Serial.println(firstName);
 Serial.print("Last name");
 Serial.println(lastName);
}
void handle_NotFound()
{
  Serial.println("the server not found");
  server.send(200, "text/plain", "Not found server"); //Send web page
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
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  if(WiFi.status() == WL_CONNECTED) //If WiFi connected to hot spot then start mDNS
  {
    if (MDNS.begin("niraj-esp8266")) {  //Start mDNS with name esp8266
      Serial.println("MDNS started");
    }
else {
Serial.println("Error setting up MDNS responder!");
}
  }
  server.on("/", handleRoot);      //Which routine to handle at root location
  server.on("/action_page", handleForm); //form action is handled here
  server.onNotFound(handle_NotFound);
  server.begin();                  //Start server
  Serial.println("HTTP server started");
   MDNS.addService("http", "tcp", 80);
}

void loop() {
  // put your main code here, to run repeatedly:
 MDNS.update();
server.handleClient();
}
