 /**************************************************************
   Projeto Arduino Push Button
   @autor Prof. Ms. Paulo Barreto
   @date  18/07/2015
   Curso de IntroduÃ§Ã£o a Arduino
**************************************************************/

int ledPin = 13; // porta 13 em output para o LED
 
int inPin = 2; // porta 2 em input (para o push button)
 
int val = 0; // variável para ler o status do pino
 
void setup() {
 
    pinMode(ledPin, OUTPUT); // declare LED como output
 
    pinMode(inPin, INPUT); // declare pushbutton como input
 
}
 
void loop(){
 
	val = digitalRead(inPin); // ler a entrada de valor
	
	if (val == HIGH) {// verificar se a entrada é alta
 
		digitalWrite(ledPin, LOW); // LED OFF
 
	} else {
 
		digitalWrite(ledPin, HIGH); // LED ON
 
	} 
}