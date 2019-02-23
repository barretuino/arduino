 /**************************************************************
   Projeto Arduino Acionamento de Shield Rele de 4.
   @autor Prof. Ms. Paulo Barreto
   @date  23/05/2018
**************************************************************/

int val;

void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);  //Rele 1
  pinMode(3, OUTPUT);  //Rele 2
  pinMode(4, OUTPUT);  //Rele 3
  pinMode(5, OUTPUT);  //Rele 4
  menu();
}

void loop()
{
  if (Serial.available()) {
    val = (int)Serial.read();
    //Relé 1
    if (val == 49) {
      digitalWrite(2, HIGH);      
    } 
    if (val == 50) {
      digitalWrite(2, LOW);
    }
    //Relé 2
    if (val == 51) {
      digitalWrite(3, HIGH);
    } 
    if (val == 52) {
      digitalWrite(3, LOW);
    }
    //Relé 3
    if (val == 53) {
      digitalWrite(4, HIGH);
    } 
    if (val == 54) {
      digitalWrite(4, LOW);
    }
    //Relé 4
    if (val == 55) {
      digitalWrite(5, HIGH);
    } 
    if (val == 56) {
      digitalWrite(5, LOW);
    }
    if(val == 48){
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
    }
  }else{
    delay(1000);
  }
}

void menu(){
    Serial.println("************************");
    Serial.println("** 1 - Liga Rele 1    **");
    Serial.println("** 2 - Desliga Rele 1 **");
    Serial.println("** 3 - Liga Rele 2    **");
    Serial.println("** 4 - Desliga Rele 2 **");
    Serial.println("** 5 - Liga Rele 3    **");
    Serial.println("** 6 - Desliga Rele 3 **");
    Serial.println("** 7 - Liga Rele 4    **");
    Serial.println("** 8 - Desliga Rele 4 **");
    Serial.println("** 9 - Desliga Todos  **");
    Serial.println("** 0 - Ligar Todos    **");
    Serial.println("************************");
}
