#include <SoftwareSerial.h>   //Inlcui a biblioteca SoftwareSerial.h
 
#define RxD         6 //Define RxD como 6
#define TxD         7 //Define TxD como 7
 
#define LED_AMARELO    2 //LED_AMARELO_BLINK como 2
#define LED_VERMELHO    3 //LED_VERMELHO_FADE como 3
#define RELE_LAMPADA         4 //RELE_LAMPADA como 4
 
SoftwareSerial blueToothSerial(RxD,TxD); //Instância a biblioteca SoftwareSerial.h
 
void setup()
{

  pinMode(LED_AMARELO, OUTPUT); //Configura o pino 2 como saída
  pinMode(LED_VERMELHO, OUTPUT); //Configura o pino 3 como saída
  pinMode(RELE_LAMPADA, OUTPUT); //Configura o pino 4 como saída
parear_dispositivo(); //Executa a função para parear o dispositivo
}
 
void loop()
{
  char letra; //Variável char para armazenar o caractere recebido
if(blueToothSerial.available()) //Se algo for recebido pela serial do módulo bluetooth
    {
      letra = blueToothSerial.read(); //Armazena o caractere recebido na variável letra
if(letra == 'A') digitalWrite(LED_AMARELO, HIGH); //Se o caractere recebido for a letra A, liga o LED Amarelo
      else if(letra == 'a') digitalWrite(LED_AMARELO, LOW); //Senão se o caractere recebido for a letra a, desliga o LED Amarelo
      else if(letra == 'B') digitalWrite(LED_VERMELHO, HIGH); //Senão se o caractere recebido for a letra B, liga o LED Vermelho
      else if(letra == 'b') digitalWrite(LED_VERMELHO, LOW); //Senão se o caractere recebido for a letra b, delisga o LED Vermelho
      else if(letra == 'C') digitalWrite(RELE_LAMPADA, HIGH); //Senão se o caractere recebido for a letra C, liga a Lâmpada
      else if(letra == 'c') digitalWrite(RELE_LAMPADA, LOW); //Senão se o caractere recebido for a letra c, desliga a Lâmpada
      else if(letra == 'H') digitalWrite(9, LOW);
      else if(letra == 'h') digitalWrite(9, HIGH);
  }
}
 
void parear_dispositivo()
{
  blueToothSerial.begin(38400); // Configura o baud rate do bluetooth como 38400
  blueToothSerial.print("\r\n+STWMOD=0\r\n"); // Configura o módulo bluetooth para trabalhar como slave
  blueToothSerial.print("\r\n+STNA=SeedBTShield\r\n"); // Configura o nome do disopsitivo bluetooth
  blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permite que outros dispositivos encontrem o módulo bluetooth
  blueToothSerial.print("\r\n+STAUTO=0\r\n"); // Desabilita a auto conexão
  delay(2000); // Aguarda 2 segundos
  blueToothSerial.print("\r\n+INQ=1\r\n"); // Habilita modo de paridade
  delay(2000); // Aguarda 2 segundos
  blueToothSerial.flush(); // Dá um flush na serial do módulo bluetooth
}
