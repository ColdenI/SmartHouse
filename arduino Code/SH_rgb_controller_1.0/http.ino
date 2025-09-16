void HTTP_init(void){
  HTTP.onNotFound(handleNotFound);
  
  HTTP.on("/test", send_test_code);
  HTTP.on("/get_data", send_data);
  
  HTTP.on("/", handleMain);
  HTTP.on("/redat", restart_);
  HTTP.on("/restart", Restart);
  HTTP.on("/connection_attempt", connection_attempt);
  HTTP.on("/security_code_check", security_code_check);

  HTTP.on("/brightness", set_brightness);
  
  HTTP.on("/mode", set_mode);
  HTTP.on("/color", set_color);
  HTTP.on("/speed", set_speed);

  HTTP.on("/timer_off", set_timer_off);
  HTTP.on("/auto_time", set_timer_auto);
  
}



void set_timer_auto(){
  if (HTTP.arg("s_code") == S_code){ 
    
    int time_auto = HTTP.arg("time").toInt();
    if(time_auto != 0){
      Auto_Time = time_auto * 60000;
      isAuto = 1;
    }else{
      isAuto = 0;
      Auto_Time = 0;
    }
    
    mode_tick();
    HTTP.send(200, "text/plain", "Smart House - SET timer auto");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }    
}

void set_timer_off(){
  if (HTTP.arg("s_code") == S_code){ 
    
    int time_auto_off = HTTP.arg("time").toInt();
    if(time_auto_off != 0){
      AutoOff_Time = time_auto_off * 60000;
      isAutoOff = 1;
      AutoOff_Timer = millis();
    }else{
      isAutoOff = 0;
      AutoOff_Time = 0;
    }
    
    mode_tick();
    HTTP.send(200, "text/plain", "Smart House - SET timer off");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }    
}

void set_speed(){
  if (HTTP.arg("s_code") == S_code){ 
    speed = HTTP.arg("speed").toInt();
    mode_tick();
    HTTP.send(200, "text/plain", "Smart House - SET speed");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }    
}

void set_brightness(){
  if (HTTP.arg("s_code") == S_code){ 
    brig = HTTP.arg("brightness").toInt();
    mode_tick();
    HTTP.send(200, "text/plain", "Smart House - SET brightness");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }    
}

void set_color(){
  if (HTTP.arg("s_code") == S_code){ 
    Mode = 1;
    color_R = HTTP.arg("r").toInt();
    color_G = HTTP.arg("g").toInt();
    color_B = HTTP.arg("b").toInt();
    
    mode_tick();
    HTTP.send(200, "text/plain", "Smart House - SET COLOR");
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }    
}

void set_mode(){
  if (HTTP.arg("s_code") == S_code){ 
    Mode = HTTP.arg("mode").toInt();
    mode_tick();
    HTTP.send(200, "text/plain", "Smart House - SET MODE");
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
  String mass = String(Mode)+"\\"+String(brig)+"\\"+String(isAuto)+"\\"+String(isAutoOff)+"\\"+String(AutoOff_Time)+"\\"+String(AutoOff_Time - (millis() - AutoOff_Timer)) + "\\" + String(speed) + "\\" + String(color_R) + "\\" + String(color_G) + "\\" + String(color_B);
  HTTP.send(200, "text/plain", mass);    // ответить на HTTP запрос
}

void send_test_code() //обработчик
{
  HTTP.send(200, "text/plain", "rgb_lamp");    // ответить на HTTP запрос
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
