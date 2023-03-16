#include <WiFi.h>
#include <ESPAsyncWebSrv.h>

const char* ssid="OPPO A54";
const char* password="ranita321";

AsyncWebServer server(80);

void conectarse(){
    Serial.print("conectando ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }
    Serial.print(WiFi.localIP());    
}

void ledLoop(){
    digitalWrite(2, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
    digitalWrite(2, LOW);   // turn the LED off by making the voltage LOW
    delay(1000); 
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  conectarse();
  pinMode(2, OUTPUT);
  server.on("/", HTTP_GET,[](AsyncWebServerRequest * request){
    int numParametros = request->params();
    Serial.print(numParametros);
    if(numParametros == 0){
      request->send(200,"text/html","<h1>hola mundo</h1>");
    }else{
      AsyncWebParameter * p = request->getParam(0);
      String html="<h1> hola" + p->value() + " desde ESP32</h1>";
      request->send(200,"text/html",html);
    }
  });

  server.on("/adios",HTTP_GET,[](AsyncWebServerRequest * r){
    r->send(200,"text/html","<h1>adios</h1>");
  });

  server.on("/on",HTTP_GET,[](AsyncWebServerRequest * r){
    digitalWrite(2, HIGH);
    r->send(200,"text/html","<h1>Led Encendido</h1>");
  });
  server.on("/off",HTTP_GET,[](AsyncWebServerRequest * r){
    digitalWrite(2, LOW);
    r->send(200,"text/html","<h1>Led Apagado</h1>");
  });
  server.on("/loop",HTTP_GET,[](AsyncWebServerRequest * r){
    while(true){
      ledLoop();      
    }
    r->send(200,"text/html","<h1>Led Loop</h1>");
  });
  server.begin();

}
   
void loop() {
  // put your main code here, to run repeatedly:
}