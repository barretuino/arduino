//Ethernet Shield para medir temperatura exemplo criado para o site WebTronico.

#include "etherShield.h"
#include "ETHER_28J60.h"

static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};   //Endereço MAC - Camada de Enlace                                                        
static uint8_t ip[4] = {192, 168, 0, 15}; //Endereço IP - Camada de Rede
static uint16_t port = 80; //Porta padrão protocolo HTTP

ETHER_28J60 e;

int analog;
float temperatura;

void setup()
{
  e.setup(mac, ip, port);
}

void loop()
{
  if (e.serviceRequest())
  {
    e.print("<html><head><title>WebServer Simples</title></head><body>");//Instruções HTML.
    e.print("<H1>Temperatura</H1><br/>");
    e.print("Temperatura em Celsius: ");
    analog = analogRead(0);
    temperatura = (analog * 0.00488);  // 5V / 1023 = 0.00488 (precisão do A/D)
    temperatura = temperatura * 100; //Converte milivolts para graus celcius, lembrando que a cada 10mV equi
    e.print(temperatura);
    e.print("<br><br><b>Desenvolvido por Allan Romanato</b></body></html>");
    e.respond();
  }
  delay(100);
}
