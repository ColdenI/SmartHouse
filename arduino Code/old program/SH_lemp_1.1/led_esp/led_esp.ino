#include "FastLED.h"          // библиотека для работы с лентой
byte ballColors[3][3] = {
  {0xff, 0, 0},
  {0xff, 0xff, 0xff},
  {0   , 0   , 0xff}
};
#define LED_COUNT 30         // число светодиодов в кольце/ленте
#define LED_DT 6             // пин, куда подключен DIN ленты

int max_bright = 255;          // максимальная яркость (0 - 255)
boolean adapt_light = 0;       // адаптивная подсветка (1 - включить, 0 - выключить)

int ledMode=random(1, 15);
int comand;

int briggggg=1;


// ---------------СЛУЖЕБНЫЕ ПЕРЕМЕННЫЕ-----------------
int BOTTOM_INDEX = 0;        // светодиод начала отсчёта
int TOP_INDEX = int(LED_COUNT / 2);
int EVENODD = LED_COUNT % 2;
struct CRGB leds[LED_COUNT];
int ledsX[LED_COUNT][3];     //-ARRAY FOR COPYING WHATS IN THE LED STRIP CURRENTLY (FOR CELL-AUTOMATA, MARCH, ETC)

int thisdelay = 20;          //-FX LOOPS DELAY VAR
int thisstep = 10;           //-FX LOOPS DELAY VAR
int thishue = 0;             //-FX LOOPS DELAY VAR
int thissat = 255;           //-FX LOOPS DELAY VAR

int thisindex = 0;
int thisRED = 0;
int thisGRN = 0;
int thisBLU = 0;

int idex = 0;                //-LED INDEX (0 to LED_COUNT-1
int ihue = 0;                //-HUE (0-255)
int ibright = 0;             //-BRIGHTNESS (0-255)
int isat = 0;                //-SATURATION (0-255)
int bouncedirection = 0;     //-SWITCH FOR COLOR BOUNCE (0-1)
float tcount = 0.0;          //-INC VAR FOR SIN LOOPS
int lcount = 0;              //-ANOTHER COUNTING VAR

volatile uint32_t btnTimer;
volatile byte modeCounter;
volatile boolean changeFlag;
// ---------------СЛУЖЕБНЫЕ ПЕРЕМЕННЫЕ-----------------


void setup() {
pinMode(11, OUTPUT);
pinMode(10, OUTPUT);
pinMode(9, OUTPUT);

  
  LEDS.setBrightness(255);  // ограничить максимальную яркость 1-255
LEDS.addLeds<WS2811, LED_DT, GRB>(leds, LED_COUNT);  // настрйоки для нашей ленты (ленты на WS2811, WS2812, WS2812B)

Serial.begin(9600);

  one_color_all(0, 0, 0);          // погасить все светодиоды
  LEDS.show();



}
int old_com = 0;
void loop() {
    if (Serial.available() > 0) {     // если что то прислали
      old_com=ledMode;
      ledMode = Serial.parseInt();    // парсим в тип данных int
      change_mode(ledMode);           // меняем режим через change_mode (там для каждого режима стоят цвета и задержки)
    }

        switch (ledMode) {
    case 999: break;


    
    // пазуа
    case  0: one_color_all(0, 0, 0);LEDS.show();break;            // плавная смена цветов всей ленты
    case  2: rainbow_fade(); break;            // плавная смена цветов всей ленты
    case  3: rainbow_loop(); break;            // крутящаяся радуга
    case  4: random_burst(); break;            // случайная смена цветов
    case  5: color_bounce(); break;            // бегающий светодиод
    case  6: color_bounceFADE(); break;        // бегающий паровозик светодиодов
    case  7: ems_lightsONE(); break;           // вращаются красный и синий
    case  8: ems_lightsALL(); break;           // вращается половина красных и половина синих

    case 12: fade_vertical(); break;           // плавная смена яркости по вертикали (для кольца)
    case 13: rule30(); break;                  // безумие красных светодиодов
    case 14: random_march(); break;            // безумие случайных цветов
    case 15: rwb_march(); break;               // белый синий красный бегут по кругу (ПАТРИОТИЗМ!)
    case 16: radiation(); break;               // пульсирует значок радиации

    case 18: white_temps(); break;             // бело синий градиент (?)
    case 19: sin_bright_wave(); break;         // тоже хрень какая то
    case 20: pop_horizontal(); break;          // красные вспышки спускаются вниз
    case 21: quad_bright_curve(); break;       // полумесяц
    case 22: flame(); break;                   // эффект пламени
    case 23: rainbow_vertical(); break;        // радуга в вертикаьной плоскости (кольцо)
    case 24: pacman(); break;                  // пакман
    case 25: random_color_pop(); break;        // безумие случайных вспышек
    case 26: ems_lightsSTROBE(); break;        // полицейская мигалка
    case 27: rgb_propeller(); break;           // RGB пропеллер
    case 28: kitt(); break;                    // случайные вспышки красного в вертикаьной плоскости
    case 29: matrix(); break;                  // зелёненькие бегают по кругу случайно
    case 30: new_rainbow_loop(); break;        // крутая плавная вращающаяся радуга
    case 17: colorWipe(0x00, 0xff, 0x00, thisdelay);
      colorWipe(0x00, 0x00, 0x00, thisdelay); break;                                // плавное заполнение цветом
    case 11: CylonBounce(0xff, 0, 0, 4, 10, thisdelay); break;                      // бегающие светодиоды
    case 10: Fire(55, 120, thisdelay); break;                                       // линейный огонь
    case 9: NewKITT(0xff, 0, 0, 8, 10, thisdelay); break;                          // беготня секторов круга (не работает)
 
                          // случайные разноцветные включения (1 - танцуют все, 0 - случайный 1 диод)
    case 1: RunningLights(0xff, 0xff, 0x00, thisdelay); break;                     // бегущие огни


    case 888: demo_modeA(); break;             // длинное демо
    case 889: demo_modeB(); break;             // короткое демо
  }

}

