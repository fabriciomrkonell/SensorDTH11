#include <SPI.h>
#include <Ethernet.h>
#include <dht.h>

#define dht_dpin A1

dht DHT;

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x9B, 0x36 }; //physical mac address
byte ip[] = { 192, 168, 0, 99 }; // ip in lan
byte gateway[] = { 192, 168, 0, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port

String readString;

void setup(){
  
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.begin(9600);
  
}

void loop(){    
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
          DHT.read11(dht_dpin);                     
          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();
          client.println("<!DOCTYPE html>");
          client.println("<html>");
          client.println("<head>");
          client.println("<meta charset='utf-8'>");
          client.println("<meta http-equiv='X-UA-Compatible' content='IE=edge,chrome=1'>");
          client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
          client.println("<title>Fabrício Ronchi - Arduino</title>");
          client.println("<link rel='shortcut icon' href='http://cdn.marketplaceimages.windowsphone.com/v8/images/b778c005-a0fa-47cb-8dae-7565df234a55?imageType=ws_icon_large'>");
          client.println("<link rel='stylesheet' href='http://netdna.bootstrapcdn.com/bootstrap/3.1.1/css/bootstrap.min.css'>");
          client.println("</head>");
          client.println("<body style='background-color: #f5f5f5'>");
          client.println("<div class='container'>");
          client.println("<div class='row'>");
          client.println("<div class='col-sm-12'>");
          client.println("<br />");
          client.println("<div class='panel panel-primary'>");
          client.println("<div class='panel-heading text-center'>");
          client.println("<h3 class='panel-title'>Temperatura</h3>");
          client.println("</div>");
          client.println("<div class='panel-body text-center'>");
          client.println("<h1>");
          client.print(DHT.temperature);
          client.println("</h1>");
          client.println("<h3>Temperatura</h3>");	
          client.println("<hr />");	
          client.println("<h1>");
          client.print(DHT.humidity);
          client.println("</h1>");
          client.println("<h3>Humidade</h3>");	
          client.println("</div>");
          client.println("</div>");	    				
          client.println("<div class='text-center'>");
          client.println("<h5>Fabrício Ronchi - Arduino</<h5>");				
          client.println("<h5>www.fabricioronchi.com</<h5>");
          client.println("</div>");    				
          client.println("</div>");				
          client.println("</div>");			
          client.println("</div>");		
          client.println("</body>");
          client.println("</html>");         
          delay(1);
          client.stop();             
      }
    }
  }
}


