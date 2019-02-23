#include <SoftwareSerial.h>
#include <TinyGPS.h>
TinyGPS gps;
SoftwareSerial serialgps(2,3);
int year;
byte month, day, hour, minute, second, hundredths;
unsigned long chars;
unsigned short sentences, failed_checksum;
void setup()
{

Serial.begin(115200);
serialgps.begin(4800);
Serial.println("");
Serial.println("GPS Shield QuickStart Example Sketch v12");
Serial.println(" ...waiting for lock... ");
Serial.println("");
}
void loop()
{
while(serialgps.available())
{
int c = serialgps.read();
if(gps.encode(c))
{
float latitude, longitude;
gps.f_get_position(&latitude, &longitude);
Serial.print("Lat/Long: ");
Serial.print(latitude,5);
Serial.print(", ");
Serial.println(longitude,5);
gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
Serial.print("Date: "); Serial.print(month, DEC); Serial.print("/");
Serial.print(day, DEC); Serial.print("/"); Serial.print(year);
Serial.print(" Time: "); Serial.print(hour, DEC); Serial.print(":");
Serial.print(minute, DEC); Serial.print(":"); Serial.print(second, DEC);
Serial.print("."); Serial.println(hundredths, DEC);
Serial.print("Altitude (meters): "); Serial.println(gps.f_altitude());
Serial.print("Course (degrees): "); Serial.println(gps.f_course());
Serial.print("Speed(kmph): "); Serial.println(gps.f_speed_kmph());
Serial.print("Satellites: "); Serial.println(gps.satellites());
Serial.println();
gps.stats(&chars, &sentences, &failed_checksum);
}
}
}
