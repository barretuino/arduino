#include "etherShield.h"
#include <EEPROM.h>

// Based on Nuelecronics sample code
// Modified by JP Civade on 2009/07/01
// Needs an ATMega368 beacuse of ram
//
uint8_t mymac[6];   // mac adress
uint8_t myip[4];    // ip addr
                    // Base URL automatically made with ip addr.
uint16_t mywwwport; // listen port for tcp/www (max range 1-254)
int EESIZE=1024;    // 512 for ATMEGA168, 1024 for ATMEGA368

// Relay status. Start Off.
byte on_off1;
byte on_off2;

// Serial input
byte inByte = 0;         // incoming serial byte

#define BUFFER_SIZE 750
static uint8_t buf[BUFFER_SIZE+1];

char tmpbuf[30];        // temporary buffer

#define STR_BUFFER_SIZE 22
static char strbuf[STR_BUFFER_SIZE+1];

EtherShield es=EtherShield();

// prepare the webpage by writing the data to the tcp send buffer
uint16_t print_webpage(uint8_t *buf, byte on_off1, byte on_off2);
int8_t analyse_cmd(char *str);

// 2 relays connected to output
#define SW1  4
#define SW2  3

char *base_url(){
  if (mywwwport !=80)
    sprintf (tmpbuf,"http://%d.%d.%d.%d:%d/",myip[0],myip[1],myip[2],myip[3],mywwwport);
  else
    sprintf (tmpbuf,"http://%d.%d.%d.%d/",myip[0],myip[1],myip[2],myip[3]);
  return tmpbuf;
  }


// Display Setup Menu
void setup_menu() {
  Serial.println("Arduino Relay Setup Menu :");
  Serial.println("--------------------------");
  Serial.println("1: Clear E2PROM (first use)");
  Serial.println("2: Display current Settings");
  Serial.println("3: Modify Mac Addr");
  Serial.println("4: Modify IP Addr");
  Serial.println("5: Modify Port Number");
  Serial.println("6: Store new settings to E2PROM");
  Serial.println("7: Exit Setup");
  Serial.println("> ?");
  }

// Read eprom settings
void setup_read_settings() {
  byte value  ;
  
  myip[0] = EEPROM.read(0);
  myip[1] = EEPROM.read(1);
  myip[2] = EEPROM.read(2);
  myip[3] = EEPROM.read(3);
  mymac[0] = EEPROM.read(4);
  mymac[1] = EEPROM.read(5);
  mymac[2] = EEPROM.read(6);
  mymac[3] = EEPROM.read(7);
  mymac[4] = EEPROM.read(8);
  mymac[5] = EEPROM.read(9);
  mywwwport = EEPROM.read(10);
  }
  
// read a char from serial
void setup_read_command() {
  while (Serial.available() == 0) {
    delay(500);
    }
    // get incoming byte:
    inByte = Serial.read();
  }

// Display Current Settings from ram
void setup_display_settings() {
  Serial.println ("Current Settings :");
  Serial.print ("IP addr and port : ");
  Serial.print (myip[0], DEC);
  Serial.print (".");
  Serial.print (myip[1], DEC);
  Serial.print (".");
  Serial.print (myip[2], DEC);
  Serial.print (".");
  Serial.print (myip[3], DEC);
  Serial.print (":");
  Serial.println (mywwwport, DEC);
  Serial.print ("Mac addr : ");
  Serial.print (mymac[0], HEX);
  Serial.print (":");
  Serial.print (mymac[1], HEX);
  Serial.print (":");
  Serial.print (mymac[2], HEX);
  Serial.print (":");
  Serial.print (mymac[3], HEX);
  Serial.print (":");
  Serial.print (mymac[4], HEX);
  Serial.print (":");
  Serial.println (mymac[5], HEX);
  Serial.println(""); 
  }

// Chamge Mac adress
void setup_set_macaddr() {
  byte byte1, byte2, byte3, byte4, byte5, byte6; // An MAC address if 6 unsigned bytes.
  int index=0; // index for storing string
  
  // Output prompt
  Serial.println ("Please enter MAC address (decimal only), finishing by ! (ie: 128:233:127:33:11:9!) :");
  Serial.print ("MAC? : ");
  
  // Read Input from tty
  inByte = 255;
  while (inByte) { // while not '!' ...
    if (Serial.available() > 0) {
      // get incoming byte:
      inByte = Serial.read();
      if (inByte=='!')
        inByte=0;
      tmpbuf[index]=inByte;
      index+=1;
      }
    }
  Serial.println (tmpbuf);
    
  // Scan Input fields
  sscanf(tmpbuf,"%d:%d:%d:%d:%d:%d",&byte1,&byte2,&byte3,&byte4,&byte5,&byte6);
  
  // Verify values
  if ( (byte1>255) || (byte2>255) || (byte3>255) || (byte4>255) || (byte5>255) || (byte6>255) )
    Serial.println ("Invalid Entry. Please retry");
  else {
    mymac[0] = byte1;
    mymac[1] = byte2;
    mymac[2] = byte3;
    mymac[3] = byte4;
    mymac[4] = byte5;
    mymac[5] = byte6;
    Serial.println ("MAC Address set.");
    setup_display_settings();
    }  
  }

