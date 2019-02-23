#include "TinyGPS.h" //Faz a importação da biblioteca Tiny
#include <SoftwareSerial.h> //Faz a importação da biblioteca SoftwareSerial

SoftwareSerial Serial1(3, 4); // RX, TX

TinyGPS gps; //Inicia o objeto
int ano; // variavel que recebera o ano
byte mes, dia, hora, minuto, segundo, centesimos; //Dados que serão recebidos
unsigned long chars;
unsigned short sentences, failed_checksum;
static void print_date(TinyGPS &gps);

void setup()
{
 //Inicia as seriais
  Serial.begin(9600); 
  Serial1.begin(9600);
}

void loop()
{

  while(Serial1 .available()) //Enquanto a serial estiver disponível
  {
    int c = Serial1 .read(); //Le os dados da Serial1
    if(gps.encode(c)) //Faz a tradução dos valores lidos
    {
      float latitude, longitude;
      gps.f_get_position(&latitude, &longitude); //Obtem a latitude e longitude
      Serial.print("Lat/Long: "); //Imprime
      Serial.print(latitude,5); 
      Serial.print(", "); 
      Serial.println(longitude,5);
      //Obtem o ano, mes, dia e hora. Em seguida faz a exibição
      gps.crack_datetime(&ano,&mes,&dia,&hora,&minuto,&segundo,&centesimos);
      Serial.print("Data: "); 
      Serial.print(mes, DEC); 
      Serial.print("/"); 
      Serial.print(dia, DEC); 
      Serial.print("/"); 
      Serial.print(ano);
      Serial.print(" Hora: "); 
      Serial.print(hora-3, DEC); //Transformar para o horário Brasileiro
      Serial.print(":"); 
      Serial.print(minuto, DEC); 
      Serial.print(":"); 
      Serial.print(segundo, DEC); 
      Serial.print("."); 
      Serial.println(centesimos, DEC);
      Serial.print("Altitude (metros): "); 
      Serial.println(gps.f_altitude()); 
      Serial.print("Course (Graus): "); 
      Serial.println(gps.f_course()); 
      Serial.print("Velocidade(kmph): "); 
      Serial.println(gps.f_speed_kmph());
      Serial.print("Satellites: "); 
      Serial.println(gps.satellites());
      Serial.println();
      gps.stats(&chars, &sentences, &failed_checksum);
    }
  }
}
