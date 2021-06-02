#include <SoftwareSerial.h>
#include <string.h>
int bluetoothTx = 0;
int bluetoothRx = 1;
int lastH = 0;
int lastT = 0;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

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
#define cerrado 51
#define abierto 50
#define hume 32
#define temp 33

//Variable LDR
#define LDR  A0
int valorAnterior = 0;

//
#define luzP 31

const int echoPin = 52;
const int triggerPin =53;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  //Inicializa DHT22
  dht.begin();
  
  //Inicializa Pines LED
  pinMode(luz1, OUTPUT);
  pinMode(luz2, OUTPUT);
  pinMode(luz3, OUTPUT);
  pinMode(luz4, OUTPUT);
  pinMode(luz5, OUTPUT);
  pinMode(luz6, OUTPUT);
  pinMode(luz7, OUTPUT);
  pinMode(luz8, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(cerrado, OUTPUT);
  pinMode(abierto, OUTPUT);

  pinMode(hume, OUTPUT);
  pinMode(temp, OUTPUT);
  
  digitalWrite(abierto, HIGH);
  
  pinMode(luzP, OUTPUT);
}

void loop() {
  //prenderLuces();
  obtenerTemperatura();
  //obtenerLDR();
  obtenerHumedad();
  //delay(1000);
  //apagarLuces();
  //delay(1000);
  //detectarPersona();
  menu();
  checkTempHum();
  obtenerLDR();
}

void menu(){
  if (Serial.available()  ){
    String opcion = Serial.readString();
    opcion.trim();
    if(opcion == "encender 1"){
      digitalWrite(luz1,HIGH);
      Serial.println("Luz 1 Encendida");
    }
    else if(opcion == "Apagar uno"){
      digitalWrite(luz1,LOW);
      Serial.println("Luz 1 Apagada");
    }
    else if(opcion == "encender 2"){
      digitalWrite(luz2,HIGH);
      Serial.println("Luz 2 Encendida");
    }
    else if(opcion == "Apagar 2"){
      digitalWrite(luz2,LOW);
      Serial.println("Luz 2 Apagada");
    }
    else if(opcion == "encender 3"){
      digitalWrite(luz3,HIGH);
      Serial.println("Luz 3 Encendida");
    }
    else if(opcion == "lApagar 3"){
      digitalWrite(luz3,LOW);
      Serial.println("Luz 3 Apagada");
    }
    else if(opcion == "encender 4"){
      digitalWrite(luz4,HIGH);
      Serial.println("Luz 4 Encendida");
    }
    else if(opcion == "Apagar 4"){
      digitalWrite(luz4,LOW);
      Serial.println("Luz 4 Apagada");
    }
    else if(opcion == "encender 5"){
      digitalWrite(luz5,HIGH);
      Serial.println("Luz 5 Encendida");
    }
    else if(opcion == "Apagar 5"){
      digitalWrite(luz5,LOW);
      Serial.println("Luz 5 Apagada");
    }
    else if(opcion == "encender 6"){
      digitalWrite(luz6,HIGH);
      Serial.println("Luz 6 Encendida");
    }
    else if(opcion == "Apagar 6"){
      digitalWrite(luz6,LOW);
      Serial.println("Luz 6 Apagada");
    }
    else if(opcion == "encender 7"){
      digitalWrite(luz7,HIGH);
      Serial.println("Luz 7 Encendida");
    }
    else if(opcion == "Apagar 7"){
      digitalWrite(luz7,LOW);
      Serial.println("Luz 7 Apagada");
    }
    else if(opcion == "encender 8"){
      digitalWrite(luz8,HIGH);
      Serial.println("Luz 8 Encendida");
    }
    else if(opcion == "Apagar 8"){
      digitalWrite(luz8,LOW);
      Serial.println("Luz 8 Apagada");
    }
    else if (opcion == "temperatura"){
      obtenerTemperatura();
    }
    else if (opcion == "humedad"){
      obtenerHumedad();
    }
    else if(opcion == "encender todas"){
      prenderLuces();
    }
    else if(opcion == "Apagar todas"){
      apagarLuces();
    }
    else if (opcion == "abrir") {
      digitalWrite(abierto, HIGH);
      digitalWrite(cerrado, LOW);
      delay(100);
    }
    else{
      Serial.println("Comando no reconocido");
    }
  }
}

void detectarPersona() {
  delay(1000);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long cm, duracion;
  duracion = pulseIn(echoPin, HIGH);
  cm = duracion / 29 / 2;

  Serial.println(cm);
  delay(100);

  if (cm < 900) {
    digitalWrite(abierto, LOW);
    digitalWrite(cerrado, HIGH);
  }
  

  
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
  if(isnan(t)){
    Serial.println("Error al leer");
    return;
  }
  if(t!=lastT){
    lastT = t;
    String comm = "t ";
    comm += t;
    Serial.println(comm);
  }
}

void obtenerHumedad(){
  float h = dht.readHumidity();
  if(isnan(h)){
    Serial.println("Error al leer Humedad");
    return;
  }
  if(h!=lastH){
    lastH = h;
    String comm = "h ";
    comm += h;
    Serial.println(comm);
  }
}

void obtenerLDR(){
  int valor = analogRead(LDR);
  delay(100);
  if( valorAnterior != valor){
    valorAnterior = valor;
    if(valorAnterior <= 100){
      digitalWrite(luzP,HIGH);
    }
    else{
      digitalWrite(luzP,LOW);
    }
  }
}

void checkTempHum(){
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if( isnan(t)){
    Serial.println("Error al leer");
    return;
  }
  if( isnan(h)){
    Serial.println("Error al leer");
    return;
  }
  if(h<40 or h>60){
    digitalWrite(hume,HIGH);
  }
  else{
    digitalWrite(hume,LOW);
  }
  if(t<19 or t>25){
    digitalWrite(temp,HIGH);
  }
  else{
    digitalWrite(temp,LOW);
  }
}
