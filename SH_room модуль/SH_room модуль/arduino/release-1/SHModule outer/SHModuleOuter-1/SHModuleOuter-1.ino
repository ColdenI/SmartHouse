/*
  ░██████╗███╗░░░███╗░█████╗░██████╗░████████╗    ██╗░░██╗░█████╗░██╗░░░██╗░██████╗███████╗
  ██╔════╝████╗░████║██╔══██╗██╔══██╗╚══██╔══╝    ██║░░██║██╔══██╗██║░░░██║██╔════╝██╔════╝
  ╚█████╗░██╔████╔██║███████║██████╔╝░░░██║░░░    ███████║██║░░██║██║░░░██║╚█████╗░█████╗░░
  ░╚═══██╗██║╚██╔╝██║██╔══██║██╔══██╗░░░██║░░░    ██╔══██║██║░░██║██║░░░██║░╚═══██╗██╔══╝░░
  ██████╔╝██║░╚═╝░██║██║░░██║██║░░██║░░░██║░░░    ██║░░██║╚█████╔╝╚██████╔╝██████╔╝███████╗
  ╚═════╝░╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░    ╚═╝░░╚═╝░╚════╝░░╚═════╝░╚═════╝░╚══════╝

********************************************************************* Colden I ******************************************************************
********************************************************************* V-0.1 ******************************************************************
*/

#include "DHT.h"
#include "GyverButton.h"
#include "buildTime.h"

//**********SETTINGS**********

#define DHT_TYPE                     DHT11    // тип датчика DHT
#define TIME_AUTO_DATA               5        // время авто отправки данных (в секундах)
#define IS_WATHER                    0        // подключён ли датчик утечки (1/0)
#define IS_MOVE                      1        // подключён ли датчик движения (1/0)
#define IS_GAZ                       1        // подключён ли датчик газа (1/0)
#define IS_DEBUG                     0        // режим отладки (1/0)


#define DHT_PIN                      2        // пин подключения DHT
#define BAZER_PIN                    4        // пин зумера

#define WATHER_PIN                   0        // пин датчика утечки воды
#define GAZ_PIN                      A2       // пин датчика газа
#define MOVE_PIN                     A1       // пин датчика движения

#define latchPin                     12       // пин реле
#define clockPin                     11       // пин реле
#define dataPin                      13       // пин реле



struct Rele_st {
  bool is_on = 0;
};

Rele_st rele1, rele2, rele3, rele4, rele5, rele6, rele7, rele8;

// сенсоры
GButton mySens_1(5);
GButton mySens_2(6);
GButton mySens_3(7);
GButton mySens_4(8);
GButton mySens_5(9);
GButton mySens_6(10);


DHT dht(DHT_PIN, DHT_TYPE);




int sound_ii = 1;


uint8_t _str_num = 1;
uint8_t _str_num_max = 3;
bool initil = 0;
bool muted = 0;
bool signaliz = 0;
bool flag_warning = 0;
bool is_client = 0;
byte byte_rel = 0;


int error_tupe; // 0-нет / 1-DHT /
byte warning = 0; // 0-всё впорядке / 1-пожар / 2-потоп / 3-ограбление
int higr;
float temp;
int time_move;

int sec_start = 0, min_start = 0, hour_start = 0;
int sec = BUILD_SEC, min_ = BUILD_MIN, hour = BUILD_HOUR;

uint32_t Timer_time;
uint32_t Timer_time_move;
uint32_t Timer_send_data;



uint32_t Timer_sound;
uint32_t Timer_warn;
uint32_t Timer_mute;
uint16_t correct_time;

void(* resetFunc) (void) = 0;

void setup() {
  dht.begin();

  Serial.begin(1000000);
  Serial.setTimeout(50);

  delay(1);

  // myButt2.setTimeout(1000);

  mySens_1.setType(LOW_PULL);
  mySens_2.setType(LOW_PULL);
  mySens_3.setType(LOW_PULL);
  mySens_4.setType(LOW_PULL);
  mySens_5.setType(LOW_PULL);
  mySens_6.setType(LOW_PULL);

  pinMode(BAZER_PIN, OUTPUT);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);


  sec += correct_time;
}


