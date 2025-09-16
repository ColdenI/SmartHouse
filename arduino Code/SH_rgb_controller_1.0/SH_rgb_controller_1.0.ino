#include <ESP8266WiFi.h>
#include <SimplePortal.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <GyverButton.h>

#define SPIC_PIN D1
#define BUTTON_PIN A0

#define R_PIN D5
#define G_PIN D7
#define B_PIN D6

#define IS_DEBUG 1


#define connection_attempts 30

const String S_code = "a7K9X-8cAh2-AKE4J-fO2WE-QMFI1";

GButton button(BUTTON_PIN);


// Имя и пароль вашей сети WiFi
String ssid = "Wifi";
String password = "12345678";

bool isAuto = 1;
bool isAutoOff = 0;

int Mode = 0;   // лента 0- выкл  1- color  2- gradient  3- jump
int brig = 10;  // 1-10
int speed = 5;  // 1-10

int gradient_i = 0;
int jump_i = 0;
int color_R = 0, color_G = 0, color_B = 0;


long AutoOff_Time = 0;
long Auto_Time = 300000;

uint32_t timer_grad = 0;
uint32_t timer_jump = 0;

uint32_t AutoOff_Timer=0;
uint32_t AutoL_Timer=0;
uint32_t myTimer2 = 0;


ESP8266WebServer HTTP(80);



void setup() {
  
  EEPROM.begin(512);
  Serial.begin(9600);
  delay(10);

 pinMode(R_PIN, OUTPUT);
 pinMode(G_PIN, OUTPUT);
 pinMode(B_PIN, OUTPUT);


  
delay(1000); // задержка для возможности сброса настроек

  //tool_for_eeprom(64,70); // заполняет '0' все ячейки с - по

  reader();   //чтение из EEPROM
  SO_start(); //звук

  WIFIinit(); // инит. сети попытка подключения, конфиг
  HTTP_init();// инит запросов
  
delay(200);
Mode = 2;
}



void loop(){
  mode_tick();
  auto_off_tick();
  auto_tick();

  HTTP.handleClient();
  //delay(1);
}
