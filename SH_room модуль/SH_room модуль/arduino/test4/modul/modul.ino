/*
  ░██████╗███╗░░░███╗░█████╗░██████╗░████████╗    ██╗░░██╗░█████╗░██╗░░░██╗░██████╗███████╗
  ██╔════╝████╗░████║██╔══██╗██╔══██╗╚══██╔══╝    ██║░░██║██╔══██╗██║░░░██║██╔════╝██╔════╝
  ╚█████╗░██╔████╔██║███████║██████╔╝░░░██║░░░    ███████║██║░░██║██║░░░██║╚█████╗░█████╗░░
  ░╚═══██╗██║╚██╔╝██║██╔══██║██╔══██╗░░░██║░░░    ██╔══██║██║░░██║██║░░░██║░╚═══██╗██╔══╝░░
  ██████╔╝██║░╚═╝░██║██║░░██║██║░░██║░░░██║░░░    ██║░░██║╚█████╔╝╚██████╔╝██████╔╝███████╗
  ╚═════╝░╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░    ╚═╝░░╚═╝░╚════╝░░╚═════╝░╚═════╝░╚══════╝

********************************************************************* Colden I ******************************************************************
*/

#include "DHT.h"
#include "GyverButton.h"
#include <GyverOLED.h>
#include <microLED.h>

//**********SETTINGS**********

#define DHT_TYPE                     DHT11    // тип датчика DHT
#define TIME_AUTO_DATA               1        // время авто отправки данных (в секундах)
#define IS_AUTO_OFF_DISPLAY          0        // включить/выключить авто погашение экрана (1/0)
#define AUTO_OFF_DISPLAY_TIME        15       // авто погашение экрана время (в секундах)
#define AUTO_DRAW_DISPLAY            5        // авто обновление дисплея (в секундах)
#define IS_WATHER                    0        // подключён ли датчик утечки (1/0)
#define IS_MOVE                      1        // подключён ли датчик движения (1/0)
#define IS_GAZ                       1        // подключён ли датчик газа (1/0)
#define IS_DEBUG                     0        // режим отладки (1/0)
#define IS_ADPBR                     1        // адаптитвная ярковсть (1/0)


#define DHT_PIN                      2        // пин подключения DHT
#define STRIP_PIN                    3        // пин ленты
#define BRI_PIN                      A3       // пин датчика освещения
#define BAZER_PIN                    4        // пин зумера

#define WATHER_PIN                   0        // пин датчика утечки воды
#define GAZ_PIN                      A2       // пин датчика газа
#define MOVE_PIN                     A1       // пин датчика движения

#define latchPin                     12       // пин реле
#define clockPin                     11       // пин реле
#define dataPin                      13       // пин реле



struct Rele_st{
  bool is_on = 0;
};

Rele_st rele1, rele2, rele3, rele4, rele5, rele6, rele7, rele8;

// сенсоры
GButton mySens_1(10);
GButton mySens_2(9);
GButton mySens_3(10);
GButton mySens_4(10);
GButton mySens_5(10);
GButton mySens_6(10);


microLED<1, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_GRB, CLI_AVER> strip;
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
DHT dht(DHT_PIN, DHT_TYPE);

GButton myButt1;
GButton myButt2;
GButton myButt3;

const static uint8_t icons_8x8[][8] PROGMEM = {
  {0x80, 0xc0, 0xe6, 0xef, 0xef, 0xe6, 0xc0, 0x80}, //2 user
  {0x7e, 0x81, 0x95, 0xa1, 0xa1, 0x95, 0x81, 0x7e}, //5 ylibka
  {0xe0, 0xfc, 0xfe, 0xa3, 0xfe, 0xfc, 0xe0, 0x00}, //24 warning
  {0x70, 0x88, 0x84, 0x84, 0xa4, 0x98, 0x90, 0x60}, //59 cloud
  {0xc0, 0xe0, 0x70, 0x3e, 0x19, 0x11, 0x10, 0x0c}, //71 tool
  {0x3f, 0xa1, 0xa1, 0xe1, 0xe1, 0xa1, 0xa1, 0x3f}, //116 monitor, display

};

bool led_blinc_ = 1;
int led_bring = 100;
int sound_ii = 1;
int Bring_ = 255;
int error_tupe; // 0-нет / 1-DHT /
bool is_client = 0;
byte byte_rel = 0;

