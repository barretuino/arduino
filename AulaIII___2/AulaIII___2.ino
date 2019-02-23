int val;
void setup() {
 Serial.begin(9600);
 pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
 pinMode(4, OUTPUT);
 pinMode(5, OUTPUT);
 menu();//Chamada a Função menu()
}

void loop() {
  if(Serial.available()){
  val = (int)Serial.read(); 
   if(val == 49){//Liga Rele 1
     digitalWrite(2,HIGH);
   }
   if(val == 50){//Desliga Rele 1
     digitalWrite(2,LOW);
   }
  }else{  
    delay(1000);
  }
}
void menu(){
  Serial.println("Menu");
  Serial.println("1 - Liga Rele 1");
  Serial.println("2 - Desliga Rele 1");
}
