
#include <SPI.h>
#include <Ethernet.h>

#include <Servo.h> 
Servo myservo1;  // create servo object to control a servo1
Servo myservo2;  // create servo object to control a servo2


byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x78, 0xEC }; //physical mac address
byte ip[] = { 192, 168, 1, 102 }; // ip in lan
byte gateway[] = { 192, 168, 1, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(84); //server port

String readString; 

//////////////////////

void setup(){


  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();

  myservo1.write(90); //set initial servo1 position if desired
  myservo2.write(90); //set initial servo2 position if desired
  
  myservo1.attach(9);  //the pin for the servo1 control
  myservo2.attach(8);  //the pin for the servo2 control
  //enable serial data print 
  Serial.begin(9600); 
  Serial.println("server servo/pin 9,8 test 1.0"); // so I can keep track of what is loaded
}

void loop()
{
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

          client.println("<H1>Arduino </H1>");
         
         //Servo1 movement
          client.println("<a href=\"/?right\"\">RIGHT</a>");
          client.println("<a href=\"/?center\"\">CENTER</a>"); 
          client.println("<a href=\"/?left\"\">LEFT</a>"); 
          
          //servo2 movement
          client.println("<a href=\"/?up\"\">UP</a>");
          client.println("<a href=\"/?mid\"\">MIDDLE</a>"); 
          client.println("<a href=\"/?down\"\">DOWN</a>"); 

          client.println("</BODY>");
          client.println("</HTML>");
 
          delay(100);
          //stopping client
          client.stop();

          ///////////////////// control arduino pin

          if(readString.indexOf("left") >0)
          {
            myservo1.write(135);
            delay (50);          
            Serial.println(" Turn to Left");
          }
                    
          if(readString.indexOf("center") >0)
          {
            myservo1.write(90);
            delay (50);            
            Serial.println(" Turn to Center");
          }
          if(readString.indexOf("right") >0)
          {
            myservo1.write(45);
            delay (50);            
            Serial.println(" Turn to Right");
          }
          
          
          
          
          if(readString.indexOf("up") >0)
          {
            myservo2.write(135);
            delay (50);            
            Serial.println(" Move Upwards ");
          }
                    
          if(readString.indexOf("mid") >0)
          { 
            myservo2.write(90);
            delay (50);
            Serial.println(" Move to Center");
          }
          
          if(readString.indexOf("down") >0)
          {
            myservo2.write(45);
            delay (50);            
            Serial.println(" Move downwards ");
          }
          
          //clearing string for next read
          readString="";

        }
      }
    }
  }
} 

