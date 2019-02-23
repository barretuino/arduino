#include <Servo.h>
 
Servo motor;

void setup(){ 
   motor.attach(3);
} 

void loop(){  
  motor.write(160);  
  delay(1000);  
  motor.write(16);
  delay(1000);
} 
