/*the webserver is created using the ESP8266 webserver this webpage have some advanced content then previous .
 * 
 */




#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>

const char *ssid = "SSC"; // The SSID (name) of the Wi-Fi network you want to connect to
const char *password = "XXXXXXXXXX123@"; // The password of the Wi-Fi network


ESP8266WebServer server(80); //Server on port 80

String root()
{
  String ptr="<!DOCTYPE html> <HTML>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr+="<TITLE>My first web page using esp 8266</TITLE>\n";
  ptr+="<style>html{ display: inline-block; margin: 0px auto; text-align: center;}\n";
   ptr+="body { background-color:#ffd8d9; background-image:url('https://cdn.pixabay.com/photo/2015/05/23/13/35/road-780544_960_720.jpg') ; background-size:cover;}\n";
   ptr+="h1 { color:#3cb371; font-size:30px; font-family:Georgia,serif; }\n";
   ptr+="h3{color:#6a5acd; font-size:25px; font-family:Impact, Charcoal, sans-serif;}\n";
   ptr+=" h4 { color:#ff0000; font-size:20px; font-family:Helvetica; }</style>\n";
  ptr+="</HEAD><BODY><h1>This is Home page of ESP8266....</h1><hr> <h3>cannot able to display image in html format</h3>\n";
  ptr+="<hr> <h4>can also Go also goto page 1 and page 2 </h4></BODY></HTML>\n";
  return ptr;
}
void handleroot() 
{
  String s=root();
  //server.send(200, "text/plain", "\thello from esp8266!\n\t you can also go to ip address/pg1 \n \t you can also go ip address/pg2\n");// server.send(200,"text/html",string)
  //server.send(200, "text/html", "<HTML> <HEAD><TITLE>My first web page</TITLE> </HEAD> <BODY><CENTER> <B>Hello World.... </B></CENTER> </BODY></HTML>");
  server.send(200,"text/html",s);
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

void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();          //Handle client requests
}
