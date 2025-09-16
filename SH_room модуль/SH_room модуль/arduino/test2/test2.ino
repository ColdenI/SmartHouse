// простая функция отправки по GBUS
#include "GBUSmini.h"  // мини-библиотека с лёгкими функциями

#define TRX_PIN 4    // пин
#define MY_ADDR 5   // наш адрес

void setup() {
  pinMode(TRX_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

// отправляемая дата (байты)
char data[] = {' ', 's', 'd'};

void loop() {
  // пин, адрес получателя, адрес отправителя, дата, размер
  GBUS_send(TX_PIN, RX_ADDR, TX_ADDR, data, sizeof(data));
  delay(1000);
}



char data_[6];       // приёмный буфер (байты)


void loop() {
  // ждём приём, если функция вернула отличное от 0 значение
  if (GBUS_read(RX_PIN, RX_ADDR, data, sizeof(data))) {
    // если успешно приняли
    for (char i = 0; i < sizeof(data); i++) {
      Serial.print(data[i]);
      Serial.print(" ");
    }
    Serial.println();
  }
}