// Change Ip adress  
void setup_set_ipaddr() {
  byte byte1, byte2, byte3, byte4; // An ethernet address if 4 unsigned bytes.
  int index=0; // index for storing string
  
  // Output prompt
  Serial.println ("Please enter IP address, finishing by ! (ie: 192.168.1.1!) :");
  Serial.print ("IP? : ");
  
  // Read Input from tty
  inByte = 255;
  while (inByte) { // while note enter...
    if (Serial.available() > 0) {
      // get incoming byte:
      inByte = Serial.read();
      if (inByte=='!')
        inByte=0;
      tmpbuf[index]=inByte;
      index+=1;
      }
    }
  Serial.println (tmpbuf);
    
  // Scan Input fields
  sscanf(tmpbuf,"%d.%d.%d.%d",&byte1,&byte2,&byte3,&byte4);
  
  // Verify values
  if ( (byte1>255) || (byte2>255) || (byte3>255) || (byte4>255) )
    Serial.println ("Invalid Entry. Please retry");
  else {
    myip[0] = byte1;
    myip[1] = byte2;
    myip[2] = byte3;
    myip[3] = byte4;
    Serial.println ("IP Address set.");
    setup_display_settings();
    }
}

// Change port  
void setup_set_port() {
  byte byte1; // port number (1->255).
  int index=0; // index for storing string
  
  // Output prompt
  Serial.println ("Please enter port Nomber, finishing by ! (ie: 80!) :");
  Serial.print ("Port? : ");
  
  // Read Input from tty
  inByte = 255;
  while (inByte) { // while note enter...
    if (Serial.available() > 0) {
      // get incoming byte:
      inByte = Serial.read();
      if (inByte=='!')
        inByte=0;
      tmpbuf[index]=inByte;
      index+=1;
      }
    }
  Serial.println (tmpbuf);
    
  // Scan Input fields
  sscanf(tmpbuf,"%d",&byte1);
  
  // Verify values
  if (byte1>255) 
    Serial.println ("Invalid Entry. Please retry");
  else {
    mywwwport = byte1;
    Serial.println ("Port number set.");
    setup_display_settings();
    }
}

//Store settings into e2prom
void setup_store_settings() {

  EEPROM.write(0,myip[0]);
  EEPROM.write(1,myip[1]);
  EEPROM.write(2,myip[2]);
  EEPROM.write(3,myip[3]);
  EEPROM.write(4,mymac[0]);
  EEPROM.write(5,mymac[1]);
  EEPROM.write(6,mymac[2]);
  EEPROM.write(7,mymac[3]);
  EEPROM.write(8,mymac[4]);
  EEPROM.write(9,mymac[5]);
  EEPROM.write(10,mywwwport);  
  Serial.println("--> Settings stored to E2Prom.");
  }
  
// Init eprom
void setup_init_eeprom() {
  int i;
  // write a 0 to all EESIZE bytes of the EEPROM
  for (int i = 0; i < EESIZE; i++)
    EEPROM.write(i, 0);  
  Serial.println("--> E2Prom cleared.");
  // default MAC
  mymac[0] = 0x54;
  mymac[1] = 0x55;
  mymac[2] = 0x58;
  mymac[3] = 0x10;
  mymac[4] = 0x00;
  mymac[5] = 0x24; 
  //Default IP
  myip[0] = 192;
  myip[1] = 168;
  myip[2] = 20;
  myip[3] = 99;
  // Default port for tcp/www (max range 1-254)
  mywwwport =80; 
  Serial.println("--> Default settings loaded");
  setup_store_settings();
  }

  
void call_setup() {
  // read E2prom current settings in ram
  while (1==1) {
    setup_menu();
    setup_read_command(); // read a command into inByte
    switch (inByte) {
      case '1':
        setup_init_eeprom(); // erase e2prom
        break;
      case '2': // Display settings from RAM
        setup_display_settings();
        break;
      case '3': // Change MAC address
        setup_set_macaddr();
        break;
      case '4': // Change IP address
        setup_set_ipaddr();
        break;
      case '5': // Change Port Number
        setup_set_port();    
        break;
      case '6':
        setup_store_settings();
        break;
      case '7':
        goto EXITSETUP;
        break;
      }
    }
  EXITSETUP: 
     Serial.println("Reeinit while exiting setup.");
     setup();
  }

