void HTTP_init(void){
  HTTP.onNotFound(handleNotFound);
  
  HTTP.on("/test", send_test_code);
  HTTP.on("/get_data", send_data);
  
  HTTP.on("/", handleMain);
  HTTP.on("/redat", restart_);
  HTTP.on("/restart", Restart);
  HTTP.on("/connection_attempt", connection_attempt);
  HTTP.on("/security_code_check", security_code_check);
  
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



void connection_attempt(){
  tone(SPIC_PIN,700,400);
  delay(300);
  tone(SPIC_PIN,2000,200);
  HTTP.send(200,"text/plain", "Smart House - connection_attempt OK");
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
