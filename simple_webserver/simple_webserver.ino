/*The web server created on esp8266 nodemcu hardware.first we connected modemcu as a station mode.
 * the ESP8266 sebserver haeder file is used the object with server port to start on port 80.
 * the HTTP uses the default port 80.we can use diffferent port also .
 * server.on() with handle url request it chas seperate handler function to handle url
 * the server.begin(),to begin server,the server.send() send the page at  request handler 
 * server.handleClient() to handle the client request.
 */




#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
const char *ssid = "SSC"; // The SSID (name) of the Wi-Fi network you want to connect to
const char *password = "XXXXXXXXX123@"; // The password of the Wi-Fi network

ESP8266WebServer server(80); //Server on port 80


void handleroot() 
{
  //server.send(200, "text/plain", "\thello from esp8266!\n\t you can also go to ip address/pg1 \n \t you can also go ip address/pg2\n");// server.send(200,"text/html",string)
  server.send(200, "text/html", "<HTML> <HEAD><TITLE>My first web page</TITLE> </HEAD> <BODY><CENTER> <B>Hello World.... </B></CENTER> </BODY></HTML>");
} 
void First_page()
{
  //server.send(200,"text/plain","\tHello !!! \n\t welcome to page 1 of server");// server.send(200,"text/plain",string);
  server.send(200, "text/html", "<HTML> <HEAD><TITLE>This is first page</TITLE> </HEAD> <BODY><CENTER> <B>Welcome to page 1 this is HTML.... </B></CENTER> </BODY></HTML>");
}
void Second_page()
{
  //server.send(200,"text/plain","\tHello !!! \n \t welcome to page 2 of server");
  server.send(200, "text/html", "<HTML> <HEAD><TITLE>This is Second page</TITLE> </HEAD> <BODY><CENTER> <B>Welcome to page 2 this is HTML.... </B></CENTER> </BODY></HTML>");
}
void SecThird_page()
{
  server.send(200, "text/html", "<HTML> <HEAD><TITLE>This is third page inside second</TITLE> </HEAD> <BODY><CENTER> <B>Welcome to page 3 inside 2 this is HTML.... </B></CENTER> </BODY></HTML>");
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
 server.on("/", handleroot);      //Which routine to handle at root location
 server.on("/pg1",First_page);
 server.on("/pg2",Second_page);
 server.on("/pg2/pg3",SecThird_page);
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop() 
{
  // put your main code here, to run repeatedly:
server.handleClient();          //Handle client requests
}
