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

  HTTP.on("/mode0", set_mode_0);
  
  HTTP.on("/mode1", set_mode_1);
  HTTP.on("/mode2", set_mode_2);
  HTTP.on("/mode3", set_mode_3);
  HTTP.on("/mode4", set_mode_4);
  HTTP.on("/mode5", set_mode_5);
  HTTP.on("/mode6", set_mode_6);
  HTTP.on("/mode7", set_mode_7);
  HTTP.on("/mode8", set_mode_8);
  HTTP.on("/mode9", set_mode_9);
  HTTP.on("/mode10", set_mode_10);
  HTTP.on("/mode11", set_mode_11);
  HTTP.on("/mode12", set_mode_12);
  HTTP.on("/mode13", set_mode_13);
  HTTP.on("/mode14", set_mode_14);
  HTTP.on("/mode15", set_mode_15);
  HTTP.on("/mode16", set_mode_16);
  HTTP.on("/mode17", set_mode_17);
  HTTP.on("/mode18", set_mode_18);
  HTTP.on("/mode19", set_mode_19);
  HTTP.on("/mode20", set_mode_20);
  HTTP.on("/mode21", set_mode_21);
  HTTP.on("/mode22", set_mode_22);
  HTTP.on("/mode23", set_mode_23);
  HTTP.on("/mode24", set_mode_24);
  HTTP.on("/mode25", set_mode_25);
  HTTP.on("/mode26", set_mode_26);
  HTTP.on("/mode27", set_mode_27);
  HTTP.on("/mode28", set_mode_28);
  HTTP.on("/mode29", set_mode_29);
  HTTP.on("/mode30", set_mode_30);

   HTTP.on("/bri_1", set_bri_1);
   HTTP.on("/bri_2", set_bri_2);
   HTTP.on("/bri_3", set_bri_3);
   HTTP.on("/bri_4", set_bri_4);
   HTTP.on("/bri_5", set_bri_5);

   HTTP.on("/color_1", set_color_1);
   HTTP.on("/color_2", set_color_2);
   HTTP.on("/color_3", set_color_3);
   HTTP.on("/color_4", set_color_4);
   HTTP.on("/color_5", set_color_5);
   HTTP.on("/color_6", set_color_6);
   HTTP.on("/color_7", set_color_7);

   HTTP.on("/timer_15", set_timer_off_15);
   HTTP.on("/timer_30", set_timer_off_30);
   HTTP.on("/timer_n", set_timer_off_n);

   HTTP.on("/auto_1", set_auto_1);
   HTTP.on("/auto_0", set_auto_0);
  
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
  String mass = String(Mode_l)+"\\"+String(is_lemp)+"\\"+String(isAuto)+"\\"+String(isAutoOff)+"\\"+String(AutoOff_Time)+"\\"+String(AutoOff_Time - (millis() - AutoOff_Timer));
  HTTP.send(200, "text/plain", mass);    // ответить на HTTP запрос
}


void set_auto_1(){
  isAuto = 1;
  AutoL_Timer = millis();  
  tone(4,2000,200);delay(300);tone(4,2000,200); 
  HTTP.send(200,"text/plain", "Smart House - OK"); 
  EEPROM_update();
}
void set_auto_0(){
  isAuto = 0;
  AutoL_Timer = millis();  
  tone(4,2000,500);
  HTTP.send(200,"text/plain", "Smart House - OK"); 
  EEPROM_update();
}


void set_timer_off_15(){
  AutoOff_Timer = millis();
  isAutoOff = 1;
  AutoOff_Time = 15 * 60000;
  tone(4,2000,200);delay(300);tone(4,2000,200); 
  HTTP.send(200,"text/plain", "Smart House - OK");
}
void set_timer_off_30(){
  AutoOff_Timer = millis();
  isAutoOff = 1;
  AutoOff_Time = 30 * 60000;
  tone(4,2000,200);delay(300);tone(4,2000,200); 
  HTTP.send(200,"text/plain", "Smart House - OK");
}
void set_timer_off_n(){
  AutoOff_Timer = millis();
  isAutoOff = 0;
  tone(4,2000,500);
  HTTP.send(200,"text/plain", "Smart House - OK");
}


void set_color_1(){
  set_Mode(101);
  HTTP.send(200,"text/plain", "Smart House - OK");
}
void set_color_2(){
  set_Mode(102);
  HTTP.send(200,"text/plain", "Smart House - OK");
}
void set_color_3(){
  set_Mode(103);
  HTTP.send(200,"text/plain", "Smart House - OK");
}
void set_color_4(){
  set_Mode(104);
  HTTP.send(200,"text/plain", "Smart House - OK");
}
void set_color_5(){
  set_Mode(105);
  HTTP.send(200,"text/plain", "Smart House - OK");
}
void set_color_6(){
  set_Mode(106);
  HTTP.send(200,"text/plain", "Smart House - OK");
}
void set_color_7(){
  set_Mode(107);
  HTTP.send(200,"text/plain", "Smart House - OK");
}




void set_bri_1(){
  Serial.print(201);
  delay(50);
  //set_Mode(Mode_l);
  HTTP.send(200,"text/plain", "Smart House - OK");
}
void set_bri_2(){
  Serial.print(202);
  delay(50);
  //set_Mode(Mode_l);
  HTTP.send(200,"text/plain", "Smart House - OK");
}
void set_bri_3(){
  Serial.print(203);
  delay(50);
  //set_Mode(Mode_l);
  HTTP.send(200,"text/plain", "Smart House - OK");
}
void set_bri_4(){
  Serial.print(204);
  delay(50);
  //set_Mode(Mode_l);
  HTTP.send(200,"text/plain", "Smart House - OK");
}
void set_bri_5(){
  Serial.print(205);
  delay(50);
  //set_Mode(Mode_l);
  HTTP.send(200,"text/plain", "Smart House - OK");
}



void set_mode_0  (){
  set_Mode(0);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_1  (){
  set_Mode(1);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_2  (){
  set_Mode(2);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_3  (){
  set_Mode(3);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_4  (){
  set_Mode(4);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_5  (){
  set_Mode(5);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_6  (){
  set_Mode(6);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_7  (){
  set_Mode(7);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_8  (){
  set_Mode(8);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_9  (){
  set_Mode(9);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_10  (){
  set_Mode(10);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_11  (){
  set_Mode(11);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_12  (){
  set_Mode(12);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_13  (){
  set_Mode(13);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_14  (){
  set_Mode(14);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_15  (){
  set_Mode(15);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_16  (){
  set_Mode(16);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_17  (){
  set_Mode(17);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_18  (){
  set_Mode(18);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_19  (){
  set_Mode(19);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_20  (){
  set_Mode(20);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_21  (){
  set_Mode(21);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_22  (){
  set_Mode(22);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_23  (){
  set_Mode(23);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_24  (){
  set_Mode(24);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_25  (){
  set_Mode(25);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_26  (){
  set_Mode(26);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_27  (){
  set_Mode(27);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_28 (){
  set_Mode(28);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_29  (){
  set_Mode(29);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
}
void set_mode_30  (){
  set_Mode(30);
  HTTP.send(200,"text/plain", "Smart House - security_code_check OK");
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

void key0(){
  set_Lemp(0);
  HTTP.send(200,"text/plain", "Smart House - GPIO OK");
}

void key1(){
  set_Lemp(1);
  HTTP.send(200,"text/plain", "Smart House - GPIO OK");
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
