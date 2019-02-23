/**
   Potenciometro doméstico
   @autor: Prof. Paulo Barreto
   Calibração
**/
void setup() {
  Serial.begin(9600);
  Serial.println("Inicio ok");
}
  
void loop() {
  // Le valor do pino analógico
  int valorSensor = analogRead(A0);
  Serial.print("valor lido = " );
  Serial.println(valorSensor);
  delay(100);
}
