/*********************************
Autor: Prof. Paulo Barreto
Data: 08/05/2015
Exemplo de utilização do Sensor Óptico Reflexivo TCRT5000
********************************/
 
int ledPin = 13;
int inPin = 10;
int valor = 0;
 
void setup()
{
   Serial.begin(9600);
   pinMode(ledPin, OUTPUT);
   pinMode(inPin, INPUT);
}
 
void loop()
{
    valor = digitalRead(inPin);
 
    if (valor == HIGH)
    {
           digitalWrite(ledPin, HIGH);
       Serial.write("Preto");
    } else
         {
               digitalWrite(ledPin, LOW);
           Serial.write("Branco");
        }
}
