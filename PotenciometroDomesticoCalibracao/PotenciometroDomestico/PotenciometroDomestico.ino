/**
    Potenciometro Doméstico
    @autor: Prof. Paulo Barreto
    Usando o potenciometro
**/

int pinoLed = 5;
  
void setup() {
  pinMode(pinoLed, OUTPUT);
}
  
void loop() {
  // Le valor do pino analogico
  int valorSensor = analogRead(A0);
  
  // Mapeia o valor lido para escala 0 a 255
  int valorParaLed = map(valorSensor, 0, 1023, 0, 255);
  
  // Validaçao para que nao sejam extrapolados os valores
  if (valorParaLed < 0){     valorParaLed = 0;   }   if (valorParaLed > 255){
    valorParaLed = 255;
  }
  
  // Faz uma escrita analgica em um pino digital (usa PWM)
  analogWrite(pinoLed, valorParaLed);
  
  delay(10);
}
