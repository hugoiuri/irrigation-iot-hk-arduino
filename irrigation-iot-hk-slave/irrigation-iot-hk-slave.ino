#include <SoftwareSerial.h>
#include <Bridge.h>
#include <HttpClient.h>

SoftwareSerial arduinoUno(9,10); // (RX, TX)

int initialized = 0;
String url = "http://iot-irrigation-hk.herokuapp.com/measurements"; //URL Sever 

void setup() {
  Serial.begin(9600);
  
  Bridge.begin();
  
  arduinoUno.begin(9600);
}

void loop() {
  initialize();
  
  if (arduinoUno.available() > 0){
    String humidity = getHumidity();
    Serial.print(" - ");
    String result = postHumidity(humidity);
  }
}

void initialize(){
  if (initialized == 0) {
    Serial.println("|------------------------------------------------------------|");
    Serial.println("|--------      Sistema de irrigação Arduino (YÚN)    --------|");
    Serial.println("|--------               Sistema Ligado               --------|");
    Serial.println("|------------------------------------------------------------|");
    Serial.println("|--------   Autores:                                 --------|");
    Serial.println("|--------            Hugo Iuri - @hugoiuri           --------|");
    Serial.println("|--------            Karine Cordeiro - @kpazfagundes --------|");
    Serial.println("|------------------------------------------------------------|");
    Serial.println();
    initialized = 1;
  }
}

String getHumidity(){
  String humidity = "";
  
  while (arduinoUno.available()) {
    char c = arduinoUno.read();
    humidity = humidity + c;
  }
  Serial.print("Umidade recebida: ");
  Serial.print(humidity);
  return humidity;
}

String postHumidity(String humidity){
  String result = "";
  String body = "{ \"type\": \"humidity\", \"value\": " + humidity + " }";
    
  HttpClient client;
  client.setHeader("Content-Type: application/json");
  client.post(url, body);

  while (client.available()) {
    char c = client.read();
    result = result + c;
  }
  
  Serial.print("Dados enviados para a API - ");
  Serial.println (result);
  return result;
}
