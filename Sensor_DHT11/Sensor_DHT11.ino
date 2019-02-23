#include <dht11.h>

dht11 DHT11;

void setup()
{
  DHT11.attach(9);
  Serial.begin(9600);
  Serial.println("DHT11 PROGRAMA DE TESTE");
  Serial.print("BIBLIOTECA VERSAO: ");
  Serial.println(DHT11LIB_VERSION);
}

void loop()
{
  Serial.println("\n");

  int chk = DHT11.read();

  Serial.print("Lendo sensor: ");
  switch (chk)
  {
    case 0: Serial.println("OK"); break;
    case -1: Serial.println("Checksum error"); break;
    case -2: Serial.println("Time out error"); break;
    default: Serial.println("Unknown error"); break;
  }

  Serial.print("Umidade (%): ");
  Serial.println((float)DHT11.humidity, DEC);

  Serial.print("Temperatura (°C): ");
  Serial.println((float)DHT11.temperature, DEC);

  Serial.print("Temperatura (°F): ");
  Serial.println(DHT11.fahrenheit(), DEC);

  Serial.print("Temperatura (°K): ");
  Serial.println(DHT11.kelvin(), DEC);

  Serial.print("Dew Point (°C): ");
  Serial.println(DHT11.dewPoint(), DEC);

  Serial.print("Dew PointFast (°C): ");
  Serial.println(DHT11.dewPointFast(), DEC);

  delay(2000);
}
