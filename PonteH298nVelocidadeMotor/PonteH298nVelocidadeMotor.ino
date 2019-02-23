/*Pinagem do arduino*/
 
//motor A
int IN1 = 2 ;
int IN2 = 4 ;
int velocidadeA = 3;
 
//motor B
int IN3 = 6 ;
int IN4 = 7 ;
int velocidadeB = 5;
 
//variavel auxiliar
int velocidade = 0;
 
//Inicializa Pinos
void setup(){
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
pinMode(velocidadeA,OUTPUT);
pinMode(velocidadeB,OUTPUT);
}
 
void loop(){
 
/*Exemplo de velocidades no motor A*/
 
//Sentido Horario
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
 
//Alta
analogWrite(velocidadeA,230);
 
//Intermediaria
analogWrite(velocidadeA,150);
 
//Baixa
analogWrite(velocidadeA,80);
 
/*Exemplo de variacao de velocidade no motor B*/
 
//Sentido Horario
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
 
//velocidade de 0 a 255
while (velocidadeB < 255){
analogWrite(velocidadeB,velocidade);
velocidade = velocidade + 10;
delay(50);
}
//velocidade de 255 a 0
while (velocidadeB > 0){
analogWrite(velocidadeB,velocidade);
velocidade = velocidade - 10;
delay(50);
}
}
