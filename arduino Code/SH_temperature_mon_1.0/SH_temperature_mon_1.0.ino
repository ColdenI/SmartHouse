#include <ESP8266WiFi.h>
#include <SimplePortal.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <EEPROM.h>
#include "DHT.h"
#include <GyverButton.h>



#define DHT_TYPE DHT11 
#define DHT_PIN D2   
#define SPIC_PIN D1

#define connection_attempts 25

const String S_code = "tfCKT-UeQ7W-24yRK-L8PX2-D9waL";

//Код защит

// Имя и пароль вашей сети WiFi
String ssid = "Wifi";
String password = "12345678";


float Temp, Hum;
int isF = 0;



uint32_t myTimer1;
uint32_t myTimer2;



ESP8266WebServer HTTP(80);
DHT dht(DHT_PIN, DHT_TYPE);


void setup() {
  EEPROM.begin(512);
  Serial.begin(9600);
  delay(10);
  
  pinMode(SPIC_PIN, OUTPUT);

  dht.begin();

  
  delay(1000); // задержка для возможности сброса настроек

  //tool_for_eeprom(64,70); // заполняет '0' все ячейки с - по
  
  reader();   //чтение из EEPROM
  SO_start(); //звук

  WIFIinit(); // инит. сети попытка подключения, конфиг
  HTTP_init();// инит запросов
  
delay(200);

}



void loop(){

  Temp = dht.readTemperature(); //Измеряем температуру
  Hum = dht.readHumidity(); //Измеряем влажность
  //debug();
  HTTP.handleClient();
  //delay(1);
}
