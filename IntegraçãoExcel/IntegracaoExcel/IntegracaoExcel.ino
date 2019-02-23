/*
   Integração de Dados com Excel
   @autor Prof. Ms. Paulo Barreto
   @date  18/07/2015
   Curso de Introdução ao Arduino
*/

int sensor1 = 5;                                                           //  PINO ANALÓGICO 5
int sensor2 = 4;                                                           //  PINO ANALÓGICO 4
int valor1 = 0;                                                             //  VALOR LIDO NA ENTRADA ANALÓGICA 5
int valor2 = 0;                                                             //  VALOR LIDO NA ENTRADA ANALÓGICA 4
float temp1 = 0;                                                          //  VARIÁVEL QUE RECEBERÁ VALOR CONVERTIDO DO SENSOR 1
float temp2 = 0;                                                          //  VARIÁVEL QUE RECEBERÁ VALOR CONVERTIDO DO SENSOR 2
float tempmedia = 0;                                                   //  TEMPERATURA MÉDIA MEDIDA

//  VARIÁVEIS DA COMUNICAÇÃO SERIAL COM O EXCEL (PLX-DAQ)                  
//  NÃO PODE USAR O "MONITOR SERIAL" DO IDE DO ARDUINO (CONFLITO)                                                                 

int ROW = 0; //  VARIÁVEL QUE SE REFERE AS LINHAS DO EXCEL
int LABEL = 1;

void setup() {
  Serial.begin(9600);                                                    //  INICIALIZAÇÃO DA COMUNICAÇÃO SERIAL
  Serial.println("CLEARDATA");                                 //  RESET DA COMUNICAÇÃO SERIAL
  Serial.println("LABEL,Time,TEMP1,TEMP2,TEMPMEDIA");                       //  NOMEIA AS COLUNAS
   
  }
}

void loop() {
 
  valor1 = analogRead(sensor1);                                      //  LEITURA DO PINO A5
  valor2 = analogRead(sensor2);                                      //  LEITURA DO PINO A4
  temp1 = valor1 * 0.00488;                                            //  5 VOLTS / 1023 = 0.00488
  temp2 = valor2 * 0.00488;                                            //
  temp1 = temp1 * 100;                                                   //  CONVERTER milivolts PARA CELCIUS
  temp2 = temp2 * 100;                                                   //
  tempmedia = (temp1+temp2)/2;                                     //  TEMPERATURA MÉDIA
 
  
  Serial.print("DATA,TIME,");                                         //  INICIA A "IMPRESSÃO" DOS DADOS, SEMPRE INICIANDO COM O "TIME"
  Serial.print(temp1);                                                     
  Serial.print(",");                                                  
  Serial.print(temp2);                                                   
  Serial.print(",");                                                     
  Serial.println(tempmedia);                                             
 
  ROW++;                                                                      //  INCREMENTA A LINHA DO EXCEL
  if (ROW > 500)                                                            //  LAÇO PARA LIMITAR A QUANTIDADE DE DADOS ENVIADOS, SERVE PARA LIMITAR O GRÁFICO
  {                                                                       
    ROW=0;                                                                    //  RESET DA LINHA
    Serial.println("ROW,SET,2");                                      //  ALIMENTAÇÃO DAS LINHAS COM OS DADOS, INICIANDO DA LINHA 2
  }                                                                       
  
  delay(5000);                                                                  //  ESPERA CINCO SEGUNDOS PARA NOVA LEITURA
}
