 /**************************************************************
Projeto Arduino sensor de Umidade
Autor: Prof. Paulo Barreto
**************************************************************/
int sensor = 0;      //Pino analógico em que o sensor está conectado.
int valorSensor = 0; //variável usada para ler o valor do sensor em tempo real.

//Função setup, executado uma vez ao ligar o Arduino.
void setup(){
  //Ativando o serial monitor que exibirá os valores lidos no sensor.
  Serial.begin(9600); 
}

//Função loop, executado enquanto o Arduino estiver ligado.
void loop(){
 
  //Lendo o valor do sensor.
  int valorSensor = analogRead(sensor);

  if (valorSensor > 300 && valorSensor <= 750){
    Serial.println("Terreno molhado adequadamente");
  }else{
    if (valorSensor > 750){
      Serial.println("Terreno enxarcado");
    }else{
      Serial.println("Terreno seco, molhar");
    }
  }

  //Exibindo o valor do sensor no serial monitor.
  Serial.println(valorSensor);
 
  delay(1000);
}
