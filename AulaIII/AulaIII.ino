/*
   Programa de Entrada de dados de Sensor
    LDR
    */
int pino = A0;
int led = 13;
int led2 = 12;

void setup() {
  pinMode(led, OUTPUT);
 Serial.begin(9600);
}

void loop() {
  int valor = analogRead(pino);
  Serial.print("Leitura de Sensor LDR: ");
  Serial.println(valor);
  
  if(valor >= 400 && valor < 800){
    Serial.println("Luminosidade Agradavel");
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
    if(valor > 800){      
      Serial.println("Muito Claro");
    }else{
      Serial.println("Escuro");
    }
  }
  delay(1000);
}