void setup(){
  /* Initialize Serial, only for debug */
  Serial.begin(115200);
  Serial.println("Hit 's' or 'S' to enter setup.");
  setup_read_settings(); // Get E2prom settings and store into ram
  on_off1=0;
  on_off2=0;
  
   /*initialize enc28j60*/
   es.ES_enc28j60Init(mymac);
   es.ES_enc28j60clkout(2); // change clkout from 6.25MHz to 12.5MHz
   delay(10);
        
	/* Magjack leds configuration, see enc28j60 datasheet, page 11 */
	// LEDA=greed LEDB=yellow
	//
	// 0x880 is PHLCON LEDB=on, LEDA=on
	// enc28j60PhyWrite(PHLCON,0b0000 1000 1000 00 00);
	es.ES_enc28j60PhyWrite(PHLCON,0x880);
	delay(250);
	//
	// 0x990 is PHLCON LEDB=off, LEDA=off
	// enc28j60PhyWrite(PHLCON,0b0000 1001 1001 00 00);
	es.ES_enc28j60PhyWrite(PHLCON,0x990);
	delay(250);
	//
	// 0x880 is PHLCON LEDB=on, LEDA=on
	// enc28j60PhyWrite(PHLCON,0b0000 1000 1000 00 00);
	es.ES_enc28j60PhyWrite(PHLCON,0x880);
	delay(250);
	//
	// 0x990 is PHLCON LEDB=off, LEDA=off
	// enc28j60PhyWrite(PHLCON,0b0000 1001 1001 00 00);
	es.ES_enc28j60PhyWrite(PHLCON,0x990);
	delay(250);
	//
  // 0x476 is PHLCON LEDA=links status, LEDB=receive/transmit
  // enc28j60PhyWrite(PHLCON,0b0000 0100 0111 01 10);
  es.ES_enc28j60PhyWrite(PHLCON,0x476);
  delay(100);
        
  //init the ethernet/ip layer:
  es.ES_init_ip_arp_udp_tcp(mymac,myip,mywwwport);
  
  // Init outputs
 	pinMode(SW1, OUTPUT); 
 	digitalWrite(SW1, LOW);  // switch off LED
 	pinMode(SW2, OUTPUT); 
 	digitalWrite(SW2, LOW);  // switch off LED
}

void loop(){
  uint16_t plen, dat_p;
  int8_t cmd;

  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    if ((inByte=='s')||(inByte=='S')) {
// Command mode : Setup
     Serial.println("Setup Called.");
     call_setup();   
    } //end serial=return
   } // serial not available
  
