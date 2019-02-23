#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x9B, 0x36 }; //physical mac address
byte ip[] = { 192, 168, 2, 99 }; // ip in lan
byte gateway[] = { 192, 168, 2, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port

String readString;

int pin = 9; 
int sensor = 1;      //Pino analógico em que o sensor está conectado.
int valorSensor = 0; //variável usada para ler o valor do sensor em tempo real.
boolean ligado = true;

//////////////////////

void setup(){

  pinMode(pin, OUTPUT); //pin selected to control
  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  //the pin for the servo co
  //enable serial data print
  Serial.begin(9600);
  Serial.println("Exemplo de Comunicacão via Ethernet Shield"); // so I can keep track of what is loaded
}

void loop(){
  //Lendo o valor do sensor.
  int valorSensor = analogRead(sensor);
  //Exibindo o valor do sensor no serial monitor.
  Serial.println(valorSensor); 
  delay(50);
  
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

          ///////////////////// control arduino pin
          Serial.println(readString); //print to serial monitor for debuging
          if(readString.indexOf("?ligar") >0)//checks for on
          {
            digitalWrite(pin, HIGH);    // set pin 4 high
            Serial.println("On");
            ligado = false;
          }
          else{
            if(readString.indexOf("?desligar") >0)//checks for off
            {
              digitalWrite(pin, LOW);    // set pin 4 low
              Serial.println("Off");
              ligado = true;
            }
          }
          //clearing string for next read
          readString="";

          ///////////////

          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html>");
          client.println("<head>");
          client.println("<title>Exemplo de Automação Arduino com HTML</title>");
          client.println("<meta http-equiv='Content-Type' content='text/html; charset=ISO-8859-1'>");
          client.println("<link rel='stylesheet' type='text/css' href='http://www.robocore.net/upload/projetos/RemoteAutomationV1.0.css' />");
          client.println("<script type='text/javascript' src='http://www.robocore.net/upload/projetos/RemoteAutomationV1.0.js'></script>");
          client.println("</head>");
          client.println("<body>");
          client.println("<center><h1>Olha - Exemplo realizado com integra&ccedil;&atilde;o com Hardware Livre e HTML<h1></center>");
          client.println("<center><h1>Luminosidade ");
          client.println(valorSensor);
          client.println("</h1></center>");
          client.println("<div id='wrapper'>Exemplo de Automa&ccedil;&atilde;o Arduino com HTML");
          client.print("<div id='rele'></div><div id='estado' style='visibility: hidden;'>");
          client.print(ligado);
          client.println("</div>");
          client.println("<div id='botao'></div>");
          client.println("</div>");
          client.println("<script>AlteraEstadoRele()</script>");
          client.println("</body>");
          client.println("</head>");

          delay(1);
          //stopping client
          client.stop();
        }
      }
    }
  }
}

