#include <SoftwareSerial.h>

const int pinSensorHumidity = A5;
const int pinBomb = 8;

SoftwareSerial arduinoYun(2,3); // (RX, TX)

int initialized = 0;

void setup() {
  Serial.begin(9600);

  arduinoYun.begin(9600);
  
  pinMode(pinBomb, OUTPUT);
}

void loop() {
  initialize();

  int humidity = readHumidity();
  Serial.print(" - ");
  controlBomb(humidity);
  Serial.print(" - ");
  sendData(humidity);
  Serial.println();
  
  delay(3600000);
}

void initialize(){
  if (initialized == 0) {
    Serial.println("|------------------------------------------------------------|");
    Serial.println("|--------     Sistema de irrigação Arduino (UNO)     --------|");
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

int readHumidity(){
  int humidity = analogRead(pinSensorHumidity);

  if (humidity > 800) {
    Serial.print("Baixa umidade!");
  } else if (humidity > 600) {
    Serial.print("Media umidade!");
  } else {
    Serial.print("Alta umidade");
  }
    Serial.print(" - ");
    Serial.print(humidity);
    return humidity;
}

void controlBomb(int humidity){
  if (humidity > 800) {
    Serial.print("Estamos molhando a plantinha :)");
    digitalWrite(pinBomb, HIGH);
    delay(6000);
  } else if (humidity > 600) {
    Serial.print("A plantinha está bém =D");
  } else {
    Serial.print("A plantinha está com bastante água");
  }
    digitalWrite(pinBomb, LOW);
}

void sendData(int humidity) {
  arduinoYun.print(humidity);
  Serial.print("Dados enviados ao servidor!");
}
