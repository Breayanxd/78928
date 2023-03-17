#include "DHTesp.h"
#define DHTpin 15
#include <WiFi.h>
#include <ESPAsyncWebSrv.h>

DHTesp dht;
const char* ssid="Redmi";
const char* password="12345678";
String estado = "";
float humedad = 0.0;
float temperatura = 0.0;

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

void webServer(){
  conectarse();
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

  server.on("/estado",HTTP_GET,[](AsyncWebServerRequest * r){
    r->send(200,"text/html","<h1>Estado:" + estado + "</h1>");
  });
  server.on("/temperatura",HTTP_GET,[](AsyncWebServerRequest * r){
    temperatura = dht.getTemperature();
    r->send(200,"text/html","<h1>Temperatura: "+ String(temperatura) + "</h1>");
  });
  server.on("/humedad",HTTP_GET,[](AsyncWebServerRequest * r){
    humedad =  dht.getHumidity();
    r->send(200,"text/html","<h1>humedad: "+ String(humedad) + "</h1>");
  });
  server.on("/indiceCalor",HTTP_GET,[](AsyncWebServerRequest * r){
    r->send(200,"text/html","<h1>adios</h1>");
  });
  server.begin();
}

void setup(){
  Serial.begin(115200);
  Serial.println();
  webServer();
  //Serial.println("Estado\tHumedad (%)\tTemperatura (C)\t(F)\tIndiceCalor (C)\t(F)");
  dht.setup(DHTpin, DHTesp::DHT11);
}

void loop(){
  /*delay(dht.getMinimumSamplingPeriod());
  humedad =  dht.getHumidity();
  temperatura = dht.getTemperature();
  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("No se pudo leer sensor DHT!");
    return;
  }
  estado = dht.getStatusString();
  Serial.print( dht.getStatusString() );
  Serial.print("\t");
  Serial.print(humedad, 1);
  Serial.print("\t\t");
  Serial.print(temperatura, 1);
  Serial.print("\t\t");
  Serial.print( dht.toFahrenheit(temperatura), 1);
  Serial.print("\t\t");
  Serial.print( dht.computeHeatIndex(temperatura, humedad, false), 1);
  Serial.print("\t\t");
  Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperatura), humedad, true), 1);
  delay(2000);*/
}