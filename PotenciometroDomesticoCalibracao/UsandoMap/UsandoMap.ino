/**
    Potenciometro Doméstico
    @autor: Prof. Paulo Barreto
    Usando a função map()
**/
void setup() {
  Serial.begin(9600);
  Serial.println("Inicio ok");
}
  
void loop() {
  // Le valor do pino analógico
  int valorSensor = analogRead(A0);
  
  // Mapeia o valor lido para escala 0 à 100
  int valorModificado = map(valorSensor, 0, 1023, 0, 100);
  
  Serial.print("valor lido = " );
  Serial.println(valorSensor);
  Serial.print("valor modificado = ");
  Serial.println(valorModificado);
  delay(500);
}
