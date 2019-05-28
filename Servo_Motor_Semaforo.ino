#include <Servo.h>
 
Servo motor;

int pinVermelho = 5;
int pinAmarelo = 4;
int pinVerde = 3;

void setup(){ 
	motor.attach(9);
	Serial.begin(9600);
} 

void loop(){  
  digitalWrite(pinVermelho, HIGHT);   
  digitalWrite(pinAmarelo, LOW); 
  digitalWrite(pinVerde, LOW); 
  statusSemaforo(5);
  delay(5000);  
  
  digitalWrite(pinVermelho, LOW); 
  digitalWrite(pinAmarelo, HIGHT);   
  digitalWrite(pinVerde, LOW); 
  statusSemaforo(4);
  delay(3000);  
  
  digitalWrite(pinVermelho, LOW); 
  digitalWrite(pinAmarelo, LOW);   
  digitalWrite(pinVerde, HIGHT); 
  statusSemaforo(3);
  delay(30000);  
} 

void statusSemaforo(int led){
	if(led = 5){//Vermelho
		Serial.println("XXX Pare XX - Fechado :x");
		motor.write(00);
	}else if(led = 4){//Amarelo
		Serial.println("!!! Atencao !!! - Abrindo :|");
		motor.write(45);
	}else{//Verde
		Serial.println(">>> Siga >>> - Aberto :p");
		motor.write(90);
	}
}