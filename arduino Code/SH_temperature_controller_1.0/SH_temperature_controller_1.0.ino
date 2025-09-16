#include <ESP8266WiFi.h>
#include <SimplePortal.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <EEPROM.h>
#include "DHT.h"
#include <GyverButton.h>



#define DHT_TYPE DHT11 
#define DHT_PIN D2   
#define SPIC_PIN D4

#define SENSOR_PIN_1 D1
#define SENSOR_PIN_2 D3
#define RELE_PIN_1 D5
#define RELE_PIN_2 D6


#define connection_attempts 25

const String S_code = "tfCKT-UeQ7W-24yRK-L8PX2-D9waL";

//Код защит

// Имя и пароль вашей сети WiFi
String ssid = "Wifi";
String password = "12345678";


uint8_t Mode = 0; // 0- измерение температуры, 1- режим условий, 2- вкл. охлаждение, 3- вкл. отопление
float Temp, Hum;


uint32_t delays=600000;
uint32_t myTimer1;
uint32_t myTimer2;



ESP8266WebServer HTTP(80);
GButton butt1(SENSOR_PIN_1);
GButton butt2(SENSOR_PIN_2);
DHT dht(DHT_PIN, DHT_TYPE);


void setup() {
  EEPROM.begin(512);
  Serial.begin(9600);
  delay(10);
  
  butt1.setType(HIGH_PULL);
  butt2.setType(HIGH_PULL);
  
  pinMode(RELE_PIN_1, OUTPUT);
  pinMode(RELE_PIN_2, OUTPUT);
  pinMode(SPIC_PIN, OUTPUT);

  dht.begin();

  
  delay(1000); // задержка для возможности сброса настроек
  butt1.tick();
  butt2.tick();
  if(butt1.isPress() || butt2.isPress()){
    restart_1(); // сброс SSID and PASS
  }
  //tool_for_eeprom(64,70); // заполняет '0' все ячейки с - по
  
  reader();   //чтение из EEPROM
  SO_start(); //звук

  WIFIinit(); // инит. сети попытка подключения, конфиг
  HTTP_init();// инит запросов
  
delay(200);

}



void loop(){
  butt1.tick();
  butt2.tick();
  sensor_tick();  // опрос сенсора

  
  debug();
  HTTP.handleClient();
  //delay(1);
}
