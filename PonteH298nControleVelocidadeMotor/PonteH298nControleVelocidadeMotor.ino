#define MOTOR_A 1
#define MOTOR_B 2
#define HORARIO true
#define ANTIHORARIO false
 
//inicializa pinos
void setup(){
 for (int i = 2; i < 8; i++)
 pinMode(i,OUTPUT);
}
 
void loop(){
 
acionaMotor(MOTOR_A,HORARIO, 255);
 acionaMotor(MOTOR_B,ANTIHORARIO, 255);
 
}
 
//funcao para acionamento individual de cada motor
void acionaMotor(int motor, boolean sentido, int velocidade){
 if (motor == MOTOR_A){
 digitalWrite(2,sentido);
 digitalWrite(4,!sentido);
 analogWrite(3,velocidade);
 }
 else if (motor == MOTOR_B){
 digitalWrite(6,sentido);
 digitalWrite(7,!sentido);
 analogWrite(5,velocidade);
 }
}
