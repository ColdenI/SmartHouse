// простая функция отправки по GBUS
#include "GBUSmini.h"// мини-библиотека с лёгкими функциями

#define TRX_PIN 4    // пин
#define MY_ADDR 1   // наш адрес

struct myRXstruct {
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

uint32_t timer1 = 0;

myRXstruct rxData;              // приёмная структура
byte buffer[sizeof(rxData)];

enum Situation {
  NORMAL = 0,   // нормально
  FIRE = 1,     // пожар
  FLOOD = 2,    // наводнение
  ROBBERY = 3,   // ограбление
  ERROR = 4     // оштбка
};

class Room {
  
public:
  Situation situation;
  byte addres;
  int koll_rele;
  int temp, higr;
  float time_move; // Ð² Ñ‡Ð°ÑÐ°Ñ…
  uint32_t update_time=0;
  bool is_wt_on;
  int error_tupe;
  
  Room(byte addres_, int koll_rele_ = 0){
    addres = addres_;
    koll_rele =  koll_rele;
  }
  
  void getData(){

    for(int i = 0; i < 10; i++)
      GBUS_send_request(TRX_PIN, 3, MY_ADDR);
      if (GBUS_read(TRX_PIN, MY_ADDR, buffer, sizeof(buffer))) {       
        unpackDataBytes(buffer, rxData);

        
        if (this->addres == rxData.addres){
          this->temp = rxData.temp;
          this->higr = rxData.higr;
          this->time_move = rxData.time_move;         
          this->is_wt_on = rxData.is_wt_on;
          if (rxData.is_error == 1) {
            this->situation = ERROR;
            this->error_tupe = rxData.error_tupe;
          }
          else if (rxData.water == 1) this->situation = FLOOD;
          else if (rxData.robber == 1) this->situation = ROBBERY;
          else if (rxData.fire == 1) this->situation = FIRE;
          else this->situation = NORMAL;
          
          this->serial_print();

          this->update_time = millis();
        }
        
      }
      else{
        //Serial.print("\n\nERROR!!  -  "); Serial.print(this->addres); Serial.print("\n\n");
      }
      
  }

  void serial_print(){
    Serial.print("Addres: "); Serial.println(this->addres); 
    Serial.print("Updata time: "); Serial.print(millis() - this->update_time); Serial.println(" m sec"); 
    Serial.print("Temp: "); Serial.print(this->temp); Serial.println(" C*");
    Serial.print("Higr: "); Serial.print(this->higr);  Serial.println(" %"); 
    Serial.print("Time move: "); Serial.print(this->time_move); Serial.println(" hour");
    Serial.print("Is wt on: "); Serial.println(this->is_wt_on);
    Serial.print("Situation: "); Serial.println(this->situation);
    if (this->situation == 4){
      Serial.print("Code ERROR: "); Serial.print(this->error_tupe);
      switch(this->error_tupe){
        case -1: Serial.println(" - unknown"); break;
        case 0: Serial.println(" - no"); break;
        case 1: Serial.println(" - DHT sensor"); break;
        default:Serial.println(" - unknown"); break;
      }
    }
    Serial.println(); 
    
  }
  
};



Room roo1(2);
Room roo2(3);

void setup() {
  pinMode(TRX_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.print("-------------SRART___________");
}

// отправляемая дата (байты)
//char data[] = {' ', 's', 'd'};

void loop() {
roo1.getData();
roo2.getData();



}
