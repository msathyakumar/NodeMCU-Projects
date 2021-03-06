#include <ESP8266WiFi.h> 
#include <Servo.h>
const char* ssid = "SATHYA"; //wifi ssid / wifi name
const char* password = "sathya_123"; //wifi password
int ledPin = 16; // GPIO13 


Servo myservo;
// adding positio value for servo motor


int pos = 0; 

WiFiServer server(80); 

   // variable to store the servo position




void setup() { 
  myservo.attach(15);
 Serial.begin(115200); 
 delay(10); 
 pinMode(ledPin, OUTPUT); 
 digitalWrite(ledPin, LOW); 
 // Connect to WiFi network 
 Serial.println(); 
 Serial.println(); 
 Serial.print("Connecting to "); 
 Serial.println(ssid); 
 WiFi.begin(ssid, password); 
 while (WiFi.status() != WL_CONNECTED) { 
   delay(500); 
   Serial.print("."); 
 } 
 Serial.println(""); 
 Serial.println("WiFi connected"); 
 // Start the server 
 server.begin(); 
 Serial.println("Server started"); 
 // Print the IP address 
 Serial.print("Use this URL to connect: "); 
 Serial.print("http://"); 
 Serial.print(WiFi.localIP()); 
 Serial.println("/"); 
} 
void loop() { 
 // Check if a client has connected 
 WiFiClient client = server.available(); 
 if (!client) { 
   return; 
 } 
 // Wait until the client sends some data 
 Serial.println("new client"); 
 while(!client.available()){ 
   delay(1); 
 } 
 // Read the first line of the request 
 String request = client.readStringUntil('\r'); 
 Serial.println(request); 
 client.flush(); 
 // Match the request 
 int value = LOW; 
 if (request.indexOf("/LED=ON") != -1)  { 
   digitalWrite(ledPin, HIGH); 
   value = HIGH; 
 } 
 if (request.indexOf("/LED=OFF") != -1)  { 
   digitalWrite(ledPin, LOW); 
   value = LOW; 
 } 
//For Servo motor
 if (request.indexOf("/SERVO=ON") != -1)  { 
   digitalWrite(ledPin, HIGH); 
   
    myservo.write(150);
    value = HIGH; 
 } 
 if (request.indexOf("/SERVO=OFF") != -1)  { 
   digitalWrite(ledPin, LOW);
    myservo.write(0);
    value = LOW; 
 } 




 
// Set ledPin according to the request 
//digitalWrite(ledPin, value); 
 // Return the response 
 client.println("HTTP/1.1 200 OK"); 
 client.println("Content-Type: text/html"); 
 client.println(""); //  do not forget this one 
 client.println("<!DOCTYPE HTML>"); 
 client.println("<html>"); 
 client.print("<body style='background: #00979C'>"); 
 client.println("<h1 align ='center'>"); 
 client.println("<font-color='red'>"); 
 client.println("Smart Car Tent using IOT"); 
 client.println("</font>"); 
 client.println("</h1>"); 
 client.println("<bg color ='#00ff00'>"); 
 client.println("</bg>"); 
 client.println("<p align ='center'>"); 
 client.print("Led/Servo is Now: "); 
 client.println("</p>"); 
 if(value == HIGH) { 
   client.println("<p align ='center'>"); 
   client.print("On"); 
   client.println("</p>"); 
 } else { 
   client.println("<p align ='center'>"); 
   client.print("Off"); 
   client.println("</p>"); 
 } 
 client.println("<br><br>"); 
 client.println("<p align ='center'>"); 
 client.println("<a  href=\"/LED=ON\"\"><button>Turn On </button></a>"); 
 client.println("<a  href=\"/LED=OFF\"\"><button>Turn Off </button></a><br /><br/><br/>");  
 client.println("<a  href=\"/SERVO=ON\"\"><button>Turn On Servo </button></a>&nbsp"); 
 client.println("<a  href=\"/SERVO=OFF\"\"><button>Turn Off Servo </button></a><br />");  
 client.println("</p>"); 
 client.println("<p>"); 
 client.println("<marquee direction='right'>"); 
 client.println("Developed by Sathya kumar "); 
 client.println("</marquee>"); 
 client.println("</p>"); 
 client.println("</body>"); 
 client.println("</html>"); 
 delay(1); 
 Serial.println("Client disonnected"); 
 Serial.println(""); 
} 
