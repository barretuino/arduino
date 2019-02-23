/*
   Pisca com Portas Digitais
   @autor Prof. Ms. Paulo Barreto
   @date  18/07/2015
   Curso de Introdução a Arduino
*/
//Declaração de variável
int led1 = 13;
int led2 = 12;
int led3 = 11;
int espera = 500;

//Função Setup: executada quando reset for invocado
void setup() {                
  //inicialização do pino digital de output
  pinMode(led1, OUTPUT);     
  pinMode(led2, OUTPUT); 
  pinMode(led3, OUTPUT); 
}

//Função Loop: executada repetidamente, enquanto não houver
//a execução do reset
void loop() {
  digitalWrite(led1, HIGH); //modifica estado do led para ligado (HIGH eleva o nível de voltagem)
  delay(espera);             //aguarda por tempo 'x' milessegundos
  digitalWrite(led1, LOW);  //modifica estado do led para desligado (LOW diminui o nível de voltagem)
  delay(espera);             //aguarda por tempo 'x' milissegundos
  
  digitalWrite(led2, HIGH); //modifica estado do led para ligado (HIGH eleva o nível de voltagem)
  delay(espera);             //aguarda por tempo 'x' milessegundos
  digitalWrite(led2, LOW);  //modifica estado do led para desligado (LOW diminui o nível de voltagem)
  delay(espera);             //aguarda por tempo 'x' milessegundos
  
  digitalWrite(led3, HIGH); //modifica estado do led para ligado (HIGH eleva o nível de voltagem)
  delay(espera);             //aguarda por tempo 'x' milessegundos
  digitalWrite(led3, LOW);  //modifica estado do led para desligado (LOW diminui o nível de voltagem)
  delay(espera);             //aguarda por tempo 'x' milessegundos
  
  if(espera > 0)
     espera -= 50;
  else
     espera = 500;
}