void loop() {
  rele_tick();

  if (IS_DEBUG) {
    Serial.print("Client: "); Serial.print(is_client); Serial.print("      warning: "); Serial.print(warning); Serial.print(" ERORR: "); Serial.print(error_tupe); Serial.print("      Temp: ");
    Serial.print(temp); Serial.print(" Hum: "); Serial.print(higr); Serial.print("      Time: "); Serial.print(hour); Serial.print(":"); Serial.print(min_); Serial.print(":"); Serial.println(sec);
  }

  //warning = 0;

  if (IS_WATHER) if (!digitalRead(WATHER_PIN)) {
      warning = 2;
      flag_warning = 1;
    }
  if (IS_GAZ and !flag_warning and (min_start > 5 or hour_start > 0)) if (!digitalRead(GAZ_PIN)) {
      warning = 1;
      flag_warning = 1;
      Timer_warn = millis();
    }

  if (IS_MOVE and digitalRead(MOVE_PIN)) {
    time_move = 0;
    if (signaliz) {
      warning = 3;
      flag_warning = 1;
      Timer_warn = millis();
    }
  }

  delay(1);

  if (flag_warning and !muted) {
    if (warning == 1) {
      sound(2);
    } else if (warning == 2) {
      sound(1);
    } else if (warning == 3) {
      sound(3);
    } else if (warning == 0) {
      tone(BAZER_PIN, 0 , 10);
    }
  } else tone(BAZER_PIN, 0 , 10);



  if (Serial.available() > 1) {
    char Key = Serial.read();
    char key = Serial.read();
    int val = Serial.parseInt();

    switch (Key) {
      case 't':
        if (key == 's') sec = val;
        if (key == 'm') min_ = val;
        if (key == 'h') hour = val;
        break;
      case 'M':
        if (key == 'c')tone(BAZER_PIN, 1000, 1500);
        if (key == 'e'){
          if (val == 0){
            warning = 0;
            flag_warning = 0;
            Timer_warn = millis();
          }else{ 
            warning = val;
            flag_warning = 1;
            Timer_warn = millis();
          }
        }
        if (key == 'u')
          if (val == 0)muted = 0;
          else {
            muted = 1;
            Timer_mute = millis();
          }
        break;
      case 'u':
        if (key == 'd') compil();
        break;
      case 'S':
        if (key == 'i') signaliz = val;
        break;
      case 'T':
        if (key == 'u')
          if (val == 0)is_client = 0;
          else is_client = 1;
        if (key == 'l')if (val > 0 and val <= _str_num_max) _str_num = val;
        if (key == 'I')initil = 1;
        if (IS_DEBUG)Serial.println("\nИзменён режим пользования\n");
        break;
      case 'R':
        if (key == 'R') resetFunc();
        if (key == '1') {
          set_rele(0, val);
          rele1.is_on = val;
        }
        if (key == '2') {
          set_rele(1, val);
          rele2.is_on = val;
        }
        if (key == '3') {
          set_rele(2, val);
          rele3.is_on = val;
        }
        if (key == '4') {
          set_rele(3, val);
          rele4.is_on = val;
        }
        if (key == '5') {
          set_rele(4, val);
          rele5.is_on = val;
        }
        if (key == '6') {
          set_rele(5, val);
          rele6.is_on = val;
        }
        if (key == '7') {
          set_rele(6, val);
          rele7.is_on = val;
        }
        if (key == '8') {
          set_rele(7, val);
          rele8.is_on = val;
        }
        break;

    }
  }


  if (millis() - Timer_time_move > 60000) {
    time_move += 1;
    Timer_time_move = millis();
  }

  // таймер отсчёта времени
  if (millis() - Timer_time > 1000) {

    Timer_time = millis();
    sec++;

    if (sec > 59) {
      sec = 0;
      min_++;
      if (min_ > 59) {
        min_ = 0;
        hour++;
        if (hour > 23) {
          hour = 0;
        }
      }
    }

    sec_start++;
    if (sec_start > 59) {
      sec_start = 0;
      min_start++;
      if (min_start > 59) {
        min_start = 0;
        hour_start++;
      }
    }
  }

  // таймер отправки данных
  if (millis() - Timer_send_data > TIME_AUTO_DATA * 1000) {
    Timer_send_data = millis();
    compil();
  }

  // таймер авто выключения сигнализации
  if (millis() - Timer_warn > 5 * 60000 and flag_warning) {
    flag_warning = 0;
  }

  // таймер авто выключения беззвучного режима сигнализации
  if (millis() - Timer_mute > 5 * 60000 and muted) {
    muted = 0;
  }

  error_tupe = 0;

  temp = dht.readTemperature(); //Измеряем температуру
  higr = dht.readHumidity(); //Измеряем влажность
  if (isnan(higr) || isnan(temp)) {
    error_tupe = 1;
  }


}


