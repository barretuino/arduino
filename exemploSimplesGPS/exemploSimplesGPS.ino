#include <SoftwareSerial.h>
SoftwareSerial gps(2,3); 
void setup() {
Serial.begin(9600);
gps.begin(4800);
delay(100);
}
void loop() {
char entrada = 0;
String resposta = "";
while((entrada = gps.read()) != 10) {
if(entrada > 0) 
resposta += entrada;
}
if(!resposta.equals("")) Serial.println(resposta);
}

