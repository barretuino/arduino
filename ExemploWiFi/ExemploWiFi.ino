//Programa : Wifi Shield CC3000 Sparkfun
//Biblioteca : Sparkfun SFE_CC3000
//Alteracoes e adaptacoes : FILIPEFLOP
  
#include <SPI.h>
#include <SFE_CC3000.h>
 
// Pinos
#define CC3000_INT      2   //Pino de interrupcao (D2 ou D3)
#define CC3000_EN       7   //Pode ser qualquer pino digital
#define CC3000_CS       10  //Preferencialmente pino 10 do Arduino Uno
 
#define FW_VER_LEN      2   //Armazena o valor do firmware
#define MAC_ADDR_LEN    6   //Armazena o endereço MAC
#define IP_ADDR_LEN     4   //Tamanho do endereco IP, em bytes
 
char ap_ssid[] = "NETWORK FAMILIA BARRETO";            //Nome da rede Wireless
char ap_password[] = "";          //Senha da rede Wireless
unsigned int ap_security = WLAN_SEC_WPA2; //Tipo de seguranca da rede
unsigned int timeout = 30000;             //Milisegundos
char remote_host[] = "www.filipeflop.com";  //Site para teste
unsigned int num_pings = 3;    // Numero de pings
 
SFE_CC3000 wifi = SFE_CC3000(CC3000_INT, CC3000_EN, CC3000_CS);
 
void setup() 
{
  Serial.begin(115200);
}
 
void loop()
{
  Serial.println("--------------------------------");
  Serial.println("-        SparkFun CC3000       -");
  Serial.println("--------------------------------");
  Teste_Placa();  
  Serial.println("--------------------------------");
  Serial.println("      Procurando redes wifi     ");
  Serial.println("--------------------------------");
  Procura_redes();
  Serial.println("--------------------------------");
  Serial.println("     Conexao e teste de ping    ");
  Serial.println("--------------------------------");
  ping_site();
  Serial.println("--------------------------------");
  while(1)
  {}
}
 
void Teste_Placa()
{
  int i;
  unsigned char fw_ver[FW_VER_LEN];
  unsigned char mac_addr[MAC_ADDR_LEN];
   
  // Inicializa o shield CC3000 
  if ( wifi.init() ) 
  {
    Serial.println("Inicializacao completa - CC3000 ");
  } else {
    Serial.println("Erro durante a inicializacao da CC3000 !");
  }
   
  //Le e mostra a versao de firmware
  if ( wifi.getFirmwareVersion(fw_ver) ) 
  {
    Serial.print("Versao de firmware : ");
    Serial.print(fw_ver[0], DEC);
    Serial.print(".");
    Serial.print(fw_ver[1], DEC);
    Serial.println();
  } 
  else
  {
    Serial.println("Nao foi possivel ler a versao de firmware.");
  }
   
  //Le e mostra o endereco MAC
  if ( wifi.getMacAddress(mac_addr) ) 
  {
    Serial.print("Endereco MAC : ");
    for ( i = 0; i < MAC_ADDR_LEN; i++ ) 
    {
      if ( mac_addr[i] < 0x10 ) 
      {
        Serial.print("0");
      }
      Serial.print(mac_addr[i], HEX);
      if ( i < MAC_ADDR_LEN - 1 ) 
      {
        Serial.print(":");
      }
    }
    Serial.println();
  } 
  else
  {
    Serial.println("Nao foi possivel ler o endereco MAC");
  } 
} 
 
void Procura_redes()
{
  int i;
  AccessPointInfo ap_info;
 
  unsigned char fw_ver[FW_VER_LEN];
  unsigned char mac_addr[MAC_ADDR_LEN];
 
  if ( wifi.scanAccessPoints(4000) != true ) {
    Serial.println("Erro ao procurar redes wifi");
  }
   
  //Procura por redes wifi e exibe o nome
  Serial.println("Redes Wifi encontradas:");
  Serial.println();
  while ( wifi.getNextAccessPoint(ap_info) ) {
    Serial.print("SSID: ");
    Serial.println(ap_info.ssid);
    Serial.print("Seguranca : ");
    switch(ap_info.security_mode) {
      case WLAN_SEC_UNSEC:
        Serial.println("Sem seguranca");
        break;
      case WLAN_SEC_WEP:
        Serial.println("WEP");
        break;
      case WLAN_SEC_WPA:
        Serial.println("WPA");
        break;
      case WLAN_SEC_WPA2:
        Serial.println("WPA2");
        break;
      default:
        break;
    }
    Serial.println();
  }
}
 
void ping_site()
{
  ConnectionInfo connection_info;
  IPAddress ip_addr;
  IPAddress remote_ip;
  PingReport ping_report = {0};
  int i;
 
  //Conecta e aguarda endereco via DHCP
  Serial.print("Conectando a rede : ");
  Serial.print(ap_ssid);
  if(!wifi.connect(ap_ssid, ap_security, ap_password, timeout)) {
    Serial.println("Erro: Nao foi possivel conectar !");
  }
   
  //Le os dados de conexao
  if ( !wifi.getConnectionInfo(connection_info) ) 
  {
    Serial.println("Erro: Nao foi possivel obter dados de conexao");
  } 
  else
  {
    Serial.println(" - Conectado !");
    Serial.print("Endereco IP recebido : ");
    for (i = 0; i < IP_ADDR_LEN; i++) 
    {
      Serial.print(connection_info.ip_address[i]);
      if ( i < IP_ADDR_LEN - 1 ) 
      {
        Serial.print(".");
      }
    }
    Serial.println();
  }
   
  //Usa DNSLookup para encontrar o endereco do site
  Serial.print("Aguardando endereco IP de : ");
  Serial.println(remote_host);
  if ( !wifi.dnsLookup(remote_host, &remote_ip) ) 
  {
    Serial.println("Error: Could not lookup host by name");
  } 
  else
  {
    Serial.print("Endereco IP encontrado: ");
    for (i = 0; i < IP_ADDR_LEN; i++) 
    {
      Serial.print(remote_ip[i], DEC);
      if ( i < IP_ADDR_LEN - 1 ) 
      {
        Serial.print(".");
      }
    }
    Serial.println();
  }
   
  //Realiza o teste de ping
  Serial.print("Teste de Ping IP ");
  for (i = 0; i < IP_ADDR_LEN; i++) 
  {
    Serial.print(remote_ip[i], DEC);
    if ( i < IP_ADDR_LEN - 1 ) 
    {
      Serial.print(".");
    }
  }
  Serial.print(" ");
  Serial.print(num_pings, DEC);
  Serial.println(" vezes...");
  if ( !wifi.ping(remote_ip, ping_report, 3, 56, 1000) ) {
    Serial.println("Error: no ping response");
  } else {
    Serial.print("Pacotes enviados : ");
    Serial.println(ping_report.packets_sent);
    Serial.print("Pacotes recebidos: ");
    Serial.println(ping_report.packets_received);
  }
   
  //Desconecta da rede
  if ( wifi.disconnect() ) {
    Serial.println("Desconectando da rede wifi");
  } else {
    Serial.println("Erro: Nao foi possivel desconectar !");
  }
}
