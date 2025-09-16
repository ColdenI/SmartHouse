#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
//#include <SimplePortal.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <GyverButton.h>

 
#define SPIC_PIN D1

uint16_t connection_attempts = 25;
String local_ip = "192.168.4.1";

const String S_code = "tfCKT-UeQ7W-24yRK-L8PX2-D9waL";

//Код защит

// Имя и пароль вашей сети WiFi
String ssid = "Wifi";
String password = "12345678";
String admin_login = "admin"; // e
String admin_password = "admin"; // e

uint32_t myTimer1;
uint32_t myTimer2;

ESP8266WebServer HTTP(80);

void setup() {
  EEPROM.begin(512);
  Serial.begin(9600);
  local_ip = "192.168.4.1";
  delay(10);
  
  pinMode(SPIC_PIN, OUTPUT);
  delay(1000); // задержка для возможности сброса настроек

  //EEPROM_Clear();
  //tool_for_eeprom(0, 170);

  EEPROM_Read();   //чтение из EEPROM
  SO_start();      //звук
  
  HTTP_init();// инит запросов
  
  if(read_String(70).toInt() == 1) Config_mode();
  else WIFIinit(); // инит. сети попытка подключения, конфиг
  

  
  delay(200);

}



void loop(){
  //debug();
  HTTP.handleClient();
  //delay(1);
}
