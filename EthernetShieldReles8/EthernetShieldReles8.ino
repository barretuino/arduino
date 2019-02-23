/**
   Manipulando portas Digitais - Arduino Web
   Prof. Ms. Paulo Barreto
   Data: 30/10/2014
   Exemplo de manipulação de uma Shield de Reles
**/
#include <SPI.h>
#include <Ethernet.h>
boolean incoming = 0;

int led = 0; //armazena o estado do led 0 - low e 1 - high

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x9B, 0x36 }; //Mac Adress - Endereço Físico
byte ip[] = { 192, 168, 0, 199 }; //IP da Shield na Rede
byte gateway[] = { 192, 168, 0, 1 }; //IP do Roteador que prôve o acesso
byte subnet[] = { 255, 255, 0, 0 }; //Máscara de SubNet
EthernetServer server(80); //Porta no Servidor

void setup()
{
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);  
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);  
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);  
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);  
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);  
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);  
}

void loop()
{
  //Instanciando um objeto EthernetClient
  EthernetClient client = server.available();
  if (client)
  {
    //Uma solicitação http termina com uma linha em branco
    boolean currentLineIsBlank = true;
    String str;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        str.concat(c);

        if(str.endsWith("/1on")) led =1;
        else if(str.endsWith("/1off")) led =0;

        if(str.endsWith("/2on")) led =2;
        else if(str.endsWith("/2off")) led =4;

        if(str.endsWith("/3on")) led =4;
        else if(str.endsWith("/3off")) led =5;

        if(str.endsWith("/4on")) led =6;
        else if(str.endsWith("/4off")) led =7;
        
        if(str.endsWith("/5on")) led =8;
        else if(str.endsWith("/5off")) led =9;
        
        if(str.endsWith("/6on")) led =10;
        else if(str.endsWith("/6off")) led =11;
        
        if(str.endsWith("/7on")) led =12;
        else if(str.endsWith("/7off")) led =13;
        
        if(str.endsWith("/8on")) led =14;
        else if(str.endsWith("/8off")) led =15;
        
        if (c == '\n' && currentLineIsBlank)
        {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html"); //inicializa o arquivo html
          //client.println("Refresh: 1"); // refresh a pagina a cada 1 seg
          client.println();
          client.println("<H1><center>Arduino Web - Curso de Extens&atildeo</H1></center><br/>");
          //<H1> Tamanho da letra
          //<center> Centraliza o texto que estiver na sequência
          //<br> Quebra de linha
          client.println("<hr width=50%>"); // Traço centralizado na pagina
          client.println();
          client.println("<UL>"); // iniciar lista não numerada
          if(led == 1)
          {
            client.print("<br><LI><font color=’blue’ size=’5′><a href=http://10.11.6.199/1off/><font color=red><i>Desligar Saida 1</i></center></a>");
            //<LI> Item não numerado
            //<a href=endereço pagina/>texto a ser apresentado</a> link para outra pagina
            digitalWrite(2, HIGH);
          }
          else if (led ==0)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://10.11.6.199/1on/>LIGAR SAIDA 1</a>");
            digitalWrite(2, LOW);
          }
          
          if(led == 3)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://10.11.6.199/2off/><font color=red><font color=red><i>Desligar Saida 2</i></font></font></a>");
            digitalWrite(3, HIGH);
          }
          else if (led ==2)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://10.11.6.199/2on/>LIGAR SAIDA 2</a>");
            digitalWrite(3, LOW);
          }
          
          if(led == 5)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://10.11.6.199/3off/><font color=red><i>Desligar Saida 3</i></font></a>");
            digitalWrite(4, HIGH);
          }
          else if (led ==4)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://10.11.6.199/3on/>LIGAR SAIDA 3</a>");
            digitalWrite(4, LOW);
          }          
          
          if(led == 7)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://10.11.6.199/4off/><font color=red><i>Desligar Saida 4</i></font></a>");
            digitalWrite(5, HIGH);
          }
          else if (led ==6)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://10.11.6.199/4on/>LIGAR SAIDA 4</a>");
            digitalWrite(5, LOW);
          }

          if(led == 9)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://10.11.6.199/5off/><font color=red><i>Desligar Saida 5</i></font></a>");
            digitalWrite(6, HIGH);
          }
          else if (led ==8)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://10.11.6.199/5on/>LIGAR SAIDA 5</a>");
            digitalWrite(6, LOW);
          }     
          
          if(led == 11)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://10.11.6.199/6off/><font color=red><i>Desligar Saida 6</i></font></a>");
            digitalWrite(7, HIGH);
          }
          else if (led ==10)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://10.11.6.199/6on/>LIGAR SAIDA 6</a>");
            digitalWrite(7, LOW);
          }
          
          if(led == 13)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://10.11.6.199/7off/><font color=red><i>Desligar Saida 7</i></font></a>");
            digitalWrite(8, HIGH);
          }
          else if (led ==12)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://10.11.6.199/7on/>LIGAR SAIDA 7</a>");
            digitalWrite(8, LOW);
          }
          
          if(led == 15)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://10.11.6.199/8off/><font color=red><i>Desligar Saida 8</i></font></a>");
            digitalWrite(9, HIGH);
          }
          else if (led ==14)
          {
            client.println("<br><LI><font color=’blue’ size=’5′><a href=http://10.11.6.199/8on/>LIGAR SAIDA 8</a>");
            digitalWrite(9, LOW);
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
    // Dar tempo ao navegador para receber os dados
    delay(1000);
    //Fechar a conexão
    client.stop();
  }
}
