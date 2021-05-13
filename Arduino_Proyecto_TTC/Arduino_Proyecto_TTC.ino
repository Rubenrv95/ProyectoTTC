//Variables Sensor Temperatura/Humedad
#include "DHT.h"
#define DHTTYPE DHT11
const int DHTPIN = 22;
DHT dht(DHTPIN,DHTTYPE);

//Variables Luces Interiores
#define luz1 23
#define luz2 24
#define luz3 25
#define luz4 26
#define luz5 27
#define luz6 28
#define luz7 29
#define luz8 30

//Variable LDR
const int LDR = A0;

//
#define led 31

void setup() {
  Serial.begin(9600);

  //Inicializa DHT22
  dht.begin();
  //Inicializa LDR
  pinMode(LDR, INPUT);
  
  //Inicializa Pines LED
  pinMode(luz1, OUTPUT);
  pinMode(luz2, OUTPUT);
  pinMode(luz3, OUTPUT);
  pinMode(luz4, OUTPUT);
  pinMode(luz5, OUTPUT);
  pinMode(luz6, OUTPUT);
  pinMode(luz7, OUTPUT);
  pinMode(luz8, OUTPUT);
  
  pinMode(led, OUTPUT);   
}

void loop() {
  prenderLuces();
  obtenerTemperatura();
  obtenerLDR();
  obtenerHumedad();
  delay(1000);
  apagarLuces();
  delay(1000);
  
}

void prenderLuces(){
  digitalWrite(luz1, HIGH);
  digitalWrite(luz2, HIGH);
  digitalWrite(luz3, HIGH);
  digitalWrite(luz4, HIGH);
  digitalWrite(luz5, HIGH);
  digitalWrite(luz6, HIGH);
  digitalWrite(luz7, HIGH);
  digitalWrite(luz8, HIGH);
}

void apagarLuces(){
  digitalWrite(luz1, LOW);
  digitalWrite(luz2, LOW);
  digitalWrite(luz3, LOW);
  digitalWrite(luz4, LOW);
  digitalWrite(luz5, LOW);
  digitalWrite(luz6, LOW);
  digitalWrite(luz7, LOW);
  digitalWrite(luz8, LOW);  
}

void obtenerTemperatura(){
  float t = dht.readTemperature();
  if( isnan(t)){
    Serial.println("Error al leer");
    return;
  }
  Serial.println(t);
}

void obtenerHumedad(){
  float h = dht.readHumidity();
  if(isnan(h)){
    Serial.println("Error al leer Humedad");
    return;
  }
  Serial.println(h);
}

void obtenerLDR(){
  int valor = analogRead(LDR);
  Serial.println(valor);
}
