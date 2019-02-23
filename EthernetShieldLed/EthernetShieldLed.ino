#include <SPI.h>
#include <Ethernet.h>
boolean incoming = 0;

int rele1 = 0;
int rele2 = 0;
int rele3 = 0;
int rele4 = 0;
int rele5 = 0;
int rele6 = 0;
int rele7 = 0;
int rele8 = 0;

#define pin_rly1 2
#define pin_rly2 3
#define pin_rly3 4
#define pin_rly4 5
#define pin_rly5 6
#define pin_rly6 7
#define pin_rly7 8
#define pin_rly8 9

byte mac[] = { 
  0x90, 0xA2, 0xDA, 0x00, 0x9B, 0x36 }; //physical mac address
byte ip[] = { 
  192, 168, 2, 99 }; // ip in lan
byte gateway[] = { 
  192, 168, 2, 1}; // internet access via router
byte subnet[] = { 
  255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port

void setup()
{
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);
  pinMode(pin_rly1, OUTPUT);
  digitalWrite(pin_rly1, LOW);
  pinMode(pin_rly2, OUTPUT);
  digitalWrite(pin_rly2, LOW);
  pinMode(pin_rly3, OUTPUT);
  digitalWrite(pin_rly3, LOW);
  pinMode(pin_rly4, OUTPUT);
  digitalWrite(pin_rly4, LOW);
  pinMode(pin_rly5, OUTPUT);
  digitalWrite(pin_rly5, LOW);
  pinMode(pin_rly6, OUTPUT);
  digitalWrite(pin_rly6, LOW);
  pinMode(pin_rly7, OUTPUT);
  digitalWrite(pin_rly7, LOW);
  pinMode(pin_rly8, OUTPUT);
  digitalWrite(pin_rly8, LOW);
}

void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client)
  {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    String str;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        str.concat(c);

        if(str.endsWith("/1on")) rele1 =1;
        else if(str.endsWith("/1off")) rele1 =0;

        if(str.endsWith("/2on")) rele2 =1;
        else if(str.endsWith("/2off")) rele2 =0;

        if(str.endsWith("/3on")) rele3 =1;
        else if(str.endsWith("/3off")) rele3 =0;

        if(str.endsWith("/4on")) rele4 =1;
        else if(str.endsWith("/4off")) rele4 =0;
        
        if(str.endsWith("/5on")) rele5 =1;
        else if(str.endsWith("/5off")) rele5 =0;
        
        if(str.endsWith("/6on")) rele6 =1;
        else if(str.endsWith("/6off")) rele6 =0;
        
        if(str.endsWith("/7on")) rele7 =1;
        else if(str.endsWith("/7off")) rele7 =0;
        
        if(str.endsWith("/8on")) rele8 =1;
        else if(str.endsWith("/8off")) rele8 =0;

        if (c == '\n' && currentLineIsBlank)
        {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html"); //inicializa o arquivo html
          //client.println("Refresh: 1″); // refresh a pagina a cada 1 seg
          client.println();
          client.println("<H1><center>Barretuino T&eacutecnologia</H1></center><br/>");
          client.println("<center><img src='http://127.0.0.1:8080/arduinoethernetshield.png' alt='Equipamento Acionado' height='62' width='82'></center>");
          //<H1> Tamanho da letra
          //<center> Centraliza o texto que estiver na sequência
          //<br> Quebra de linha
          client.println("<hr width=50%>"); // TRaço centralizado na pagina
          client.println();
          client.println("<UL>"); // iniciar lista não numerada
          if(rele1 == 1)
          {
            client.print("<br><LI><font color=’blue’ size=’5′><a href=http://192.168.2.99/1off/><font color=red><i>Desligar Saida 1</i></center></a>");
            //<LI> Item não numerado
            //<a href=endereço pagina/>texto a ser apresentado</a> link para outra pagina
            digitalWrite(pin_rly1, HIGH);
          }
          else if (rele1 ==0)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://192.168.2.99/1on/>LIGAR SAIDA 1</a>");
            digitalWrite(pin_rly1, LOW);
          }
          if(rele2 == 1)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://192.168.2.99/2off/><font color=red><font color=red><i>Desligar Saida 2</i></font></font></a>");
            digitalWrite(pin_rly2, HIGH);
          }
          else if (rele2 ==0)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://192.168.2.99/2on/>LIGAR SAIDA 2</a>");
            digitalWrite(pin_rly2, LOW);
          }
          if(rele3 == 1)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://192.168.2.99/3off/><font color=red><i>Desligar Saida 3</i></font></a>");
            digitalWrite(pin_rly3, HIGH);
          }
          else if (rele3 ==0)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://192.168.2.99/3on/>LIGAR SAIDA 3</a>");
            digitalWrite(pin_rly3, LOW);
          }
          if(rele4 == 1)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://192.168.2.99/4off/><font color=red><i>Desligar Saida 4</i></font></a>");
            digitalWrite(pin_rly4, HIGH);
          }
          else if (rele4 ==0)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://192.168.2.99/4on/>LIGAR SAIDA 4</a>");
            digitalWrite(pin_rly4, LOW);
          }
          client.println("</UL>");

          break;
        }
        if (c == '\n')
        {
          currentLineIsBlank = true;
        }
        else if (c != '\r')
        {
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}
