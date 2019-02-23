#include <SPI.h>
#include <Ethernet.h>

// the media access control (ethernet hardware) address for the shield:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  
//the IP address for the shield:
byte ip[] = { 198, 168, 2, 199 };    

void setup()
{
  Ethernet.begin(mac, ip);
}

void loop () {}