bool is_wt_on;

bool signaliz = 0;
bool flag_warning = 0;

byte warning; // 0-всё впорядке / 1-пожар / 2-потоп / 3-ограбление

int higr;
float temp;

int time_move;


int sec_start = 0, min_start = 0, hour_start = 0;
int sec, min_, hour;
uint32_t Timer_time;
uint32_t Timer_time_move;
uint32_t Timer_send_data;
uint32_t Timer_auto_off_display;
uint32_t Timer_auto_draw;
uint32_t Timer_led_blink_;
uint32_t Timer_sound;
uint32_t Timer_warn;

uint8_t _str_num = 1;
uint8_t _str_num_max = 3;




void setup() {
  dht.begin();
  oled.init();
  Wire.setClock(400000L);
  Serial.begin(9600);
  Serial.setTimeout(50);

  strip.setBrightness(255);
  strip.clear();
  strip.show();
  delay(1);

  // myButt2.setTimeout(1000);
  myButt1.setType(LOW_PULL);
  myButt2.setType(LOW_PULL);
  myButt3.setType(LOW_PULL);
  oled.setContrast(255);

  mySens_1.setType(LOW_PULL);
  mySens_2.setType(LOW_PULL);
  mySens_3.setType(LOW_PULL);
  mySens_4.setType(LOW_PULL);
  mySens_5.setType(LOW_PULL);
  mySens_6.setType(LOW_PULL);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  //start_draw();
  oled.clear();
  draw_display();

  pinMode(BAZER_PIN, OUTPUT);

}


