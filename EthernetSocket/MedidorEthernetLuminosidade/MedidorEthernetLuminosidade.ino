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

void setup(){

  pinMode(pin, OUTPUT); //pin selected to control
  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.begin(9600);
  Serial.println("Exemplo de Comunicacão via Ethernet Shield"); // so I can keep track of what is loaded
}

void loop(){
  //Lendo o valor do sensor.
  int valorSensor = analogRead(sensor);
  //Exibindo o valor do sensor no serial monitor.
  //Serial.println(valorSensor); 
  EthernetClient client = server.available();
  if (client) {
     client.println("HTTP/1.1 200 OK"); //send new page
    client.println("Content-Type: text/html");
    client.println();
    client.println("<html>");
    client.println("<head>"); 
    client.println("<title>Exemplo de Automação Arduino com HTML</title>");
    client.println("<meta http-equiv='Content-Type' content='text/html; charset=ISO-8859-1'>");
    client.println("</head>");
    client.println("<body>");
    client.println("<center><h1>Supervisório de Luminosidade<h1></center>");
    while (client.connected()) {
      if (client.available()) {
          valorSensor = analogRead(sensor);
          client.println("<br>Luminosidade ");
          client.println(valorSensor);              
          delay(10000);
          //stopping client
          //client.stop();
      }
    }
    client.println("</body>");
    client.println("</head>");
  }
}
