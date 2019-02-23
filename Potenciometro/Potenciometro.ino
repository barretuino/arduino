 /*
Pisca / Pisca com velocidade controlada
por um potenciometro
*/

int ledAzul = 8;        
int potenciometro = 2;
int tempoDeEspera = 0;

void setup() {
  pinMode(ledAzul,OUTPUT); 
}

void loop() {

  //Leitura do valor do potenciômetro que é usada como delay
  tempoDeEspera = analogRead(potenciometro);
 
  digitalWrite(ledAzul, HIGH);
  delay(tempoDeEspera);
  digitalWrite(ledAzul, LOW);
  delay(tempoDeEspera);
} 
