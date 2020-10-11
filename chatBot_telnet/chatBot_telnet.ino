/*the  simple chat bot is established between client and server(esp8266) using telnet port 
 * here simple covid chat bot is send data to client about covid cases (not real time data) but intially feed to system
 * when client submit request to server depend upon which the data us send to particular whose requested not all client to server.
 * we have using the visited arrray to check the client the initailly connected or not.....
 */


#include <ESP8266WiFi.h>

//how many clients should be able to telnet to this ESP8266
#define MAX_SRV_CLIENTS 10

const char *ssid = "SSC"; // The SSID (name) of the Wi-Fi network you want to connect to
const char *password = "XXXXXXXXXX123@"; // The password of the Wi-Fi network

WiFiServer server(23);
WiFiClient serverClients[MAX_SRV_CLIENTS];

uint8_t visited[MAX_SRV_CLIENTS]={0};

 char *cov="press following number of covid-19 to covid cases in india\   
                  0 for world cases\n1 for maharashtra\n2 for delhi\n3 for karnataka\n4 for Tamil Nadu\n 5 for uttar pradesh";
            
int str_cmp(const char *s1, const char *s2)
{
   while(*s1)
{
  if(*s1!=*s2)
      break;
   s1++;
   s2++;
}
if(*s1==*s2)
  return 1;
else
   return 0;
}

char *Get_client_data(uint8_t h)
{
  uint8_t g=0;
  char str[255]={0},pt1;
  while(serverClients[h].available())
  {
 pt1=serverClients[h].read();
 if(pt1=='\r')
 {
   str[g]='\0';
     break;
 }
     str[g++]=pt1;
}
  return str;
}

char* get_query( char *id)
{
   if(str_cmp("one",id) || str_cmp("1",id))
      return "maharashtra Tally\n ->total cases=719k\n ->recovered=522k\n  ->Deaths=23,089\n";
    else if(str_cmp("two",id) || str_cmp("2",id))
        return "Delhi Tally\n ->total cases=166k\n ->recovered=138k\n  ->Deaths=4,347\n";
    else if(str_cmp("three",id) || str_cmp("3",id))
        return "karnataka Tally\n ->total cases=300k\n ->recovered=212k\n  ->Deaths=5,091\n";
    else if(str_cmp("four",id)|| str_cmp("4",id))
        return "tamil nadu Tally\n ->total cases=397k\n ->recovered=338k\n  ->Deaths=6,839\n";
   else if(str_cmp("zero",id)|| str_cmp("0",id))
        return "World Tally\n ->total cases=24M\n ->recovered=15.6M\n  ->Deaths=822k\n";
    else if(str_cmp("five",id)|| str_cmp("5",id))
        return "Uttar pradesh Tally\n ->total cases=203k\n ->recovered=149k\n  ->Deaths=3,149\n";
   else if(str_cmp("symptoms",id) || str_cmp("Covid symptoms",id))
       return "=>symptoms\n -->fever\n   -->dry cough\n -->tiredness\n";
     else if (str_cmp("covid",id))
         return cov;
     else 
        return "not found";
   
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
 // Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  server.begin();
  server.setNoDelay(true);
  Serial.print("Ready! Use 'telnet ");
Serial.print(WiFi.localIP());
Serial.println(" 23' to connect");
}

void loop() {
  char *recv;
  char *tr;
  uint8_t sbuf[255]={0};
  size_t len=0;
  uint8_t data=0;
  // put your main code here, to run repeatedly:
uint8_t i;
//check if there are any new upcoming clients
if (server.hasClient())
{
for(i = 0; i < MAX_SRV_CLIENTS; i++)
{
//find those free/disconnected spot
 if (!serverClients[i] || !serverClients[i].connected())
 {
    if(serverClients[i]) 
    serverClients[i].stop();
serverClients[i] = server.available();
Serial.print("New client: "); 
Serial.print(i);
continue;
 }
}


//no free/disconnected spot so reject
WiFiClient serverClient = server.available();
serverClient.stop();
}
for(i = 0; i < MAX_SRV_CLIENTS; i++)
{
if (serverClients[i] && serverClients[i].connected())
{
if(serverClients[i].available())
{
//get data from the telnet client and push it to the UART
recv=Get_client_data(i);

//String line=serverClient.readStringUntil('\r');
//Serial.println(line);
Serial.println(recv);
if(visited[i]==0)
{
 serverClients[i].write("hello i am automated system how may i help you !! enter  covid to know covid cases");
 visited[i]=1;
}
if((str_cmp(recv," ")==0)&& (str_cmp(recv,"\0")==0))
{
  tr=get_query(recv);
  serverClients[i].write(tr);
}
}

}
}
/*if(len=Serial.available()){
//Serial.println(len);
//uint8_t sbuf[255]={0};
Serial.readBytes(sbuf, len);
}
//push UART data to all connected telnet clients
for(i = 0; i < MAX_SRV_CLIENTS; i++){
if (serverClients[i] && serverClients[i].connected()){
serverClients[i].write(sbuf, len);
delay(1);
}
}*/

}