void loop() {
  rele_tick();
  
  if (IS_DEBUG) {
    Serial.print("Client: "); Serial.print(is_client); Serial.print("      warning: "); Serial.print(warning); Serial.print(" ERORR: "); Serial.print(error_tupe); Serial.print("      Temp: ");
    Serial.print(temp); Serial.print(" Hum: "); Serial.print(higr); Serial.print("      Time: "); Serial.print(hour); Serial.print(":"); Serial.print(min_); Serial.print(":"); Serial.println(sec);
  }

  warning = 0;
  
  if (IS_WATHER and !flag_warning) if (!digitalRead(WATHER_PIN)) {
    warning = 2;
  }
  if (IS_GAZ and (min_start > 5 or hour_start > 0) and !flag_warning) if (!digitalRead(GAZ_PIN)){
    warning = 1;
  }

  if (IS_MOVE and digitalRead(MOVE_PIN)){
    time_move = 0;
    if (signaliz) warning = 3;
  }
  
  delay(1);


  if (warning == 1) {
    sound(2);
    draw_display();
    //tone(BAZER_PIN, 2000, 10);
  } else if (warning == 2) {
    sound(1);
    draw_display();
    //tone(BAZER_PIN, 1000, 10);
  } else if (warning == 3) {
    sound(3);
    draw_display();
    //tone(BAZER_PIN, 400, 10);
  } else if (warning == 0) {
    //sound(0);
    tone(BAZER_PIN, 0 , 10);

  }


  int analog = analogRead(A0);
  //Serial.println(analog);
  myButt1.tick(analog < 330 && analog > 290);
  myButt3.tick(analog < 630 && analog > 590);
  myButt2.tick(analog < 1030 && analog > 920);

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
        if (key == 'e') warning = val;
        if (key == 'u')
          if (val == 0)flag_warning = 0;
          else {
            flag_warning = 1;
            Timer_warn = millis();
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
        
        if (IS_DEBUG)Serial.println("\nИзменён режим пользования\n");
        oled.clear();
        draw_display();
        break;
      case 'R':
        if (key == '1'){
          set_rele(0, val);
          rele1.is_on = val;
        }
        if (key == '2'){
          set_rele(1, val);
          rele2.is_on = val;
        }
        if (key == '3'){
          set_rele(2, val);
          rele3.is_on = val;
        }
        if (key == '4'){
          set_rele(3, val);
          rele4.is_on = val;
        }
        if (key == '5'){
          set_rele(4, val);
          rele5.is_on = val;
        }
        if (key == '6'){
          set_rele(5, val);
          rele6.is_on = val;
        }
        if (key == '7'){
          set_rele(6, val);
          rele7.is_on = val;
        }
        if (key == '8'){
          set_rele(7, val);
          rele8.is_on = val;
        }
        break;

    }
    update();
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
      oled.setScale(3);
      oled.setCursor(18, 2);
      oled.print("        ");
      draw_display();
      if (min_ > 59) {
        min_ = 0;
        hour++;
        if (hour > 23) {
          hour = 0;
        }
      }
    }

    sec_start++;
    if (sec_start > 59){
      sec_start=0;
      min_start++;
      if(min_start > 59){
        min_start=0;
        hour_start++;
      }
    }
  }

  // таймер отправки данных
  if (millis() - Timer_send_data > TIME_AUTO_DATA * 1000) {
    Timer_send_data = millis();
    compil();
  }

  // таймер авто выключения диспея
  if (millis() - Timer_auto_off_display > AUTO_OFF_DISPLAY_TIME * 1000 and IS_AUTO_OFF_DISPLAY) {
    oled.setPower(false);
  }

  // таймер авто обновление дисплея
  if (millis() - Timer_auto_draw > AUTO_DRAW_DISPLAY * 1000 and !IS_AUTO_OFF_DISPLAY) {
    Timer_auto_draw = millis();
    update();
  }


  error_tupe = 0;

  temp = dht.readTemperature(); //Измеряем температуру
  higr = dht.readHumidity(); //Измеряем влажность
  if (isnan(higr) || isnan(temp)) {
    error_tupe = 1;
  }

  int __fgh = 100;
  if (IS_ADPBR)  __fgh = map(analogRead(BRI_PIN), 0, 1023, 50, 255);
  else  __fgh = 255;


  oled.setContrast(__fgh);
  if (error_tupe != 0) {
    led_draw(250, 0, 0, __fgh);
  } else {
    if (is_client) led_draw(0, 255, 0, __fgh);
    else led_draw(0, 0, 250, __fgh);
  }



  if (myButt2.isHolded()) 
    if (warning != 0){
    flag_warning = 1;
    signaliz = 0;
    Timer_warn = millis();
    delay(300);
  }else{
    is_client = !is_client;
    oled.clear();
    draw_display();
    delay(300);
  }

  if (myButt1.isHolded() and !is_client)
    if (warning != 0){
    flag_warning = 1;
    signaliz = 0;
    Timer_warn = millis();
    delay(300);
  }else{
    oled.clear();
    if (_str_num == 1) _str_num = _str_num_max+1;
    if (_str_num > 1) _str_num--;  
    draw_display();
    delay(300);
  }
  
  if (myButt3.isHolded() and !is_client)
    if (warning != 0){
    flag_warning = 1;
    signaliz = 0;
    Timer_warn = millis();
    delay(300);
  }else{
    oled.clear();
    if (_str_num == _str_num_max) _str_num = 0;
    if (_str_num < _str_num_max) _str_num++;
    draw_display();
    delay(300);
  }




  if (millis() - Timer_warn > 5 * 60000 and flag_warning) {
    flag_warning = 0;
  }


}


