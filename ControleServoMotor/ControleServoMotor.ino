//*****************************
//Controle de ServoMotor
//@autor: Paulo C. Barreto
//@date: 13/07/2012
//*****************************
#include <Servo.h> 

Servo myservo;  //criação do objeto servo a ser controlado 

int pos = 0;    //posicao inicial

void setup() 
{ 
  myservo.attach(8);  //pino digital do arduino onde o servo motor está conectado. 
  Serial.begin(9600); //abre a porta serial definindo o datarate 9600
} 

void loop() 
{ 
  //Recebendo dados da porta serial
  Serial.print("a");
  if (Serial.available() != 0) {
    //leitura do bite recebido
    pos = Serial.read();

    myservo.write(pos);
  
    //resposta na serial da informação recebida  
    Serial.print("Recebido: ");
    Serial.println(pos, DEC);
  }
} 

