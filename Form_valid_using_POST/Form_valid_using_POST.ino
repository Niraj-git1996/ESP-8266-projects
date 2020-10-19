/* The node mcu is working in station mode. the mdns server is also used to avoid typing og ipaddress of server repeatedly . the HTTP use POST request  
 *  to send the form value in key=value pair , the forms values are valid using server.arg() this argument are catch at request handler function here is 
 *  (action_page). after the successfully authenticate the user the led control page access given to the user which is simple prototupe of home automation. 
*/
#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include<ESP8266mDNS.h>


const char *ssid = "SSC"; // The SSID (name) of the Wi-Fi network you want to connect to
const char *password = "XXXXXXXXXXXXX23@"; // The password of the Wi-Fi network
const char *pass1="77788";

bool LED1status=LOW;
bool LED2status=LOW;
ESP8266WebServer server(80); //Server on port 80 default port of HTTP protocols

uint8_t pass_cmp(String s)
{
  uint8_t i=0;
  while(pass1[i])
  {
     if(pass1[i]!=s[i])
         break;
         i++;
  }
  if(pass1[i]==s[i])
     return 1;
   else
      return 0;
}
const String main_page="<!DOCTYPE html>\
<html>\
<body style=\"text-align:center;background-color:powderblue;\">\
<h2>My forms validation system<h2>\
<h3> HTML Form ESP8266</h3>\
<form action=\"/action_page\" method=\"post\">\
  <label for=\"fname\" style=\"color:tomato;\">First name:</label><br>\
  <input type=\"text\" name=\"fname\" value=\"\"   maxlength=\"10\" size=\"20\" autofocus required>\
  <br>\
  <label for=\"lname\" style=\"color:tomato;\">last name:</label><br>\
  <input type=\"text\" name=\"lname\" value=\"\"  maxlength=\"10\" size=\"20\" required>\
  <br>\
  <label for=\"pass\" style=\"color:tomato;\">Pass Word:</label><br>\
  <input type=\"password\" name=\"pass\" value=\"\"  maxlength=\"8\" size=\"20\" required>\
  <br><br>\
  <input type=\"reset\"> <input type=\"submit\" value=\"Submit\">\
</form>\
</body>\
</html>";

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
String valid_form(uint8_t flag)
{
 String ptr="<!DOCTYPE html>\n";
 ptr+="<html>\n";
  ptr+="<body  style=\"text-align:center;background-color:#3cb371;\">\n";
if(flag)
{
ptr+="<h1>Form action submited<h1>\n";
ptr+="<h3> submission succesfully your credentials correct......</h3>\n";
}
else
{
ptr+="<h1>Password is enter is wrong <h1>\n";
ptr+="<h3>Go back to home check the password......</h3>\n";
}
ptr+="</body>\n";
ptr+="</html>";
return ptr;
}

void handleRoot()
{
  Serial.println("the root called");
  server.send(200, "text/html", main_page); //Send web page
}
void handleForm()
{
  Serial.println("the submit handler");
  String firstName = server.arg("fname"); 
 //String lastName = server.arg("lname"); 
 String password=server.arg("pass");
 Serial.print("First Name:");
 Serial.println(firstName);
 Serial.print("password:");
 Serial.println(password);
 if(pass_cmp(password))
 {
    Serial.println("password is correct");
    // server.send(200, "text/html", valid_form(1)); //Send web page
     server.sendHeader("Local","/");        // Add a header to respond with a new location for the browser to go to the home page again
      server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
       server.send(302,"text/html", SendHTML(false,false));    
 }
 else
 {
    Serial.println("password is  not correct");
     server.send(200, "text/html", valid_form(0)); //Send web page
 }
  //server.send(200, "text/html", action_page); //Send web page
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
