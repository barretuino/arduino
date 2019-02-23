#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h> 

int DS18S20_Pin = 8; //DS18S20 Signal pin on digital 2

//Temperature chip i/o
OneWire ds(DS18S20_Pin);  // on digital pin 2

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x9B, 0x36 }; //physical mac address
byte ip[] = { 192, 168, 0, 101 }; // ip in lan
byte gateway[] = { 192, 168, 2, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port

String readString;

int pin = 8; 
int sensor = 1;      //Pino analógico em que o sensor está conectado.
float valorSensor = 0; //variável usada para ler o valor do sensor em tempo real.
boolean ligado = true;

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
    client.println("<center><h1>Supervisório de Temperatura<h1></center>");
    while (client.connected()) {
      if (client.available()) {
          //Lendo o valor do sensor.
          valorSensor = getTemp();  
          client.println("<br>Temperatura ");
          client.println(valorSensor);              
          delay(5000);
          //stopping client
          //client.stop();
      }
    }
    client.println("</body>");
    client.println("</head>");
  }
}
float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
  
}
