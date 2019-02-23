  // Inclusão de bibliotecas.   
  #include <Ultrasonic.h>   // inclui biblioteca de manipulação de servos motores.   
  #define echoPin 8 //Pino 13 recebe o pulso do echo   
  #define trigPin 12 //Pino 12 envia o pulso para gerar o echo   
  Ultrasonic ultrasonic(12,8);   
  // Executado na inicialização do Arduino   
  void setup(){   
  Serial.begin(9600); // inicializa a comunicação serial para Debug ou para mostrar dados em um display LCD   
  pinMode(trigPin, OUTPUT);  // define o pino triger como saída.   
  pinMode(echoPin, INPUT);  // define o pino echo como entrada.   
  }   
  // Loop pincipal do Arduino   
  void loop(){   
  Serial.print( ultrasonic.Ranging(CM) ); //exibido no computador qual a medição do sensor. Essa função faz todo os cálculos e fornece as respostas   
  Serial.println( "cm" );// imprime o centímetro no final   
  delay(1000); //espere 1 segundo pra calcular novamente   
  }   
