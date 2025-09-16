void HTTP_init(void){
  HTTP.onNotFound(handleNotFound);
  
  HTTP.on("/test", send_test_code);
  HTTP.on("/get_data", send_data);
  
  HTTP.on("/", handleMain);
  HTTP.on("/redat", restart_);
  HTTP.on("/restart", Restart);
  HTTP.on("/connection_attempt", connection_attempt);
  HTTP.on("/security_code_check", security_code_check);

  HTTP.on("/key/set", set_key);
  
  HTTP.on("/mode/set", set_mode);
  
  HTTP.on("/mode/auto/set", set_auto);

  HTTP.on("/bri/set", set_bri);

  HTTP.on("/color/set", set_color);

  HTTP.on("/timer/set", set_timer_off);

  HTTP.on("/schedule/time_zone/set", set_timeZone);

  HTTP.on("/schedule/set", scheduleSet);

  
  
}


void scheduleSet(){
  if (HTTP.arg("s_code") == S_code){ 
    HTTP.send(200, "text/plain", "s_code_correct");
    
    bool _isInvLamp = true;
    if(HTTP.arg("is_inv_lamp") == "0") _isInvLamp = false; else _isInvLamp = true;
      
    if(HTTP.arg("type") == "1"){
      schedule.Create(HTTP.arg("f_hour").toInt(), HTTP.arg("f_min").toInt(), _isInvLamp);
    }else if(HTTP.arg("type") == "2"){
      schedule.Create(HTTP.arg("f_hour").toInt(), HTTP.arg("f_min").toInt(), HTTP.arg("day_index").toInt(), _isInvLamp);
    }else
      schedule.Destroy();
    
    tone(SPIC_PIN,2000,200);
    delay(310);
    tone(SPIC_PIN,2000,200);
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

void security_code_check(){
  if (HTTP.arg("s_code") == S_code){ 
    HTTP.send(200, "text/plain", "s_code_correct");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void send_data() //обработчик
{
  if (HTTP.arg("s_code") == S_code){ 
    String mass = String(Mode_l)+"\\"+String(is_lemp)+"\\"+String(isAuto)+"\\"+String(isAutoOff)+"\\"+String(AutoOff_Time)+"\\"+String(AutoOff_Time - (millis() - AutoOff_Timer))+"\\"+String(n_hour)+"\\"+String(n_min)+"\\"+
    String(schedule.type)+"\\"+String(schedule.f_hour)+"\\"+String(schedule.f_min)+"\\"+String(schedule.day_index)+"\\"+String(schedule.isInvLamp);
    HTTP.send(200, "text/plain", mass);    // ответить на HTTP запрос
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}


void set_auto(){
  if (HTTP.arg("s_code") == S_code){ 
    if(HTTP.arg("arg") == "0"){
      isAuto = 0;     
      tone(SPIC_PIN,2000,1000);
    }else{
      isAuto = 1; 
      tone(SPIC_PIN,2000,200);delay(300);tone(SPIC_PIN,2000,200);  
    }
    
    AutoL_Timer = millis();  
    HTTP.send(200,"text/plain", "Smart House - OK"); 
    EEPROM_update();
    
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void set_timer_off(){
  if (HTTP.arg("s_code") == S_code){ 
    int _time = HTTP.arg("time").toInt();

    if(_time == -1){
      isAutoOff = 0;
      tone(SPIC_PIN,2000,1000); 
    }else{
      isAutoOff = 1;
      AutoOff_Time = _time * 60000;
      tone(SPIC_PIN,2000,200);delay(300);tone(SPIC_PIN,2000,200); 
    }

    HTTP.send(200,"text/plain", "Smart House - OK");
    AutoOff_Timer = millis();
    
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }  
}

void set_color(){
  if (HTTP.arg("s_code") == S_code){
    int _color = HTTP.arg("arg").toInt();
    
    if(_color > 0 && _color < 8){
      set_Mode(100 + _color);
      HTTP.send(200,"text/plain", "Smart House - OK");
      delay(50);
    }else{
      HTTP.send(200, "text/plain", "color_incorrect");
    }
    
    
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
  
}

void set_bri(){
  if (HTTP.arg("s_code") == S_code){
    int _bri = HTTP.arg("arg").toInt();
    
    if(_bri > 0 && _bri < 6){
      Serial.print(200 + _bri);
      delay(50);
    }
    
    HTTP.send(200,"text/plain", "Smart House - OK");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void set_mode(){
  if (HTTP.arg("s_code") == S_code){
    int _mode = HTTP.arg("arg").toInt();
    
    if(_mode >= 0 && _mode <= 30){
      set_Mode(_mode);
      delay(50);
    }
    
    HTTP.send(200,"text/plain", "Smart House - OK");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  } 
}

void set_key(){
  if (HTTP.arg("s_code") == S_code){
    
    if(HTTP.arg("arg") == "0"){
      set_Lemp(0);
    }else{
      set_Lemp(1);
    }
    
    HTTP.send(200,"text/plain", "Smart House - OK");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}




void send_test_code() //обработчик
{
  HTTP.send(200, "text/plain", "lemp");    // ответить на HTTP запрос
}

void connection_attempt(){
  tone(SPIC_PIN,700,400);
  delay(300);
  tone(SPIC_PIN,2000,200);
  HTTP.send(200,"text/plain", "Smart House - connection_attempt OK");
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
