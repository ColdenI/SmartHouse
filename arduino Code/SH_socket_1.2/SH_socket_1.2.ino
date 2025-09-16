#include <ESP8266WiFi.h>
#include <SimplePortal.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <GyverButton.h>
#include <NTPClient.h>

#define SENSOR_PIN D1
#define SPIC_PIN D5
#define RELE_PIN D7
#define MODUL_PIN D3
#define connection_attempts 25



//Код защит
const String S_code = "tfCKT-UeQ7W-24yRK-L8PX2-D9waL";

// Имя и пароль вашей сети WiFi
String ssid = "Wifi";
String password = "12345678";

void EEPROM_update();


uint8_t time_Zone = 3;
uint32_t myTimer2;
int n_day_index = 0, n_hour = 0, n_min = 0;

WiFiUDP ntpUdp;
ESP8266WebServer HTTP(80);
NTPClient RealTime(ntpUdp, "pool.ntp.org", 0, 60000);

class Schedule{  
  public:
    uint8_t type = 0;
    uint8_t day_index = 0;
    uint8_t f_index_day = 0, f_hour = 0, f_min = 0;
    uint8_t t_index_day = 0, t_hour = 0, t_min = 0;
    
  public:
    void Create(uint8_t f_hour, uint8_t f_min, uint8_t t_hour, uint8_t t_min){
      this->type = 1;
      this->f_hour = f_hour;
      this->f_min = f_min;
      this->t_hour = t_hour;
      this->t_min = t_min;
    }
    void Create(uint8_t f_hour, uint8_t f_min, uint8_t t_hour, uint8_t t_min, uint8_t day_index){
      this->type = 2;
      this->f_hour = f_hour;
      this->f_min = f_min;
      this->t_hour = t_hour;
      this->t_min = t_min;
      this->day_index = day_index;
    }
    void Create(uint8_t f_index_day, uint8_t f_hour, uint8_t f_min, uint8_t t_index_day, uint8_t t_hour, uint8_t t_min){
      this->type = 3;
      this->f_hour = f_hour;
      this->f_min = f_min;
      this->f_index_day = f_index_day;
      this->t_hour = t_hour;
      this->t_min = t_min;
      this->t_index_day = t_index_day;
    }
    void Destroy(){
      this->type = 0;
    }

    Schedule(void){
      this->type = 0;
    }
        
    bool tick(){
             
      if(this->type == 1){
        if(this->f_hour * 60 + this->f_min <= n_hour * 60 + n_min && n_hour * 60 + n_min < this->t_hour * 60 + this->t_min) return true;
        else return false;
      }else if(this->type == 2){
        if(this->f_hour * 60 + this->f_min <= n_hour * 60 + n_min && n_hour * 60 + n_min < this->t_hour * 60 + this->t_min && this->day_index == n_day_index) return true;
        else return false;
      }else if(this->type == 3){
        if(this->f_hour * 60 + this->f_min <= n_hour * 60 + n_min && n_hour * 60 + n_min < this->t_hour * 60 + this->t_min && f_index_day <= n_day_index <= t_index_day) return true;
        else return false;
      }else
        return false;  
    }
};

class Relay{
 
  public:
    bool is_Flag = 0;
    bool is_Invert = 0;
    int Mode = 1;
    bool is_ON;
    byte EEdel;
    uint8_t relay_pin;
    uint8_t modul_pin;
    bool M_FLAG=0;
    uint32_t delays=600000;
    uint32_t myTimer1;
    GButton Sensor, Modul;
  
    Schedule schedule_1, schedule_2, schedule_3;
  
  
    Relay(uint8_t relay_pin, uint8_t sensor_pin, uint8_t modul_pin, bool SensorType = LOW_PULL){
      this->relay_pin = relay_pin;
      this->modul_pin = modul_pin;
      this->Sensor._PIN = sensor_pin;
      this->Modul._PIN = modul_pin;
      this->Sensor.init();
      this->Modul.init();
      pinMode(this->relay_pin, OUTPUT);
      this->Sensor.setType(SensorType);
    }
  