// Ethernet Mode
  plen = es.ES_enc28j60PacketReceive(BUFFER_SIZE, buf);

	/*plen will ne unequal to zero if there is a valid packet (without crc error) */
  if(plen!=0){
	           
    // arp is broadcast if unknown but a host may also verify the mac address by sending it to a unicast address.
    if(es.ES_eth_type_is_arp_and_my_ip(buf,plen)){
      es.ES_make_arp_answer_from_request(buf);
      return;
    }

    // check if ip packets are for us:
    if(es.ES_eth_type_is_ip_and_my_ip(buf,plen)==0){
      return;
    }
    
    if(buf[IP_PROTO_P]==IP_PROTO_ICMP_V && buf[ICMP_TYPE_P]==ICMP_TYPE_ECHOREQUEST_V){
      es.ES_make_echo_reply_from_request(buf,plen);
      return;
    }
    
    // tcp port www start, compare only the lower byte
    if (buf[IP_PROTO_P]==IP_PROTO_TCP_V&&buf[TCP_DST_PORT_H_P]==0&&buf[TCP_DST_PORT_L_P]==mywwwport){
      if (buf[TCP_FLAGS_P] & TCP_FLAGS_SYN_V){
         es.ES_make_tcp_synack_from_syn(buf); // make_tcp_synack_from_syn does already send the syn,ack
         return;     
      }
      if (buf[TCP_FLAGS_P] & TCP_FLAGS_ACK_V){
        es.ES_init_len_info(buf); // init some data structures
        dat_p=es.ES_get_tcp_data_pointer();
        if (dat_p==0){ // we can possibly have no data, just ack:
          if (buf[TCP_FLAGS_P] & TCP_FLAGS_FIN_V){
            es.ES_make_tcp_ack_from_any(buf);
          }
          return;
        }
        if (strncmp("GET ",(char *)&(buf[dat_p]),4)!=0){
            // head, post and other methods for possible status codes see:
            // http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
            plen=es.ES_fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>200 OK</h1>"));
            goto SENDTCP;
        }
        // If "get /" without parameters 
 	if (strncmp("/ ",(char *)&(buf[dat_p+4]),2)==0){
            plen=print_webpage(buf, on_off1, on_off2);
            goto SENDTCP;
         }
        cmd=analyse_cmd((char *)&(buf[dat_p+5]));
        
        // Process commands
        switch (cmd) {
        case 2:
                on_off1=1;
        	digitalWrite(SW1, HIGH);  // switch on LED1
                break;
        case 3:
                on_off1=0;
        	digitalWrite(SW1, LOW);  // switch off LED1
                break;
        case 4:
                on_off2=1;
        	digitalWrite(SW2, HIGH);  // switch on LED2
                break;
        case 5:
                on_off2=0;
        	digitalWrite(SW2, LOW);  // switch off LED2
                break;
            }
        plen=print_webpage(buf, on_off1, on_off2);
        	
SENDTCP:  es.ES_make_tcp_ack_from_any(buf); // send ack for http get
           es.ES_make_tcp_ack_with_data(buf,plen); // send data       
      }
    }
  }
        
}
// The returned value is stored in the global var strbuf
uint8_t find_key_val(char *str,char *key)
{
        uint8_t found=0;
        uint8_t i=0;
        char *kp;
        kp=key;
        while(*str &&  *str!=' ' && found==0){
                if (*str == *kp){
                        kp++;
                        if (*kp == '\0'){
                                str++;
                                kp=key;
                                if (*str == '='){
                                        found=1;
                                }
                        }
                }else{
                        kp=key;
                }
                str++;
        }
        if (found==1){
                // copy the value to a buffer and terminate it with '\0'
                while(*str &&  *str!=' ' && *str!='&' && i<STR_BUFFER_SIZE){
                        strbuf[i]=*str;
                        i++;
                        str++;
                }
                strbuf[i]='\0';
        }
        return(found);
}

int8_t analyse_cmd(char *str)
{
        int8_t r=-1;
     
        if (find_key_val(str,"cmd")){
                if (*strbuf < 0x3a && *strbuf > 0x2f){
                        // is a ASCII number, return it
                        r=(*strbuf-0x30);
                }
        }
        return r;
}

uint16_t print_webpage(uint8_t *buf, byte on_off1, byte on_off2)
{
        int i=0;
        uint16_t plen;
        plen=es.ES_fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n"));
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<FONT FACE=\"arial\"><center><p><h1><A HREF=\"/\">Arduino Power Switch</A></h1></p>"));
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<br><table border=0 bgcolor=\"#f7f7f7\" width=\"300\"><tr><td width=50% align=center>"));
         
        switch (on_off1) {
          case 1:
 	        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<h2>Out 1: <font color=\"#00FF00\">On</font></h2><br>"));
                plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<form METHOD=get action=\""));
                plen=es.ES_fill_tcp_data(buf,plen,base_url());
                plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("\">"));
        	plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<input type=hidden name=cmd value=3>"));
        	plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<input type=submit value=\"Switch off\"></form>"));
                break;
          case 0:
       	        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<h2>Out 1: <font color=\"#CCCCCC\">Off</font></h2><br>"));
                plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<form METHOD=get action=\""));
                plen=es.ES_fill_tcp_data(buf,plen,base_url());
                plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("\">"));
        	plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<input type=hidden name=cmd value=2>"));
        	plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<input type=submit value=\"Switch on\"></form>"));
                break;
          }
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("</td><td width=50% align=center>"));
        switch (on_off2) {
          case 1:
 	        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<h2>Out 2: <font color=\"#00FF00\">On</font></h2><br>"));
                plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<form METHOD=get action=\""));
                plen=es.ES_fill_tcp_data(buf,plen,base_url());
                plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("\">"));
        	plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<input type=hidden name=cmd value=5>"));
        	plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<input type=submit value=\"Switch off\"></form>"));
                break;
          case 0:
       	        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<h2>Out 2: <font color=\"#CCCCCC\">Off</font></h2><br>"));
                plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<form METHOD=get action=\""));
                plen=es.ES_fill_tcp_data(buf,plen,base_url());
                plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("\">"));
        	plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<input type=hidden name=cmd value=4>"));
        	plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<input type=submit value=\"Switch on\"></form>"));
                break;
          }        
             
        plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("</td></tr></table></center><hr>Connect to serial, 115200,n,8,1 to setup."));
// For debugging purpose, show buffer...size.
//        Serial.print ("Buffer size :");
//        Serial.println (plen,DEC);  
        return(plen);
}