void rele_tick() {
  mySens_1.tick();
  mySens_2.tick();
  mySens_3.tick();
  mySens_4.tick();
  mySens_5.tick();
  mySens_6.tick();

  if (mySens_1.isClick()) SetRele(1);
  if (mySens_2.isClick()) SetRele(2);
  if (mySens_3.isClick()) SetRele(3);
  if (mySens_4.isClick()) SetRele(4);
  if (mySens_5.isClick()) SetRele(5);
  if (mySens_6.isClick()) SetRele(6);


}

void SetRele(uint8_t addres) {
  switch (addres) {
    case 1:
      rele1.is_on = !rele1.is_on;
      set_rele(0, rele1.is_on);
      break;
    case 2:
      rele2.is_on = !rele2.is_on;
      set_rele(1, rele2.is_on);
      break;
    case 3:
      rele3.is_on = !rele3.is_on;
      set_rele(2, rele3.is_on);
      break;
    case 4:
      rele4.is_on = !rele4.is_on;
      set_rele(3, rele4.is_on);
      break;
    case 5:
      rele5.is_on = !rele5.is_on;
      set_rele(4, rele5.is_on);
      break;
    case 6:
      rele6.is_on = !rele6.is_on;
      set_rele(5, rele6.is_on);
      break;
  }
  compil();

}



void start_draw() {
  correct_time = millis();
  tone(BAZER_PIN, 1000 , 100);
  delay(2000);
  tone(BAZER_PIN, 1000 , 100);
  delay(600);
  tone(BAZER_PIN, 1000 , 100);
}


void compil() {
  String mes = "";
  if (IS_MOVE) {
    mes = "CiSHP-1m|t3|" + String(error_tupe) + "|" + String(warning) + "|" + String(temp) + "|" + String(higr) + "|" + String(is_client) + "|" + String(hour_start) + ":" + String(min_start) + ":" + String(sec_start) + "|" + String(rele1.is_on) + "," + String(rele2.is_on) + "," + String(rele3.is_on) + "," + String(rele4.is_on) + "," + String(rele5.is_on) + "," + String(rele6.is_on) + "," + String(rele7.is_on) + "," + String(rele8.is_on) + "|" +String(time_move);
    Serial.println(mes);
  }
  if (!IS_MOVE) {
    mes = "CiSHP-1m|t4|" + String(error_tupe) + "|" + String(warning) + "|" + String(temp) + "|" + String(higr) + "|" + String(is_client) + "|" + String(hour_start) + ":" + String(min_start) + ":" + String(sec_start) + "|" + String(rele1.is_on) + "," + String(rele2.is_on) + "," + String(rele3.is_on) + "," + String(rele4.is_on) + "," + String(rele5.is_on) + "," + String(rele6.is_on) + "," + String(rele7.is_on) + "," + String(rele8.is_on) + "|-1";
    Serial.println(mes);
  }
}


void sound(byte type) {
  switch (type) {
    case 1:
      if (millis() - Timer_sound > 200) {
        Timer_sound = millis();
        if (sound_ii == 1) {
          sound_ii++;
          tone(BAZER_PIN, 700);
        }
        else if (sound_ii == 2) {
          sound_ii++;
          tone(BAZER_PIN, 1000);
        }
        else if (sound_ii == 3) {
          tone(BAZER_PIN, 1300);
          sound_ii++;
        }
        else if (sound_ii == 4) {
          tone(BAZER_PIN, 1500);
          sound_ii++;
        }
        else if (sound_ii == 5) {
          tone(BAZER_PIN, 0);
          sound_ii = 1;
        }
      }
      break;

    case 2:
      if (millis() - Timer_sound > 500) {
        Timer_sound = millis();
        if (sound_ii == 1) {
          sound_ii++;
          tone(BAZER_PIN, 0);
        }
        else if (sound_ii == 2) {
          sound_ii++;
          tone(BAZER_PIN, 2000);
        }
        else if (sound_ii == 3) {
          tone(BAZER_PIN, 0);
          sound_ii++;
        }
        else if (sound_ii == 4) {
          tone(BAZER_PIN, 2000);
          sound_ii++;
        }
        else if (sound_ii == 5) {
          tone(BAZER_PIN, 0);
          sound_ii = 1;
        }
      }
      break;

    case 3:
      if (millis() - Timer_sound > 500) {
        Timer_sound = millis();
        if (sound_ii == 1) {
          sound_ii++;
          tone(BAZER_PIN, 3000);
        }
        else if (sound_ii == 2) {
          sound_ii = 1;
          tone(BAZER_PIN, 0);

        }
      }
      break;
    case 0:
      analogWrite(BAZER_PIN, 0);
      break;
  }

}

void set_rele(int val_, bool bit_) {
  bitWrite(byte_rel, val_, bit_);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, byte_rel);
  digitalWrite(latchPin, HIGH);

}
