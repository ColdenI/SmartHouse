#include <ESP8266WiFi.h>
#include <SimplePortal.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <GyverButton.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#define IR_PIN D5
#define SPIC_PIN D2
#define RELE_PIN D1

#define IS_RADIO_P 0

#define RADIO_1_PIN D3
#define RADIO_2_PIN D4
#define RADIO_3_PIN D7 
#define RADIO_4_PIN D8

#define IS_DEBUG 0

#define connection_attempts 30

const String S_code = "tfCKT-UeQ7W-24yRK-L8PX2-D9waL";

IRrecv irrecv(IR_PIN);
decode_results results;

GButton btA(RADIO_1_PIN);
GButton btB(RADIO_2_PIN);
GButton btC(RADIO_4_PIN);
GButton btD(RADIO_3_PIN);


// Имя и пароль вашей сети WiFi
String ssid = "Wifi";
String password = "12345678";

bool isAuto = 1;
bool isAutoOff = 0;

int Mode_l = 0;   // лента 0- выкл
bool is_lemp = 1; // лампа
long AutoOff_Time = 0;
long Auto_Time = 300000;



uint32_t AutoOff_Timer=0;
uint32_t AutoL_Timer=0;
uint32_t myTimer2 = 0;


ESP8266WebServer HTTP(80);



void setup() {
btA.setType(LOW_PULL);
btB.setType(LOW_PULL);
btC.setType(LOW_PULL);
btD.setType(LOW_PULL);
  
  EEPROM.begin(512);
  Serial.begin(9600);
  delay(10);

  pinMode(RELE_PIN, OUTPUT);
  pinMode(SPIC_PIN, OUTPUT);
  
delay(1000); // задержка для возможности сброса настроек

  //tool_for_eeprom(64,70); // заполняет '0' все ячейки с - по
  set_Lemp(0);
  reader();   //чтение из EEPROM
  SO_start(); //звук

  WIFIinit(); // инит. сети попытка подключения, конфиг
  HTTP_init();// инит запросов
  
delay(200);

}



void loop(){
  if (IS_RADIO_P)radio_tick();
  
  auto_off_tick();
  auto_tick();

  HTTP.handleClient();
  //delay(1);
}
