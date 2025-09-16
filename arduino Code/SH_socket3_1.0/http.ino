
void send_test_code() //обработчик
{
  HTTP.send(200, "text/plain", "socket-3");    // ответить на HTTP запрос
}

void send_data() //обработчик
{
  //String mass = String(Mode)+"\\"+String(is_ON)+"\\"+String(EEdel)+"\\"+String(is_Flag)+"\\"+String(is_Invert)+"\\";
  //HTTP.send(200, "text/plain", mass);    // ответить на HTTP запрос
}



void key10(){
  if(S1.Mode == 1){
    S1.is_ON = 0;
    digitalWrite(RELE_PIN_1, S1.is_ON); 
    HTTP.send(200,"text/plain", "Smart House - GPIO OK");
}
}
void key11(){
  if(S1.Mode == 1){
    S1.is_ON = 0;
    digitalWrite(RELE_PIN_1, S1.is_ON); 
    HTTP.send(200,"text/plain", "Smart House - GPIO OK");
}
}


void security_code_check(){
  tone(SPIC_PIN,700,400);
  delay(300);
  tone(SPIC_PIN,2000,200);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
  EEPROM_update();
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
  
  S1.Mode = 1;
  S2.Mode = 1;
  S3.Mode = 1;
  
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





void HTTP_init(void){
  HTTP.onNotFound(handleNotFound);
  
  HTTP.on("/test", send_test_code);
  HTTP.on("/get_data", send_data);
  
  HTTP.on("/", handleMain);
  HTTP.on("/redat", restart_);
  HTTP.on("/restart", Restart);
  HTTP.on("/connection_attempt", connection_attempt);
  HTTP.on("/security_code_check", security_code_check);

  HTTP.on("/key-1/0", key10);
  HTTP.on("/key-1/1", key11);
  /*
  HTTP.on("/key-2/0", key20);
  HTTP.on("/key-2/1", key21);
  HTTP.on("/key-3/0", key30);
  HTTP.on("/key-3/1", key31);
  
  HTTP.on("/mode1/s", mode11);
  HTTP.on("/mode1/t", mode12);
  HTTP.on("/mode2/s", mode21);
  HTTP.on("/mode2/t", mode22);
  HTTP.on("/mode3/s", mode31);
  HTTP.on("/mode3/t", mode32);
 

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
  */
  
}
