#include <AccelStepper.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <string>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

//Informações da rede wifi
#define SSID "" //Digite aqui o nome
#define PASSWORD "" //Digite aqui a senha

// chave api do firebase
#define API_KEY ""

// Url do banco de dados */
#define DATABASE_URL "" 

// Informações de login do banco de dados
#define USER_EMAIL "" //email
#define USER_PASSWORD "" //senha

const int passos = 2*2048;

#define IN1 16
#define IN2 5
#define IN3 4
#define IN4 0

#define IN5 2
#define IN6 14
#define IN7 12
#define IN8 13

AccelStepper stepper1(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);
AccelStepper stepper2(AccelStepper::HALF4WIRE, IN5, IN7, IN6, IN8);

//Firebase objects
FirebaseData stream;
FirebaseAuth auth;
FirebaseConfig config;

//Informações de localização
String listenerPath = "ESP/itens/";
String itens[4];

// Inicia WiFi
void initWiFi() {
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

// Verifica se houve mudanças no banco de dados
void streamCallback(FirebaseStream data){
  // Armazena o local onde houve a mudança
  String streamPath = String(data.dataPath());

  // Se a mudança for de uma string, um produto foi alterado
  if (data.dataTypeEnum() == fb_esp_rtdb_data_type_string){
    int n = streamPath.substring(1).toInt()-1;
    String item = data.stringData();
    if(item==""&&itens[n]!=""){
      Serial.print(itens[n]);
      Serial.println(" foi retirado");
      itens[n]=item;
      switch (n) {
        case '0':
          item1();
          break;
        case '1':
          item2(); 
          break;
        case '2':
          item3(); 
          break;
        case '3':
          item4(); 
          break;
      }
    }
    else if(item!=""&&itens[n]!=""){
      itens[n]=item;
    }
    else if(item!=""&&itens[n]==""){
      itens[n]=item;
    }
  }
}

void streamTimeoutCallback(bool timeout){
  if (timeout)
    Serial.println("stream timeout, resuming...\n");
  if (!stream.httpConnected())
    Serial.printf("error code: %d, reason: %s\n\n", stream.httpCode(), stream.errorReason().c_str());
}

void setup(){
  Serial.begin(9600);
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(10000);
  stepper1.setCurrentPosition(0);
  stepper2.setMaxSpeed(1000);
  stepper2.setAcceleration(10000);
  stepper2.setCurrentPosition(0);
  initWiFi();
  
  config.api_key = API_KEY;

  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);

  config.token_status_callback = tokenStatusCallback;

  config.max_token_generation_retry = 5;

  Firebase.begin(&config, &auth);

  if (!Firebase.RTDB.beginStream(&stream, listenerPath.c_str()))
    Serial.printf("erro ao iniciar a stream, %s\n\n", stream.errorReason().c_str());

  Firebase.RTDB.setStreamCallback(&stream, streamCallback, streamTimeoutCallback);
  for(int i=0;i<4;i++){
    String text=listenerPath+(i+1);
    Firebase.RTDB.getString(&stream, text);
    itens[i]=stream.stringData();
  }

  delay(2000);
}

void item1(){
  stepper1.moveTo(passos/8);
  while(stepper1.distanceToGo()){
    stepper1.run();
    yield();
  }
  stepper1.setCurrentPosition(0);
  stepper2.moveTo(-passos/4);
  while(stepper2.distanceToGo()){
    stepper2.run();
    yield();
  }
  stepper2.setCurrentPosition(0);
  stepper2.moveTo(passos/4);
  while(stepper2.distanceToGo()){
    stepper2.run();
    yield();
  }
  stepper2.setCurrentPosition(0);
  stepper1.moveTo(-passos/8);
  while(stepper1.distanceToGo()){
    stepper1.run();
    yield();
  }
  stepper1.setCurrentPosition(0);
}

void item2(){
  stepper1.moveTo((3*passos)/8);
  while(stepper1.distanceToGo()){
    stepper1.run();
    yield();
  }
  stepper2.moveTo(-passos/4);
  while(stepper2.distanceToGo()){
    stepper2.run();
    yield();
  }
  stepper2.setCurrentPosition(0);
  stepper2.moveTo(passos/4);
  while(stepper2.distanceToGo()){
    stepper2.run();
    yield();
  }
  stepper2.setCurrentPosition(0);
  stepper1.setCurrentPosition(0);
  stepper1.moveTo(-(3*passos)/8);
  while(stepper1.distanceToGo()){
    stepper1.run();
    yield();
  }
  stepper1.setCurrentPosition(0);
}

void item3(){
  stepper1.moveTo(-passos/8);
  while(stepper1.distanceToGo()){
    stepper1.run();
    yield();
  }
  stepper2.moveTo(-passos/4);
  while(stepper2.distanceToGo()){
    stepper2.run();
    yield();
  }
  stepper2.setCurrentPosition(0);
  stepper2.moveTo(passos/4);
  while(stepper2.distanceToGo()){
    stepper2.run();
    yield();
  }
  stepper2.setCurrentPosition(0);
  stepper1.setCurrentPosition(0);
  stepper1.moveTo(passos/8);
  while(stepper1.distanceToGo()){
    stepper1.run();
    yield();
  }
  stepper1.setCurrentPosition(0);
}

void item4(){
  stepper1.moveTo(-(3*passos)/8);
  while(stepper1.distanceToGo()){
    stepper1.run();
    yield();
  }
  stepper2.moveTo(-passos/4);
  while(stepper2.distanceToGo()){
    stepper2.run();
    yield();
  }
  stepper2.setCurrentPosition(0);
  stepper2.moveTo(passos/4);
  while(stepper2.distanceToGo()){
    stepper2.run();
    yield();
  }
  stepper2.setCurrentPosition(0);
  stepper1.setCurrentPosition(0);
  stepper1.moveTo((3*passos)/8);
  while(stepper1.distanceToGo()){
    stepper1.run();
    yield();
  }
  stepper1.setCurrentPosition(0);
}

void loop(){
  if (Firebase.isTokenExpired()){
    Firebase.refreshToken(&config);
    Serial.println("Recarregar token");
  }
}