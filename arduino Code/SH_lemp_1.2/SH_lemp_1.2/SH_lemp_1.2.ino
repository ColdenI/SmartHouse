#include <ESP8266WiFi.h>
#include <SimplePortal.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <GyverButton.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <NTPClient.h>

#define IR_PIN D5
#define SPIC_PIN D2
#define RELE_PIN D1

#define IS_RADIO_P 1

#define RADIO_1_PIN D3
#define RADIO_2_PIN D4
#define RADIO_3_PIN D7 
#define RADIO_4_PIN D8

#define IS_DEBUG 0

#define connection_attempts 30

const String S_code = "wjIdB-Jrpfo-Ln2Tf-bRpD9-PSyzD";

IRrecv irrecv(IR_PIN);
decode_results results;

GButton btA(RADIO_1_PIN);
GButton btB(RADIO_2_PIN);
GButton btC(RADIO_4_PIN);
GButton btD(RADIO_3_PIN);

// Имя и пароль вашей сети WiFi
String ssid = "Wifi";
String password = "12345678";

void set_Lemp(bool val);

uint8_t time_Zone = 3;

int n_day_index = 0, n_hour = 0, n_min = 0;

bool isAuto = 1;
bool isAutoOff = 0;

int Mode_l = 0;   // лента 0- выкл
bool is_lemp = 1; // лампа
uint32_t AutoOff_Time = 0;
uint32_t Auto_Time = 300000;


uint32_t AutoOff_Timer=0;
uint32_t AutoL_Timer=0;
uint32_t myTimer2 = 0;
uint32_t TimerAlarmClock = 0;
bool isAlarmClockOn = false;

WiFiUDP ntpUdp;
NTPClient RealTime(ntpUdp, "pool.ntp.org", 0, 60000);
ESP8266WebServer HTTP(80);



class Schedule{

  public:
    uint8_t type = 0;
    uint8_t day_index = 0;
    uint8_t f_hour = 0, f_min = 0;
    bool isOn = false;
    bool _isOn = false;
    uint16_t ni = 0;
    uint16_t nii = 0;
    bool isInvLamp = true;

    
  public:
    void Create(uint8_t f_hour, uint8_t f_min, bool isInvLamp = true){
      this->type = 1;
      this->f_hour = f_hour;
      this->f_min = f_min;
      this->_isOn = true;
      this->isOn = false;
      this->ni = 0;
      this->nii = 0;
      this->isInvLamp = isInvLamp;
      
    }
    void Create(uint8_t f_hour, uint8_t f_min, uint8_t day_index, bool isInvLamp = true){
      this->type = 2;
      this->f_hour = f_hour;
      this->f_min = f_min;
      this->day_index = day_index;
      this->_isOn = true;
      this->isOn = false;
      this->ni = 0;
      this->nii = 0;
      this->isInvLamp = isInvLamp;
    }

    void Destroy(){
      this->type = 0;
      this->_isOn = false;
      this->isOn = false;
      this->ni = 0;
      this->nii = 0;
      set_Lemp(1);
    }

    Schedule(void){
      this->type = 0;
      this->_isOn = false;
      this->isOn = false;
      this->ni = 0;
      this->nii = 0;
    }
        
    void tick(){        
      if(this->type == 1 && _isOn){
        if(this->f_hour * 60 + this->f_min == n_hour * 60 + n_min) {
          this->_isOn = false;
          this->isOn = true;
          this->ni = 0;
          this->nii = 0;
        }else{
          
        }
      }else if(this->type == 2 && _isOn){
        if(this->f_hour * 60 + this->f_min == n_hour * 60 + n_min && this->day_index == n_day_index){
          this->_isOn = false;
          this->isOn = true;
          this->ni = 0;
          this->nii = 0;
        }else{
           
        }
      } 
    }

    
};


Schedule schedule;


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
RealTime.begin();

}



void loop(){
  alarm_clock();
  
  if (IS_RADIO_P)radio_tick();
  
  auto_off_tick();
  auto_tick();

  RealTime.update();

  n_day_index = RealTime.getDay(), 
  n_hour = RealTime.getHours() + time_Zone, 
  n_min= RealTime.getMinutes();
  if(n_hour >= 24)n_hour -= 24;
  
  HTTP.handleClient();
  //delay(1);
}