void rele_tick(){
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

void SetRele(uint8_t addres){
  switch(addres){
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
  draw_display();
}

void update() {
  draw_display();     // отрисовка на дисплей
  // compil();
}

void draw_display() {
  //oled.clear();

  oled.setScale(1);
  if (IS_AUTO_OFF_DISPLAY)
    Timer_auto_off_display = millis();
  oled.setPower(true);
  oled.home();

  if (is_client) {
    oled.rect(0, 0, 16, 8, 0);
    oled.setCursor(1 << 2, 0);
    drawIcon8x8(0);
  } else {
    oled.setCursor(0 << 2, 0);
    drawIcon8x8(5);
    oled.setCursor(2 << 2, 0);
    drawIcon8x8(4);
  }

  if (error_tupe == 0) {
    oled.rect(32, 0, 48, 8, 0);
  } else if (error_tupe == 1) {
    oled.setCursor(8 << 2, 0);
    drawIcon8x8(2);
    oled.setCursor(10 << 2, 0);
    drawIcon8x8(3);
  } else {
    oled.setCursor(8 << 2, 0);
    drawIcon8x8(2);
  }

  if (warning == 1) {
    oled.setCursor(29 << 2, 0);
    drawIcon8x8(2);
  } else if (warning == 2) {
    oled.setCursor(29 << 2, 0);
    drawIcon8x8(2);
  } else if (warning == 3) {
    oled.setCursor(29 << 2, 0);
    drawIcon8x8(2);
  } else if (warning == 0) {
    oled.setCursor(29 << 2, 0);
    drawIcon8x8(1);
  }

  if (is_client) {
    // вывод время
    oled.setScale(3);
    String ttt = String(hour) + ":";
    if (min_ < 10) ttt += "0" + String(min_);
    else ttt += String(min_);
    oled.setCursor(18, 2); oled.print(ttt);

    // вывод температуры и  влажности
    oled.setScale(2);
    int temp__ = temp;
    String tth;
    if (error_tupe == 1) tth = "DHT  ERROR!";
    else tth = " " + String(temp__) + "`C  " + String(higr) + "%";
    oled.setCursor(0, 6); oled.print("           "); oled.setCursor(0, 6); oled.print(tth);



  }
  else {
      switch(_str_num){
        case 1:
          oled.setScale(1);
          oled.setCursor(0, 2); oled.print("1|       Relay   ");
          oled.fastLineH(26, 26, 122, 1);
          oled.setCursor(0, 4); oled.print(" #:  1 2 3 4 5 6 7 8");
          oled.fastLineH(42, 26, 122, 1);
          oled.setCursor(0, 6); oled.print(" S:  " + String(rele1.is_on) + " " + String(rele2.is_on) + " " + String(rele3.is_on) + " " + String(rele4.is_on) + " " + String(rele5.is_on) + " " + String(rele6.is_on) + " " + String(rele7.is_on) + " " + String(rele8.is_on) + " ");
          oled.fastLineH(58, 26, 122, 1);
      
          oled.fastLineV(26, 26, 58);
          oled.fastLineV(38, 26, 58);
          oled.fastLineV(50, 26, 58);
          oled.fastLineV(62, 26, 58);
          oled.fastLineV(74, 26, 58);
          oled.fastLineV(86, 26, 58);
          oled.fastLineV(98, 26, 58);
          oled.fastLineV(110, 26, 58);
          oled.fastLineV(122, 26, 58);
          break;
        case 2:
          oled.setScale(1);
          oled.setCursor(0, 2); oled.print("2|      Sensors   ");
          oled.fastLineH(26, 0, 127, 1);
          oled.setCursor(0, 4); oled.print("Motino        -     " + String(IS_MOVE));
          oled.setCursor(0, 5); oled.print("Water leak    -     " + String(IS_WATHER));
          oled.setCursor(0, 6); oled.print("Gas           -     " + String(IS_GAZ));
          break;
        case 3:
          oled.setScale(1);
          int temp__ = temp;
          oled.setCursor(0, 2); oled.print("3|      Data   ");
          oled.setCursor(0, 3); oled.print("DHT: " + String(temp__) + "`C    " + String(higr) + "%");     
          oled.setCursor(0, 4); if (flag_warning) oled.print("Event: " + String(warning) + " - !MUTED!"); else oled.print("Event: " + String(warning) + " -          ");
          oled.setCursor(0, 5); oled.print("Error type: " + String(error_tupe));
          oled.setCursor(0, 6); oled.print("Time move: " + String(time_move) + " min");
          oled.setCursor(0, 7); oled.print("Start t: " + String(hour_start) + ":" + String(min_start) + ":" + String(sec_start));
          break;
    }
  }
  
  oled.fastLineH(11, 0, 127, 1);

}

void start_draw() {
  led_draw(random(0, 100), random(10, 200), random(20, 255), 255);
  oled.clear();
  oled.roundRect(5, 5, 122, 58, 1);
  oled.update();
  delay(200);

  oled.invertText(1);

  oled.setScale(3);
  oled.setCursor(15, 2);
  oled.print("House");
  oled.setScale(2);
  oled.setCursor(55, 1);
  oled.print("smart");

  oled.setScale(1);
  oled.setCursor(40, 6);
  oled.print("Colden I");

  oled.invertText(0);
  oled.update();
  delay(1000);
  led_draw(random(0, 100), random(10, 200), random(20, 255), 255);
  // пишалка

  for (int i = 0; i < 1200; i++) {
    led_draw(random(0, 100), random(10, 200), random(20, 255), 255);
    oled.dot(random(0, 127), random(0, 63), random(0, 1));
    delay(1);
  }
  delay(100);
  led_draw(random(0, 255), random(0, 255), random(0, 255), 255);
  oled.invertDisplay(1);
  delay(300);
  led_draw(random(0, 255), random(0, 255), random(0, 255), 255);
  oled.invertDisplay(0);
  delay(300);
  led_draw(random(0, 255), random(0, 255), random(0, 255), 255);
  oled.invertDisplay(1);
  delay(300);
  led_draw(random(0, 255), random(0, 255), random(0, 255), 255);
  oled.invertDisplay(0);
  delay(300);
  for (int i = 0; i < 63; i++) {
    for (int n = 0; n < 127; n++) {
      oled.dot(n, i, 0);
      delay(0.04);
    }
  }
  delay(300);

  oled.clear();


  oled.setScale(1);
  oled.update();
}


void led_blink(int R, int G, int B, int speed_, int speed__, int min_, int max_) {
  strip.clear();
  strip.set(0, mRGB(R, G, B));
  if (millis() - Timer_led_blink_ > speed_) {
    Timer_led_blink_ = millis();
    draw_display();

    if (led_blinc_) {
      led_bring += speed__;
      strip.setBrightness(led_bring);
      if (led_bring >= Bring_) led_blinc_ = 0;
    }
    else {
      led_bring -= speed__;
      strip.setBrightness(led_bring);
      if (led_bring <= min_) led_blinc_ = 1;
    }

  }
  strip.show();

}

void led_draw(int R, int G, int B, int led_bring_) {
  strip.clear();
  strip.setBrightness(led_bring_);
  strip.set(0, mRGB(R, G, B));
  strip.show();
  delay(1);
}


void compil() {


  //    "/" + String(xData.) +
  /*
    String mes = "data|CiSHP-1m|tupe|" + String(xData.fire) +
                                   "|" + String(xData.water) +
                                   "|" + String(xData.robber) +
                                   "|" + String(xData.higr) +
                                   "|" + String(xData.error_tupe) +
                                   "|" + String(xData.temp) +
                                   "|" + String(xData.time_move);


    Serial.println(mes);
  */


}

void drawIcon8x8(byte index) {
  size_t s = sizeof icons_8x8[index];//можна так, а можна просто 8
  for (unsigned int i = 0; i < s; i++) {
    oled.drawByte(pgm_read_byte(&(icons_8x8[index][i])));
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
          led_draw(255, 0, 0, 255);
        }
        else if (sound_ii == 2) {
          sound_ii++;
          tone(BAZER_PIN, 1000);
          led_draw(255, 0, 0, 255);
        }
        else if (sound_ii == 3) {
          tone(BAZER_PIN, 1300);
          sound_ii++;
          led_draw(255, 0, 0, 255);
        }
        else if (sound_ii == 4) {
          tone(BAZER_PIN, 1500);
          sound_ii++;
          led_draw(255, 0, 0, 255);
        }
        else if (sound_ii == 5) {
          tone(BAZER_PIN, 0);
          sound_ii = 1;
          led_draw(255, 0, 0, 255);
        }
      }
      break;

    case 2:
      if (millis() - Timer_sound > 500) {
        Timer_sound = millis();
        if (sound_ii == 1) {
          sound_ii++;
          tone(BAZER_PIN, 0);
          led_draw(255, 0, 0, 255);
        }
        else if (sound_ii == 2) {
          sound_ii++;
          tone(BAZER_PIN, 2000);
          led_draw(255, 0, 0, 255);
        }
        else if (sound_ii == 3) {
          tone(BAZER_PIN, 0);
          sound_ii++;
          led_draw(255, 0, 0, 255);
        }
        else if (sound_ii == 4) {
          tone(BAZER_PIN, 2000);
          sound_ii++;
          led_draw(255, 0, 0, 255);
        }
        else if (sound_ii == 5) {
          tone(BAZER_PIN, 0);
          sound_ii = 1;
          led_draw(255, 0, 0, 255);
        }
      }
      break;

    case 3:
      if (millis() - Timer_sound > 500) {
        Timer_sound = millis();
        if (sound_ii == 1) {
          sound_ii++;
          tone(BAZER_PIN, 3000);
          led_draw(255, 0, 0, 255);
        }
        else if (sound_ii == 2) {
          sound_ii = 1;
          tone(BAZER_PIN, 0);
          led_draw(255, 0, 0, 255);

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
