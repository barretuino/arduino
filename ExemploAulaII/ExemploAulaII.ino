/*
   Exemplo de implementação de Laço de repetição
    simples (for)
    Autor: Prof. Paulo Barreto
    Data: 02/07/2013
    */
//Declaração de      variáveis
int pin = 13;
int tempo = 1000;
int valor;
//Função principal responsável pelo SETUP
void setup() {
    pinMode(pin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    valor = Serial.read();
    tempo = tempo - valor;
    for(int i = 0; i < 10; i++){
        //Comandos que serão repetidos
       digitalWrite(pin, HIGH);
       delay(tempo);
       digitalWrite(pin , LOW);
       delay(tempo);
       //Desvio de Fluxo
       if(i <=5){
         Serial.print("\nLento ") ;
         Serial.print(tempo);         
       }//Senão
       else{
         Serial.println("Rapido");
         Serial.println(tempo);
       }
       
       tempo = tempo - valor;
    }
    tempo = 1000;
    delay(tempo);
}
