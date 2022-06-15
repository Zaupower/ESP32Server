#include <WiFi.h>

#define SSID "PFMQ052"
#define PASSWD "00000000"

unsigned long int last_time = millis();

const uint16_t port = 1234;
const uint16_t portReceive = 5555;
const char * host = "172.21.28.77";
WiFiServer server(portReceive);

void txLEDS(void *pvParameters){

  WiFiClient client2;

  while(1){

    if (!client2.connect(host, portReceive)){
        Serial.println("Falha de conexao socket");
        delay(1000);
    }else{
      Serial.println("Conectado!");
      client2.print("A3");
      delay(3000);
    }

  }
}

void rxPins(void * parameter){

    delay(500);

    WiFiClient client = server.available();

    while(1){

      Serial.println("Runing income");
      if (client) {
         while (client.connected()) {

          while (client.available()>0) {

            char c = client.read();
            Serial.write(c);

           }

          delay(10);

          }
    }
    delay(3000);
  }
  /*

  WiFiClient clientRx = server.available();

  if (clientRx) {

    while (clientRx.connected()) {

      while (clientRx.available()>0) {
        char c = clientRx.read();
        Serial.println(c);
      }

      delay(10);
    }

    //client.stop();
    Serial.println("Client disconnected");

  }*/
}


void setup(){
    Serial.begin(115200);

    WiFi.begin(SSID,PASSWD);
    while (WiFi.status() != WL_CONNECTED){delay(100);}

    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    delay(500);

    server.begin();

    delay(500);
    xTaskCreatePinnedToCore(txLEDS,"txLEDS",10000,NULL,2,NULL,1);
    delay(500);
    xTaskCreatePinnedToCore(rxPins,"rxPins",10000,NULL,2,NULL,1);

}

void loop(){
  while(1){}
}