void change_mode(int newmode) {
  thissat = 255;
  my_RGB__(0, 0, 0);
  switch (newmode) {

    case 201: LEDS.setBrightness(51); briggggg = 5; change_mode(old_com);break;
    case 202: LEDS.setBrightness(100);briggggg = 4; change_mode(old_com);break;
    case 203: LEDS.setBrightness(150);briggggg = 3;change_mode(old_com);break;
    case 204: LEDS.setBrightness(200);briggggg = 2;change_mode(old_com); break;
    case 205: LEDS.setBrightness(255); briggggg = 1;change_mode(old_com);break;
    
    case 0: one_color_all(0, 0, 0); LEDS.show(); break; //---ALL OFF
    case 101: one_color_all(255, 255, 255); my_RGB__(255, 255, 255);LEDS.show(); break; //---ALL ON
    case 2: thisdelay = 60; break;                      //---STRIP RAINBOW FADE
    case 3: thisdelay = 20; thisstep = 10; break;       //---RAINBOW LOOP
    case 4: thisdelay = 20; break;                      //---RANDOM BURST
    case 5: thisdelay = 20; thishue = random(1, 252); break;         //---CYLON v1
    case 6: thisdelay = 80; thishue = random(1, 252); break;         //---CYLON v2
    case 7: thisdelay = 40; thishue = 0; break;         //---POLICE LIGHTS SINGLE
    case 8: thisdelay = 40; thishue = 0; break;         //---POLICE LIGHTS SOLID

    case 12: thisdelay = 60; thishue = random(1, 252); break;      //---VERTICAL SOMETHING
    case 13: thisdelay = 100; break;                    //---CELL AUTO - RULE 30 (RED)
    case 14: thisdelay = 80; break;                     //---MARCH RANDOM COLORS
    case 15: thisdelay = 80; break;                     //---MARCH RWB COLORS
    case 16: thisdelay = 60; thishue = 95; break;       //---RADIATION SYMBOL
    //---PLACEHOLDER FOR COLOR LOOP VAR DELAY VARS
    case 19: thisdelay = 35; thishue = 180; break;      //---SIN WAVE BRIGHTNESS
    case 20: thisdelay = 100; thishue = random(1, 252); break;       //---POP LEFT/RIGHT
    case 21: thisdelay = 100; thishue = 180; break;     //---QUADRATIC BRIGHTNESS CURVE
    //---PLACEHOLDER FOR FLAME VARS
    case 23: thisdelay = 50; thisstep = 15; break;      //---VERITCAL RAINBOW
    case 24: thisdelay = 50; break;                     //---PACMAN
    case 25: thisdelay = 35; break;                     //---RANDOM COLOR POP
    case 26: thisdelay = 25; thishue = random(1, 252); break;        //---EMERGECNY STROBE
    case 27: thisdelay = 100; thishue = random(1, 252); break;        //---RGB PROPELLER
    case 28: thisdelay = 100; thishue = random(1, 252); break;       //---KITT
    case 29: thisdelay = 100; thishue = random(1, 252); break;       //---MATRIX RAIN
    case 30: thisdelay = 15; break;                      //---NEW RAINBOW LOOP
    case 17: thisdelay = 50; break;                     // colorWipe
    case 11: thisdelay = 50; break;                     // CylonBounce
    case 10: thisdelay = 15; break;                     // Fire
    case 9: thisdelay = 50; break;                     // NewKITT

    case 1: thisdelay = 50; break;                     // RunningLights


    case 102: one_color_all(255, 0, 0); LEDS.show(); my_RGB__(255, 0, 0); break; //---ALL RED
    case 103: one_color_all(0, 255, 0); LEDS.show();my_RGB__(0, 255, 0); break; //---ALL GREEN
    case 104: one_color_all(0, 0, 255); LEDS.show(); my_RGB__(0, 0, 255);break; //---ALL BLUE
    case 105: one_color_all(255, 255, 0); LEDS.show();my_RGB__(255, 255, 0); break; //---ALL COLOR X
    case 106: one_color_all(0, 255, 255); LEDS.show();my_RGB__(0, 255, 255); break; //---ALL COLOR Y
    case 107: one_color_all(255, 0, 255); LEDS.show();my_RGB__(255, 0, 255); break; //---ALL COLOR Z
  }
  bouncedirection = 0;
  one_color_all(0, 0, 0);
  ledMode = newmode;
}

void my_RGB__(int r, int g, int b){
  analogWrite(11, b/briggggg);
  analogWrite(10, r/briggggg);
  analogWrite(9, g/briggggg);
}
