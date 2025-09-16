#include "Arduino.h"

class Room {
  
public:
  byte addres;
  int koll_rele;
  int temp, higr;
  float time_move; // в часах
  uint32_t update_time;
  bool is_wt_on;
  
  Room(byte addres_, int koll_rele_ = 0){
    addres = addres_;
    koll_rele =  koll_rele;
  }
  
  void getData(){
        
      byte data[6];
      String a = "";
      if (GBUS_read(TRX_PIN, MY_ADDR, data, sizeof(data))) {
        // если успешно приняли
        for (byte i = 0; i < sizeof(data); i++) {
          Serial.print(data[i]);
          Serial.print(" ");
          a += data[i];
        }
        Serial.print(a);
        Serial.println();
      }
      
  }
};