    void setON(bool is){
      this->is_ON = is;
      digitalWrite(this->relay_pin, this->is_ON);
    }
  
    void modul(){
      if(this->is_Flag == 1){
        this->Modul.tick();
        if(this->Modul.isClick()){
          this->is_ON =!this->is_ON;
          digitalWrite(this->relay_pin, this->is_ON);     
        }
    
      }else{
         this->is_ON = digitalRead(this->modul_pin);
         if (this->is_Invert) this->is_ON = !this->is_ON;
         digitalWrite(this->relay_pin, this->is_ON);
      }
    }
  
    void sensor_tick(){
      if(this->Mode == 4){
        if(this->schedule_1.tick() || this->schedule_2.tick() || this->schedule_3.tick())
          if(this->is_Invert) this->setON(false);
          else this->setON(true);
        else
          if(this->is_Invert) this->setON(true);
          else this->setON(false);
      }

      
    if(this->Mode==1){
      if (this->Sensor.isSingle()){ 
        this->is_ON =!this->is_ON;
        digitalWrite(this->relay_pin, this->is_ON); 
    }}
  
  if (this->Sensor.isDouble()) {
    this->Mode=1;
    EEPROM_update();
    this->myTimer1 = millis();
    tone(SPIC_PIN,1000,100);
  }
  
  if (this->Sensor.isTriple()){
    this->Mode=2;
    EEPROM_update();
    this->myTimer1 = millis();
    tone(SPIC_PIN,1000,100);
    delay(300);
    tone(SPIC_PIN,1000,100);
  }


 if (this->Sensor.hasClicks()){
    if (this->Sensor.getClicks() == 4){
        this->Mode = 3; 
        EEPROM_update();      
        this->myTimer1 = millis();
        tone(SPIC_PIN,1000,100);
        delay(300);
        tone(SPIC_PIN,1000,100);
        delay(300);
        tone(SPIC_PIN,1000,100);
    }
    if (this->Sensor.getClicks() == 5){
        this->Mode = 4; 
        EEPROM_update();      
        this->myTimer1 = millis();
        tone(SPIC_PIN,1000,100);
        delay(300);
        tone(SPIC_PIN,1000,100);
        delay(300);
        tone(SPIC_PIN,1000,100);
        delay(300);
        tone(SPIC_PIN,1000,100);
    }
 }

  if(this->Mode==2)
    if (millis() - this->myTimer1 >= this->delays) {   // ищем разницу (500 мс)
      this->myTimer1 = millis();              // сброс таймера
      this->is_ON =!this->is_ON;
      digitalWrite(this->relay_pin, this->is_ON);
    }
    
  this->Sensor.tick();
  }

};

Relay relay(RELE_PIN, SENSOR_PIN, MODUL_PIN, HIGH_PULL);





void setup() {
  EEPROM.begin(512);
  Serial.begin(9600);

  Serial.println("Code Version: 1.2");
  delay(10);
  
  pinMode(SPIC_PIN, OUTPUT);
  
delay(1000); // задержка для возможности сброса настроек
if(isPressButton()){
  restart_1(); // сброс SSID and PASS
}
  //tool_for_eeprom(64,80); // заполняет '0' все ячейки с - по
  
  reader();   //чтение из EEPROM
  SO_start(); //звук

  WIFIinit(); // инит. сети попытка подключения, конфиг
  HTTP_init();// инит запросов
  
delay(200);
RealTime.begin();


}



void loop(){

  
  relay.Sensor.tick();
  relay.sensor_tick();  // опрос сенсора
  if (relay.Mode == 3) relay.modul(); //опрос модуля
  
  //debug();
  HTTP.handleClient();
  RealTime.update();

  n_day_index = RealTime.getDay(), 
  n_hour = RealTime.getHours() + time_Zone, 
  n_min= RealTime.getMinutes();
  if(n_hour >= 24)n_hour -= 24;

 // Serial.print(n_hour);Serial.print(":");Serial.println(n_min);


}
