//zoomkat 3-17-12
//simple button GET server code to control servo and arduino pin 5
//for use with IDE 1.0
//open serial monitor to see what the arduino receives
//use the \ slash to escape the " in the html 
//address will look like http://192.168.1.102:84 when submited
//for use with W5100 based ethernet shields
//Powering a servo from the arduino usually DOES NOT WORK.
//note that the below bug fix may be required
// http://code.google.com/p/arduino/issues/detail?id=605 

#include <SPI.h>
#include <Ethernet.h>

#include <Servo.h> 
Servo myservo;  // create servo object to control a servo 

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
byte ip[] = { 192, 168, 1, 102 }; // ip in lan
byte gateway[] = { 192, 168, 1, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(84); //server port

String readString; 

//////////////////////

void setup(){

  pinMode(5, OUTPUT); //pin selected to control
  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();

  myservo.write(90); //set initial servo position if desired
  myservo.attach(7);  //the pin for the servo co
  //enable serial data print 
  Serial.begin(9600); 
  Serial.println("server LED test 1.0"); // so I can keep track of what is loaded
}

void loop(){
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {

          //store characters to string 
          readString += c; 
          //Serial.print(c);
        } 

        //if HTTP request has ended
        if (c == '\n') {

          ///////////////
          Serial.println(readString); //print to serial monitor for debuging 

          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();

          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<TITLE>Arduino GET test page</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY>");

          client.println("<H1>Zoomkat's simple Arduino button</H1>");
          
          // DIY buttons
          client.println("<a href=\"/?on\"\">ON</a>"); 
          client.println("<a href=\"/?off\"\">OFF</a><br />"); 

          // mousedown buttons
          client.println("<br><input type=\"button\" value=\"ON\" onmousedown=\"location.href ('/?on');\"/>"); 
          client.println("<input type=\"button\" value=\"OFF\" onmousedown=\"location.href ('/?off');\"/>");        
          
          // mousedown radio buttons
          client.println("<br><br><input type=\"radio\" value=\"ON\" onmousedown=\"location.href ('/?on');\"\">ON</>"); 
          client.println("<input type=\"radio\" value=\"OFF\" onmousedown=\"location.href ('/?off');\"\">OFF</>");        

          client.println("</BODY>");
          client.println("</HTML>");

          delay(1);
          //stopping client
          client.stop();

          ///////////////////// control arduino pin
          if(readString.indexOf("on") >0)//checks for on
          {
            myservo.write(40);
            digitalWrite(5, HIGH);    // set pin 5 high
            Serial.println("Led On");
          }
          if(readString.indexOf("off") >0)//checks for off
          {
            myservo.write(140);
            digitalWrite(5, LOW);    // set pin 5 low
            Serial.println("Led Off");
          }
          //clearing string for next read
          readString="";

        }
      }
    }
  }
} 
