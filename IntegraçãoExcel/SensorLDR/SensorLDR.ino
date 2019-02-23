/*
   IntegraÃ§Ã£o de Dados com Excel
   @autor Prof. Ms. Paulo Barreto
   @date  18/07/2015
   Curso de IntroduÃ§Ã£o ao Arduino
   Componentes:  
      Arduino UNO  
      LDR  
      10K resistor  
 */  

int ROW = 0; 
int LABEL = 1; 
int val = 0; 

void setup(){
Serial.begin(9600); 
Serial.println("CLEARDATA"); 
Serial.println("LABEL,Time,val,ROW"); 
}

void loop(){

val = analogRead(A0); 
ROW++; 

Serial.print("DATA,TIME,"); 
Serial.print(val); 
Serial.print(",");
Serial.println(ROW);

if (ROW > 100)
{
   ROW = 0;
   Serial.println("ROW,SET,2"); 
}
delay(200);
}
   
