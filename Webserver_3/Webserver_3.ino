/* In this program we controlling two  on board led D0(which is near RST  switch) and led D4(which is near to esp8266 chip) using the Esp 8266 Web server  buit in class function 
 *  first we create object of ESP8266webserver server(80)
 *  giving parameters  server.on(url,Thandler function) function with /=root  and example /led0n /ledoff and extra different web pages to display with differebt URL
 *  sever.begin(80) start the server at particular port name or without port name server.begin()  
 *  the led are on and off using webpage button function without using GET and POST function 
 *  server.handleclient() function are using to handle diffrerent client request
 *  server.send(HTTp code,"text/html" or "text/html", string containning html code or plain text
*/
#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>

const char *ssid = "SSC"; // The SSID (name) of the Wi-Fi network you want to connect to
const char *password = "XXXXXXXXXX123@"; // The password of the Wi-Fi network

uint8_t LED1=D0;       // declare LED   near to RST on nodemcw
uint8_t LED2=D4;       // Declare LED near to esp8266 chip   

ESP8266WebServer server(80); //Server on port 80 default port of HTTP protocols
//ESP8266WebServer server(100);
bool LED1status=LOW;
bool LED2status=LOW;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
   pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
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
    //server.begin(100); 
   server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.onNotFound(handle_NotFound);
  server.begin();                  //Start ser
  Serial.println("HTTP server started");
}

void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();
 if(LED1status)
  {digitalWrite(LED1, LOW);}
  else
  {digitalWrite(LED1, HIGH);}
  
  if(LED2status)
  {digitalWrite(LED2, LOW);}
  else
  {digitalWrite(LED2, HIGH);}
}

void handle_OnConnect() {
  LED1status = LOW;
  LED2status = LOW;
  Serial.println("GPIO7 Status: OFF | GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status)); 
}

void handle_led1on() {
  LED1status = HIGH;
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(true,LED2status)); 
}

void handle_led1off() {
  LED1status = LOW;
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(false,LED2status)); 
}

void handle_led2on() {
  LED2status = HIGH;
  Serial.println("GPIO6 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,true)); 
}

void handle_led2off() {
  LED2status = LOW;
  Serial.println("GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,false)); 
}

void handle_NotFound(){
  server.send(404, "text/html", "<HTML> <HEAD><TITLE> hello wrong address </TITLE> </HEAD> <BODY><CENTER> <h1 style=\"color:#ff6845;\">OOPS SOMETHING WRONG HAPPEN.... </h1></CENTER> </BODY></HTML>");
}

String SendHTML(uint8_t led1stat,uint8_t led2stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
  ptr +="<h3>Using Station Mode connected to SSC networks) Mode</h3>\n";
  
   if(led1stat)
  {ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
