
#include <Ethernet.h>
#include <SPI.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  //endereco mac
byte ip[] = { 192, 168, 1, 201 };    //endereço IP
Server server(80);  //criando um objeto do tipo servidor

void setup()
{

  //Serial.begin(9600);
  Ethernet.begin(mac, ip);    //setando o ip e o mac para o arduino ser reconhecido na rede
  server.begin();        // levantando o servidor

}

void loop()
{
  Client client = server.available();    /*servidor esperando uma requisicao, apos a
   requisicao ser encontrada a funcao retorna
   um objeto do tipo client
   */
  if (client) {    //testa se o exeiste

    while (client.connected()) {    //testa se o cliente esta conectado
      while (client.available()) {    //retorna o numero de byte no buffer de entrada

        Serial.print(client.read());    

      }

      client.println("Bem vindo! Curso Arduino WEB");    //envia para o cliente a seguinte String
      delay(2); // dá um tempo para  o cliente receber os caracteres

      while (client.available()) {    //retorna o numero de byte no buffer de entrada

        Serial.print(client.read());    

      }
      delay(2); // dá um tempo para  o cliente receber os caracteres
      client.stop();    //finaliza a conexao
      break;    //sai do loop
    }
    while(1);    //loop infinito para evitar a finalizacao do programa
  }
}
