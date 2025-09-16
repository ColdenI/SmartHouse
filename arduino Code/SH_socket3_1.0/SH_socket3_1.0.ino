#include <ESP8266WiFi.h>
#include <SimplePortal.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <GyverButton.h>

#define SPIC_PIN D1

#define SENSOR_PIN_1 D8
#define SENSOR_PIN_2 D7
#define SENSOR_PIN_3 D6

#define RELE_PIN_1 D4
#define RELE_PIN_2 D3
#define RELE_PIN_3 D2

#define connection_attempts 20

//Код защит

// Имя и пароль вашей сети WiFi
String ssid = "Wifi";
String password = "12345678";

struct Soc {
  
int Mode = 1;
boolean is_ON;
byte EEdel;

uint32_t delays=600000;
uint32_t myTimer1;
};

uint32_t myTimer2;

ESP8266WebServer HTTP(80);

GButton butt_1(SENSOR_PIN_1);
GButton butt_2(SENSOR_PIN_2);
GButton butt_3(SENSOR_PIN_3);

Soc S1, S2, S3;

void WIFIinit();
void restart_1();
void HTTP_init(void);

void setup() {
  EEPROM.begin(512);
  Serial.begin(9600);
  delay(10);
  
  butt_1.setType(LOW_PULL);
  butt_2.setType(LOW_PULL);
  butt_3.setType(LOW_PULL);
  
  pinMode(RELE_PIN_1, OUTPUT);
  pinMode(RELE_PIN_2, OUTPUT);
  pinMode(RELE_PIN_3, OUTPUT);
  
  pinMode(SPIC_PIN, OUTPUT);
  
delay(1000); // задержка для возможности сброса настроек

butt_1.tick();
butt_2.tick();
butt_3.tick();

if(butt_1.isPress() || butt_2.isPress() || butt_3.isPress()){
  restart_1(); // сброс SSID and PASS
}
  tool_for_eeprom(64,74); // заполняет '0' все ячейки с - по
  
  reader();   //чтение из EEPROM
  SO_start(); //звук

  WIFIinit(); // инит. сети попытка подключения, конфиг
  HTTP_init();// инит запросов
  
delay(200);

}



void loop(){
  butt_1.tick();
  butt_2.tick();
  butt_3.tick();
  
  sensor_tick();  // опрос сенсора
  
  
  //debug();
  HTTP.handleClient();
  //delay(1);
}
