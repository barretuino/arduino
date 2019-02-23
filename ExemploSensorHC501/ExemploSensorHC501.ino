/*----------------------------------------------------
Exemplo de utilização Sensor HC-SR501 
PASSIVE INFRARED SENSOR WITH ARDUINO
@autor: Prof. Paulo Barreto
@date: 15/05/2015
----------------------------------------------------*/

void setup(){
 pinMode(13,OUTPUT);
 pinMode(2,INPUT);
}

void loop(){
 digitalWrite(13,digitalRead(2));
}
