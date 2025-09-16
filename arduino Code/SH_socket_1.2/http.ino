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
  HTTP.on("/mode/sh", mode4);

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

  HTTP.on("/schedule/set_time_zone", set_timeZone);
  HTTP.on("/schedule/set/1", scheduleSet1);
  HTTP.on("/schedule/set/2", scheduleSet2);
  HTTP.on("/schedule/set/3", scheduleSet3);
  
}

void scheduleSet1(){
  if (HTTP.arg("s_code") == S_code){ 
    HTTP.send(200, "text/plain", "s_code_correct");

    if(HTTP.arg("type") == "1"){
      relay.schedule_1.Create(HTTP.arg("f_hour").toInt(), HTTP.arg("f_min").toInt(), HTTP.arg("t_hour").toInt(), HTTP.arg("t_min").toInt());
    }else if(HTTP.arg("type") == "2"){
      relay.schedule_1.Create(HTTP.arg("f_hour").toInt(), HTTP.arg("f_min").toInt(), HTTP.arg("t_hour").toInt(), HTTP.arg("t_min").toInt(), HTTP.arg("day_index").toInt());
    }else if(HTTP.arg("type") == "3"){
      relay.schedule_1.Create(HTTP.arg("f_day_index").toInt(), HTTP.arg("f_hour").toInt(), HTTP.arg("f_min").toInt(), HTTP.arg("t_day_index").toInt(), HTTP.arg("t_hour").toInt(), HTTP.arg("t_min").toInt());
    }else
      relay.schedule_1.Destroy();
    
    tone(SPIC_PIN,2000,200);
    delay(310);
    tone(SPIC_PIN,2000,200);
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void scheduleSet2(){
  if (HTTP.arg("s_code") == S_code){ 
    HTTP.send(200, "text/plain", "s_code_correct");

    if(HTTP.arg("type") == "1"){
      relay.schedule_2.Create(HTTP.arg("f_hour").toInt(), HTTP.arg("f_min").toInt(), HTTP.arg("t_hour").toInt(), HTTP.arg("t_min").toInt());
    }else if(HTTP.arg("type") == "2"){
      relay.schedule_2.Create(HTTP.arg("f_hour").toInt(), HTTP.arg("f_min").toInt(), HTTP.arg("t_hour").toInt(), HTTP.arg("t_min").toInt(), HTTP.arg("day_index").toInt());
    }else if(HTTP.arg("type") == "3"){
      relay.schedule_2.Create(HTTP.arg("f_day_index").toInt(), HTTP.arg("f_hour").toInt(), HTTP.arg("f_min").toInt(), HTTP.arg("t_day_index").toInt(), HTTP.arg("t_hour").toInt(), HTTP.arg("t_min").toInt());
    }else
      relay.schedule_2.Destroy();
    
    tone(SPIC_PIN,2000,200);
    delay(310);
    tone(SPIC_PIN,2000,200);
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void scheduleSet3(){
  if (HTTP.arg("s_code") == S_code){ 
    HTTP.send(200, "text/plain", "s_code_correct");

    if(HTTP.arg("type") == "1"){
      relay.schedule_3.Create(HTTP.arg("f_hour").toInt(), HTTP.arg("f_min").toInt(), HTTP.arg("t_hour").toInt(), HTTP.arg("t_min").toInt());
    }else if(HTTP.arg("type") == "2"){
      relay.schedule_3.Create(HTTP.arg("f_hour").toInt(), HTTP.arg("f_min").toInt(), HTTP.arg("t_hour").toInt(), HTTP.arg("t_min").toInt(), HTTP.arg("day_index").toInt());
    }else if(HTTP.arg("type") == "3"){
      relay.schedule_3.Create(HTTP.arg("f_day_index").toInt(), HTTP.arg("f_hour").toInt(), HTTP.arg("f_min").toInt(), HTTP.arg("t_day_index").toInt(), HTTP.arg("t_hour").toInt(), HTTP.arg("t_min").toInt());
    }else
      relay.schedule_3.Destroy();
    
    tone(SPIC_PIN,2000,200);
    delay(310);
    tone(SPIC_PIN,2000,200);
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
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
  String mass = String(relay.Mode)+"\\"+String(relay.is_ON)+"\\"+String(relay.EEdel)+"\\"+String(relay.is_Flag)+"\\"+String(relay.is_Invert)+"\\"+String(time_Zone)+"\\"+String(relay.schedule_1.type)+"\\"+String(relay.schedule_2.type)+"\\"+String(relay.schedule_3.type)+"\\"+
  String(relay.schedule_1.day_index)+"\\"+String(relay.schedule_2.day_index)+"\\"+String(relay.schedule_3.day_index)+"\\"+
  String(relay.schedule_1.f_hour)+"\\"+String(relay.schedule_2.f_hour)+"\\"+String(relay.schedule_3.f_hour)+"\\"+String(relay.schedule_1.f_min)+"\\"+String(relay.schedule_2.f_min)+"\\"+String(relay.schedule_3.f_min)+"\\"+
  String(relay.schedule_1.t_hour)+"\\"+String(relay.schedule_2.t_hour)+"\\"+String(relay.schedule_3.t_hour)+"\\"+String(relay.schedule_1.t_min)+"\\"+String(relay.schedule_2.t_min)+"\\"+String(relay.schedule_3.t_min)+"\\"+
  String(n_hour)+"\\"+String(n_min)+"\\";
  HTTP.send(200, "text/plain", mass);    // ответить на HTTP запрос
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void module_invert_1(){
    if (HTTP.arg("s_code") == S_code){
  relay.is_Invert = 1;
  tone(SPIC_PIN,2000,200);
  delay(310);
  tone(SPIC_PIN,2000,200);
  HTTP.send(200,"text/plain", "Smart House - Invert modul OK");
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void set_timeZone(){
  if (HTTP.arg("s_code") == S_code){

    time_Zone = HTTP.arg("time").toInt();

  
  tone(SPIC_PIN,700,500);
  HTTP.send(200,"text/plain", "Smart House - Invert modul OK");
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}


void module_invert_0(){
    if (HTTP.arg("s_code") == S_code){
  relay.is_Invert = 0;
  tone(SPIC_PIN,700,500);
  HTTP.send(200,"text/plain", "Smart House - Invert modul OK");
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void module_flag_1(){
    if (HTTP.arg("s_code") == S_code){
  relay.is_Flag = 1;
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
  relay.is_Flag = 0;
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
  if(relay.Mode == 1){
    relay.setON(0);
    HTTP.send(200,"text/plain", "Smart House - GPIO OK");
    EEPROM_update();
  }else HTTP.send(404,"text/plain", "Smart House - GPIO NO");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void key1(){
    if (HTTP.arg("s_code") == S_code){
  if(relay.Mode == 1){
    relay.setON(1);
    HTTP.send(200,"text/plain", "Smart House - GPIO OK");
    EEPROM_update();
  }else HTTP.send(404,"text/plain", "Smart House - GPIO NO");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void mode1(){
    if (HTTP.arg("s_code") == S_code){
  relay.Mode = 1;
  relay.myTimer1 = millis(); tone(SPIC_PIN,1000,100);
  HTTP.send(200,"text/plain", "Smart House - save setting");
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void mode2(){
    if (HTTP.arg("s_code") == S_code){
  relay.Mode = 2;
  relay.myTimer1 = millis(); tone(SPIC_PIN,1000,100); delay(300); tone(SPIC_PIN,1000,100);
  HTTP.send(200,"text/plain", "Smart House - save setting");
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void mode3(){
    if (HTTP.arg("s_code") == S_code){
  relay.Mode = 3;
  relay.myTimer1 = millis(); tone(SPIC_PIN,1000,100); delay(300); tone(SPIC_PIN,1000,100); delay(300); tone(SPIC_PIN,1000,100);
  HTTP.send(200,"text/plain", "Smart House - save setting");
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void mode4(){
    if (HTTP.arg("s_code") == S_code){
  relay.Mode = 4;
  relay.myTimer1 = millis(); tone(SPIC_PIN,1000,100); delay(300); tone(SPIC_PIN,1000,100); delay(300); tone(SPIC_PIN,1000,100);delay(300); tone(SPIC_PIN,1000,100);
  HTTP.send(200,"text/plain", "Smart House - save setting");
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}


void ti10(){
    if (HTTP.arg("s_code") == S_code){
relay.delays=43200000;  tone(SPIC_PIN,1000,1000); relay.myTimer1 = millis();
relay.EEdel=10;
EEPROM_update();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti1(){
    if (HTTP.arg("s_code") == S_code){
  relay.delays=300000;   tone(SPIC_PIN,1000,1000); relay.myTimer1 = millis();
  relay.EEdel=1;
  EEPROM_update();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti2(){
    if (HTTP.arg("s_code") == S_code){
  relay.delays=600000;   tone(SPIC_PIN,1000,1000); relay.myTimer1 = millis();
  relay.EEdel=2;
  EEPROM_update();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti3(){
    if (HTTP.arg("s_code") == S_code){
  relay.delays=1800000;   tone(SPIC_PIN,1000,1000); relay.myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  relay.EEdel=3;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti4(){
    if (HTTP.arg("s_code") == S_code){
  relay.delays=3600000;   tone(SPIC_PIN,1000,1000); relay.myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  relay.EEdel=4;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti5(){
    if (HTTP.arg("s_code") == S_code){
  relay.delays=7200000;   tone(SPIC_PIN,1000,1000); relay.myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  relay.EEdel=5;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti6(){
    if (HTTP.arg("s_code") == S_code){
  relay.delays=10800000;   tone(SPIC_PIN,1000,1000); relay.myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  relay.EEdel=6;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti7(){
    if (HTTP.arg("s_code") == S_code){
  relay.delays=18000000;   tone(SPIC_PIN,1000,1000); relay.myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  relay.EEdel=7;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti8(){
    if (HTTP.arg("s_code") == S_code){
  relay.delays=28800000;  tone(SPIC_PIN,1000,1000); relay.myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  relay.EEdel=8;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti9(){
    if (HTTP.arg("s_code") == S_code){
  relay.delays=36000000;   tone(SPIC_PIN,1000,1000); relay.myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  relay.EEdel=9;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti11(){
    if (HTTP.arg("s_code") == S_code){
  relay.delays=61200000;   tone(SPIC_PIN,1000,1000); relay.myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  relay.EEdel=11;
  EEPROM_update();
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}
void ti12(){
    if (HTTP.arg("s_code") == S_code){
  relay.delays=86400000;  tone(SPIC_PIN,1000,1000); relay.myTimer1 = millis();
  HTTP.send(200,"text/plain", "Smart House - timer set");
  relay.EEdel=12;
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
  relay.Mode = 1;
  
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
