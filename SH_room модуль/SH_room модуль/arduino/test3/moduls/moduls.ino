#include "DHT.h"
#include "GBUSmini.h"  // мини-библиотека с лёгкими функциями
// простая функция отправки по GBUS

#define TRX_PIN 4    // пин
#define MY_ADDR 3   // наш адрес
#define M_ADDR 1
#define DHTPIN 2


DHT dht(DHTPIN, DHT11);

uint32_t timer1;
uint32_t timer2;

int sec, min, hour;

struct myTXstruct {
  bool is_error;
  bool is_wt_on;
  bool fire;
  bool water;
  bool robber;
  int addres;
  int higr;
  int error_tupe;  
  float temp;
  float time_move;
};

myTXstruct txData;
byte buffer[sizeof(txData)]; 

void setup() {
  dht.begin();
  pinMode(TRX_PIN, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  txData.addres = MY_ADDR;
  //Serial.begin(9600);

  txData.is_wt_on = 0;
  txData.fire = 0;
  txData.water = 0;
  txData.robber = 0;
  txData.temp = 24;
  txData.higr = 60;
  txData.time_move = 0.5;
}

void loop() {

  if (GBUS_read_request(TRX_PIN, MY_ADDR)) tickk();
    if (millis() - timer1 >= 1000) {   // ищем разницу (500 мс)
      timer1 = millis();              // сброс таймера
      sec++;
      if (sec >= 60){
        sec = 0;
        min++;
        if (min >= 60){
          min = 0;
          hour++;
          if (hour >= 24)
            hour = 0;                   
        }
      }
    }
}


void tickk(){
  Serial.print(1);

  float h = dht.readHumidity(); //Измеряем влажность
  float t = dht.readTemperature(); //Измеряем температуру

  if (isnan(h) || isnan(t)) {
    txData.is_error = 1;
    txData.error_tupe = 1;
  }else{
    txData.is_error = 0;
    txData.error_tupe = 0;
  }
    
  txData.is_wt_on = 0;
  txData.fire = 0;
  txData.water = 0;
  txData.robber = 0;
  txData.temp = t;
  txData.higr = h;
  txData.time_move = 0;
  packDataBytes(buffer, txData);
  GBUS_send(TRX_PIN, M_ADDR, MY_ADDR, buffer, sizeof(buffer));

  delay(4);

  

}


void read_(){
  
}

void draw(){
  
}
