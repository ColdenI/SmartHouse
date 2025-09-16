void HTTP_init(void){
  HTTP.onNotFound(handleNotFound);
  
  HTTP.on("/test", send_test_code);
  HTTP.on("/get_data", send_data);
  
  HTTP.on("/", handleMain);
  HTTP.on("/redat", restart_);
  HTTP.on("/restart", Restart);
  HTTP.on("/connection_attempt", connection_attempt);
  HTTP.on("/security_code_check", security_code_check);

  HTTP.on("/key/0", key0);
  HTTP.on("/key/1", key1);

  HTTP.on("/modul/invert/1", module_invert_1);
  HTTP.on("/modul/invert/0", module_invert_0);
  
  HTTP.on("/modul/flag/1", module_flag_1);
  HTTP.on("/modul/flag/0", module_flag_0);
  
  HTTP.on("/mode/s", mode1);
  HTTP.on("/mode/t", mode2);
  HTTP.on("/mode/m", mode3);

  HTTP.on("/timer_delay/m5", ti1);
  HTTP.on("/timer_delay/m10", ti2);
  HTTP.on("/timer_delay/m30", ti3);
  HTTP.on("/timer_delay/h1", ti4);
  HTTP.on("/timer_delay/h2", ti5);
  HTTP.on("/timer_delay/h3", ti6);
  HTTP.on("/timer_delay/h5", ti7);
  HTTP.on("/timer_delay/h8", ti8);
  HTTP.on("/timer_delay/h10", ti9);
  HTTP.on("/timer_delay/h12", ti10);
  HTTP.on("/timer_delay/h17", ti11);
  HTTP.on("/timer_delay/h24", ti12);
  
}

void send_test_code() //обработчик
{
  HTTP.send(200, "text/plain", "socket");    // ответить на HTTP запрос
}

void send_data() //обработчик
{
  String mass = String(Mode)+"\\"+String(is_ON)+"\\"+String(EEdel)+"\\"+String(is_Flag)+"\\"+String(is_Invert)+"\\";
  HTTP.send(200, "text/plain", mass);    // ответить на HTTP запрос
}

void module_invert_1(){
  is_Invert = 1;
  tone(SPIC_PIN,2000,200);
  delay(310);
  tone(SPIC_PIN,2000,200);
  HTTP.send(200,"text/plain", "Smart House - Invert modul OK");
  EEPROM_update();
}



void module_invert_0(){
  is_Invert = 0;
  tone(SPIC_PIN,700,500);
  HTTP.send(200,"text/plain", "Smart House - Invert modul OK");
  EEPROM_update();
}

void module_flag_1(){
  is_Flag = 1;
  tone(SPIC_PIN,2000,200);
  delay(310);
  tone(SPIC_PIN,2000,200);
  HTTP.send(200,"text/plain", "Smart House - Fix modul OK");
  EEPROM_update();
}

void module_flag_0(){
  is_Flag = 0;
  tone(SPIC_PIN,700,500);
  HTTP.send(200,"text/plain", "Smart House - Fix modul OK");
  EEPROM_update();
}

void security_code_check(){
  if (HTTP.arg("s_code") == S_code){ 
    HTTP.send(200, "text/plain", "s_code_correct");
    tone(SPIC_PIN,2000,200);
    delay(310);
    tone(SPIC_PIN,2000,200);
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void connection_attempt(){
  tone(SPIC_PIN,700,400);
  delay(300);
  tone(SPIC_PIN,2000,200);
  HTTP.send(200,"text/plain", "Smart House - connection_attempt OK");
  EEPROM_update();
}

void key0(){
  if(Mode == 1){
    is_ON = 0;
    digitalWrite(RELE_PIN, is_ON); 
    HTTP.send(200,"text/plain", "Smart House - GPIO OK");
    EEPROM_update();
  }else HTTP.send(404,"text/plain", "Smart House - GPIO NO");
}

void key1(){
  if(Mode == 1){
    is_ON = 1;
    digitalWrite(RELE_PIN, is_ON); 
    HTTP.send(200,"text/plain", "Smart House - GPIO OK");
    EEPROM_update();
  }else HTTP.send(404,"text/plain", "Smart House - GPIO NO");
}

void mode1(){
  Mode = 1;
  myTimer1 = millis(); tone(SPIC_PIN,1000,100);
  HTTP.send(200,"text/plain", "Smart House - save setting");
  EEPROM_update();
}

void mode2(){
  Mode = 2;
  myTimer1 = millis(); tone(SPIC_PIN,1000,100); delay(300); tone(SPIC_PIN,1000,100);
  HTTP.send(200,"text/plain", "Smart House - save setting");
  EEPROM_update();
}


void mode3(){
  Mode = 3;
  myTimer1 = millis(); tone(SPIC_PIN,1000,100); delay(300); tone(SPIC_PIN,1000,100); delay(300); tone(SPIC_PIN,1000,100);
  HTTP.send(200,"text/plain", "Smart House - save setting");
  EEPROM_update();
}


void ti10(){
delays=43200000;  tone(SPIC_PIN,1000,1000); myTimer1 = millis();
EEdel=10;
EEPROM_update();
  HTTP.send(200,"text/plain", "Smart House - timer set");
}
void ti1(){
  delays=300000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  EEdel=1;
  EEPROM_update();
  HTTP.send(200,"text/plain", "Smart House - timer set");
}
void ti2(){
  delays=600000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  EEdel=2;
  EEPROM_update();
  HTTP.send(200,"text/plain", "Smart House - timer set");
}
void ti3(){
  delays=1800000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=3;
  EEPROM_update();
}
void ti4(){
  delays=3600000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=4;
  EEPROM_update();
}
void ti5(){
  delays=7200000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=5;
  EEPROM_update();
}
void ti6(){
  delays=10800000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=6;
  EEPROM_update();
}
void ti7(){
  delays=18000000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=7;
  EEPROM_update();
}
void ti8(){
  delays=28800000;  tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=8;
  EEPROM_update();
}
void ti9(){
  delays=36000000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=9;
  EEPROM_update();
}
void ti11(){
  delays=61200000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=11;
  EEPROM_update();
}
void ti12(){
  delays=86400000;  tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=12;
  EEPROM_update();
}

void handleNotFound(){
  String mes = "Not Found!";
  mes+= "URI: ";
  mes+=HTTP.uri();
  HTTP.send(404,"text/plain", mes);
}

void handleMain(){
  String mes = "Smart House - Main page";
  HTTP.send(200,"text/plain", mes);
}

void restart_(){  
  ssid="wifi";
  password="12345678";
  writeString(0,ssid);
  writeString(32,password);
  Mode = 1;
  
  String mes = "Smart House - Clear data: OK";
  HTTP.send(200,"text/plain", mes);
  ESP.restart();
}

void restart_1(){  
  ssid="wifi";
  password="12345678";
  writeString(0,ssid);
  writeString(32,password);
  Config_mode();
}

void Restart(){  
  String mes = "Smart House - Restart: OK";
  HTTP.send(200,"text/plain", mes);
  ESP.restart();
}
