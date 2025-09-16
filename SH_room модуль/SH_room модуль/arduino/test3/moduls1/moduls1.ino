#include "DHT.h"
#include "GBUSmini.h"  // мини-библиотека с лёгкими функциями
// простая функция отправки по GBUS

#define TRX_PIN 4    // пин
#define MY_ADDR 2   // наш адрес
#define M_ADDR 1
#define DHTPIN 2


DHT dht(DHTPIN, DHT11);

struct myTXstruct {
  bool is_error;
  bool is_wt_on;
  bool fire;
  bool water;
  bool robber;
  int addres;
  int higr;  
  float temp;
  float time_move;
};

myTXstruct txData;
byte buffer[sizeof(txData)]; 

void setup() {
  dht.begin();
  pinMode(TRX_PIN, INPUT_PULLUP);
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
  tickk();

}


void tickk(){
  float h = dht.readHumidity(); //Измеряем влажность
  float t = dht.readTemperature(); //Измеряем температуру

  if (isnan(h) || isnan(t)) {
    txData.is_error = 1;
  }else{
    txData.is_error = 0;
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
  delay(random(100,1000));

}
