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

void send_test_code() //обработчик
{
  HTTP.send(200, "text/plain", "socket");    // ответить на HTTP запрос
}

void send_data() //обработчик
{
    if (HTTP.arg("s_code") == S_code){
  String mass = String(Mode)+"\\"+String(is_ON)+"\\"+String(EEdel)+"\\"+String(is_Flag)+"\\"+String(is_Invert)+"\\";
  HTTP.send(200, "text/plain", mass);    // ответить на HTTP запрос
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void module_invert_1(){
    if (HTTP.arg("s_code") == S_code){
  is_Invert = 1;
  tone(SPIC_PIN,2000,200);
  delay(310);
  tone(SPIC_PIN,2000,200);
  HTTP.send(200,"text/plain", "Smart House - Invert modul OK");
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}



void module_invert_0(){
    if (HTTP.arg("s_code") == S_code){
  is_Invert = 0;
  tone(SPIC_PIN,700,500);
  HTTP.send(200,"text/plain", "Smart House - Invert modul OK");
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void module_flag_1(){
    if (HTTP.arg("s_code") == S_code){
  is_Flag = 1;
  tone(SPIC_PIN,2000,200);
  delay(310);
  tone(SPIC_PIN,2000,200);
  HTTP.send(200,"text/plain", "Smart House - Fix modul OK");
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void module_flag_0(){
    if (HTTP.arg("s_code") == S_code){
  is_Flag = 0;
  tone(SPIC_PIN,700,500);
  HTTP.send(200,"text/plain", "Smart House - Fix modul OK");
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}


void connection_attempt(){
  tone(SPIC_PIN,700,400);
  delay(300);
  tone(SPIC_PIN,2000,200);
  HTTP.send(200,"text/plain", "Smart House - connection_attempt OK");
}

void key0(){
    if (HTTP.arg("s_code") == S_code){
  if(Mode == 1){
    is_ON = 0;
    digitalWrite(RELE_PIN, is_ON); 
    HTTP.send(200,"text/plain", "Smart House - GPIO OK");
    EEPROM_update();
  }else HTTP.send(404,"text/plain", "Smart House - GPIO NO");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void key1(){
    if (HTTP.arg("s_code") == S_code){
  if(Mode == 1){
    is_ON = 1;
    digitalWrite(RELE_PIN, is_ON); 
    HTTP.send(200,"text/plain", "Smart House - GPIO OK");
    EEPROM_update();
  }else HTTP.send(404,"text/plain", "Smart House - GPIO NO");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void mode1(){
    if (HTTP.arg("s_code") == S_code){
  Mode = 1;
  myTimer1 = millis(); tone(SPIC_PIN,1000,100);
  HTTP.send(200,"text/plain", "Smart House - save setting");
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void mode2(){
    if (HTTP.arg("s_code") == S_code){
  Mode = 2;
  myTimer1 = millis(); tone(SPIC_PIN,1000,100); delay(300); tone(SPIC_PIN,1000,100);
  HTTP.send(200,"text/plain", "Smart House - save setting");
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void mode3(){
    if (HTTP.arg("s_code") == S_code){
  Mode = 3;
  myTimer1 = millis(); tone(SPIC_PIN,1000,100); delay(300); tone(SPIC_PIN,1000,100); delay(300); tone(SPIC_PIN,1000,100);
  HTTP.send(200,"text/plain", "Smart House - save setting");
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}


void ti10(){
    if (HTTP.arg("s_code") == S_code){
delays=43200000;  tone(SPIC_PIN,1000,1000); myTimer1 = millis();
EEdel=10;
EEPROM_update();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti1(){
    if (HTTP.arg("s_code") == S_code){
  delays=300000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  EEdel=1;
  EEPROM_update();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti2(){
    if (HTTP.arg("s_code") == S_code){
  delays=600000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  EEdel=2;
  EEPROM_update();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti3(){
    if (HTTP.arg("s_code") == S_code){
  delays=1800000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=3;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti4(){
    if (HTTP.arg("s_code") == S_code){
  delays=3600000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=4;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti5(){
    if (HTTP.arg("s_code") == S_code){
  delays=7200000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=5;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti6(){
    if (HTTP.arg("s_code") == S_code){
  delays=10800000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=6;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti7(){
    if (HTTP.arg("s_code") == S_code){
  delays=18000000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=7;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti8(){
    if (HTTP.arg("s_code") == S_code){
  delays=28800000;  tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=8;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti9(){
    if (HTTP.arg("s_code") == S_code){
  delays=36000000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=9;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti11(){
    if (HTTP.arg("s_code") == S_code){
  delays=61200000;   tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=11;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti12(){
    if (HTTP.arg("s_code") == S_code){
  delays=86400000;  tone(SPIC_PIN,1000,1000); myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  EEdel=12;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
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
    if (HTTP.arg("s_code") == S_code){
  ssid="wifi";
  password="12345678";
  writeString(0,ssid);
  writeString(32,password);
  Mode = 1;
  
  String mes = "Smart House - Clear data: OK";
  HTTP.send(200,"text/plain", mes);
  ESP.restart();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void restart_1(){  
  ssid="wifi";
  password="12345678";
  writeString(0,ssid);
  writeString(32,password);
  Config_mode();
}

void Restart(){ 
    if (HTTP.arg("s_code") == S_code){ 
  String mes = "Smart House - Restart: OK";
  HTTP.send(200,"text/plain", mes);
  ESP.restart();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
