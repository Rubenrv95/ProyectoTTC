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

//Variable LDR
#define LDR  A0
int valorAnterior = 0;

//
#define luzP 31

const int echoPin = 52;
const int triggerPin =53;

void setup() {
  Serial.begin(9600);

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
  
  digitalWrite(abierto, HIGH);
  
  pinMode(luzP, OUTPUT);
    Serial.println("Ingresa comando:");
}

void loop() {
  //prenderLuces();
  //obtenerTemperatura();
  //obtenerLDR();
  //obtenerHumedad();
  //delay(1000);
  //apagarLuces();
  //delay(1000);
  detectarPersona();
  menu();
  obtenerLDR();
  
}

void menu(){
  if (Serial.available()  ){
    String opcion = Serial.readString();
    opcion.trim();
    if(opcion == "luz 1 on"){
      digitalWrite(luz1,HIGH);
    }
    else if(opcion == "luz 1 off"){
      digitalWrite(luz1,LOW);
    }
    else if(opcion == "luz 2 on"){
      digitalWrite(luz2,HIGH);
    }
    else if(opcion == "luz 2 off"){
      digitalWrite(luz2,LOW);
    }
    else if(opcion == "luz 3 on"){
      digitalWrite(luz3,HIGH);
    }
    else if(opcion == "luz 3 off"){
      digitalWrite(luz3,LOW);
    }
    else if(opcion == "luz 4 on"){
      digitalWrite(luz4,HIGH);
    }
    else if(opcion == "luz 4 off"){
      digitalWrite(luz4,LOW);
    }
    else if(opcion == "luz 5 on"){
      digitalWrite(luz5,HIGH);
    }
    else if(opcion == "luz 5 off"){
      digitalWrite(luz5,LOW);
    }
    else if(opcion == "luz 6 on"){
      digitalWrite(luz6,HIGH);
    }
    else if(opcion == "luz 6 off"){
      digitalWrite(luz6,LOW);
    }
    else if(opcion == "luz 7 on"){
      digitalWrite(luz7,HIGH);
    }
    else if(opcion == "luz 7 off"){
      digitalWrite(luz7,LOW);
    }
    else if(opcion == "luz 8 on"){
      digitalWrite(luz8,HIGH);
    }
    else if(opcion == "luz 8 off"){
      digitalWrite(luz8,LOW);
    }
    else if (opcion == "temperatura"){
      obtenerTemperatura();
    }
    else if (opcion == "humedad"){
      obtenerHumedad();
    }
    else if(opcion == "luces on"){
      prenderLuces();
    }
    else if(opcion == "luces off"){
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
