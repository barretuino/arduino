/*
   Exemplo Básico com Portas Digitais
   @autor Prof. Ms. Paulo Barreto
   @date  18/07/2015
   Curso de Introdução a Arduino
*/
//Declaração de variável
int led = 13;
int led2 = 12;
int contador = 500;

//Função Setup: executada quando reset for invocado
void setup() {                
  //inicialização do pino digital de output
  pinMode(led, OUTPUT);     
  pinMode(led2, OUTPUT);
}

//Função Loop: executada repetidamente, enquanto não houver
//a execução do reset
void loop() {
  digitalWrite(led, HIGH); //modifica estado do led para ligado (HIGH eleva o nível de voltagem)
  delay(contador);             //aguarda por tempo 'x' segundos
  digitalWrite(led, LOW);  //modifica estado do led para desligado (LOW diminui o nível de voltagem)
  delay(contador);             //aguarda por tempo 'x' segundos
  
  digitalWrite(led2, HIGH);
  delay(contador);
  digitalWrite(led2, LOW);
  delay(contador);
  
  //Comando de desvio de fluxo
  if(contador > 0)
    contador -= 50; //contador = contador - 50;
  else
    contador = 500;
}
