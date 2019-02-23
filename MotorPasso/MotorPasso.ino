#include <Stepper.h> // Incluir Biblioteca 'Stepper'
 
// Agora define-se uma instância no Motor de Passo, primeiramente
// o número de passos de rotação. Os próximos 4 números
// referem-se aos pinos conectados ao Arduino.
 
Stepper myStepper(300, 2, 4, 3, 5);
 
void setup(){
}
 
void loop(){
 myStepper.setSpeed(100); // Ajusta a velocidade, este valor pode ser mudado
 myStepper.step(1500); // Numero de passos, sentido horário
 delay(500); // Delay de 0,5seg antes do próximo
 
myStepper.setSpeed(100); // Velocidade agora pela metade
 myStepper.step(-1500); // Numero de passos, agora sentido anti-horário
 delay(500); // Delay de 0,5seg
}
