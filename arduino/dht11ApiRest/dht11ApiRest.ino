#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <ArduinoJson.h>
#include "DHTesp.h"
#define DHTpin 15

//variables WiFi
const char* ssid="dr-rojano";
const char* password="78928-tw";

//ServidorWeb
AsyncWebServer server(80);

//Formato Json
StaticJsonDocument<250> jsonDocument;
char buffer[250];

//Variables Sensor
DHTesp dht;
String estado = "ok";
float temperatura = 0.0;
float humedad = 1.5;
float indiceCalor = 0.0;

//Método para conectarse a la red WiFi
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

char* getTemperatura(){
  temperatura = dht.getTemperature();
  create_json(estado, "temperatura", String(temperatura), "°C");
  return buffer;
}

char* getHumedad(){
  humedad =  dht.getHumidity();
  create_json(estado, "humedad", String(humedad), "°C");
  return buffer;
}

char* getCalor(){
  temperatura = dht.getTemperature();
  humedad =  dht.getHumidity();
  indiceCalor = dht.computeHeatIndex(temperatura, humedad, false);
  create_json(estado, "indiceCalor", String(indiceCalor), "°C");
  return buffer;
}

//Método que establece las rutas
void establecerRutas(){
  server.on("/temperatura",HTTP_GET,[](AsyncWebServerRequest * request){
    request->send(200, "application/json", getTemperatura());
  });
  server.on("/humedad",HTTP_GET,[](AsyncWebServerRequest * request){
    request->send(200, "application/json", getHumedad());
  });
  server.on("/indiceCalor",HTTP_GET,[](AsyncWebServerRequest * request){
    request->send(200, "application/json", getCalor());
  });
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");  
  server.begin();  
}

//Métodos predefinidos JSON
void create_json(String estado, char *dato, String valor, char *unidad) {  
  jsonDocument.clear();  
  jsonDocument["estado"] = estado;
  jsonDocument["dato"] = dato;
  jsonDocument["valor"] = valor;
  jsonDocument["unidad"] = unidad;
  serializeJson(jsonDocument, buffer);
}

void add_json_object(String estado, char *dato, String valor, char *unidad) {
  JsonObject obj = jsonDocument.createNestedObject();
  obj["estado"] = estado;
  obj["dato"] = dato;
  obj["valor"] = valor;
  obj["unidad"] = unidad;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.setup(DHTpin, DHTesp::DHT11);
  conectarse();
  establecerRutas();
}

void loop() {
  // put your main code here, to run repeatedly:

}
