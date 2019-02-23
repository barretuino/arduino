#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x9B, 0x36 }; //physical mac address
byte ip[] = { 192, 168, 0, 105 }; // ip in lan
byte gateway[] = { 192, 168, 0, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port

int sensor = 1;      //Pino analógico em que o sensor está conectado.
int valorSensor = 0; //variável usada para ler o valor do sensor em tempo real.

void setup(){
  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  //the pin for the servo co
  //enable serial data print
  Serial.begin(9600);
  Serial.println("Exemplo de Comunicacão via Ethernet Shield"); // so I can keep track of what is loaded
}

void loop(){
  //Lendo o valor do sensor.
  int valorSensor = analogRead(sensor);
  //Exibindo o valor do sensor no serial monitor.
  //Serial.println(valorSensor); 
  EthernetClient client = server.available();
  if (client) {
    client.println("HTTP/1.1 200 OK"); //send new page
    client.println("Content-Type: text/html");
    client.println();
    client.println("<html>");
    client.println("<head>"); 
    client.println("<meta http-equiv='Content-Type' content='text/html; charset=utf-8'>");
        client.println("<link href='http://192.168.0.101:8080/Demos/styles.css' rel='stylesheet' />");
        client.println("<script src='http://192.168.0.101:8080/Demos/js/jquery-1.9.1.min.js'></script>");
        client.println("<script src='http://192.168.0.101:8080/Demos/js/knockout-2.2.1.js'></script>");
        client.println("<script src='http://192.168.0.101:8080/Demos/js/globalize.min.js'></script>");
        client.println("<script src='http://192.168.0.101:8080/Demos/js/dx.chartjs.js'></script>");
        client.println("</head><body><script type='text/javascript'>");
        client.println("function grafico(valor)");
        client.println("{");
        client.println("var d=document.formBotoes; //Vai pegar o formulario e adicionar em uma variavél");
        client.println("var valor = valor");
        //client.println("var menor = d.menor.value;");
        client.println("var maior = d.maior.value;");
        client.println("$('#chartContainer').dxCircularGauge({");
        client.println("scale: {");
        client.println("startValue: 0,");
        client.println("endValue: 100,");
        client.println("majorTick: {");
        client.println("tickInterval: 10");
        client.println("}},");
        client.println("rangeContainer: {");
        client.println("backgroundColor: 'none',");
        client.println("ranges: [");
        client.println("{");
        client.println("startValue: 0,");
        client.println("endValue: 30,");
        client.println("color: '#E19094'");
        client.println("},{");
        client.println("startValue: 30,");
        client.println("endValue: 70,");
        client.println("color: '#A6C567'");
        client.println("},{");
        client.println("startValue: 70,");
        client.println("endValue: 100,");
        client.println("color: '#FCBB69'");
        client.println("}]},");
        client.println("needles: [{value: valor}],");
        client.println("markers: [{value: valor}, { value: maior}]");
        client.println("});");
        client.println("}");
        client.println("</script>");
        client.println("<div class='title'>");	
        client.println("<center><h1>Projeto Arduino</h1>&nbsp;&nbsp;&nbsp;<h2>Medidas de Luminosidade</h2></center>");
        client.println("</div>");
        client.println("<form name='formBotoes'>");
        client.println("<center>");
        //client.println("<input type='text' name='menor' size='4'>");
        client.println("Considerada Adequada: <input type='text' name='maior' size='4'>");
        client.print("<input type='button' value='Atualizar' onClick='grafico(");
        client.print(map(valorSensor, 504, 950, 0, 100));
        client.println (")'>");
        client.println("</center>");
        client.println("</form>");         
        client.println("<div id='chartContainer' style='width: 100%; height: 440px;'></div>");
        client.println("</div>");        
      while (client.connected()) {
      if (client.available()) {
          valorSensor = analogRead(sensor);
          client.println("<br>Luminosidade ");
          client.println(map(valorSensor, 504, 950, 0, 100)); 
          client.print("<input type='button' value='Atualizar' onClick='grafico(");
          client.print(map(valorSensor, 504, 950, 0, 100));
          client.println (")'>");
        
          delay(5000);
      }
    }
    client.println("</body>");
    client.println("</head>");
  }
}
