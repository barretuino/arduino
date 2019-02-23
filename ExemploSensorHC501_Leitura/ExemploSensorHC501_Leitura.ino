/*----------------------------------------------------
Exemplo de utilização Sensor HC-SR501 
PASSIVE INFRARED SENSOR WITH ARDUINO
@autor: Prof. Paulo Barreto
@date: 15/05/2015
----------------------------------------------------*/

#define pir A0
#define led 11

void setup() {
  pinMode(pir, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  int i = analogRead(pir);
  int l = map(i,0,1023,0,255);

  Serial.print(i);
  Serial.print(" / ");
  Serial.println(l);
  analogWrite(led, l);

  delay(100);
}
