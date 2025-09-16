void HTTP_init(void){
  HTTP.onNotFound(handleNotFound);

  HTTP.on("/", home_page);
  HTTP.on("/home", home_page);
  HTTP.on("/settings", settings_page);
  HTTP.on("/test", send_test_code);
  HTTP.on("/get_data", send_data);
  
  HTTP.on("/eeprom_clear", restart_);
  HTTP.on("/restart", Restart);
  HTTP.on("/reset", Reset);
  HTTP.on("/reset_", Reset_);
  HTTP.on("/connection_attempt", connection_attempt);
  HTTP.on("/security_code_check", security_code_check);

  HTTP.on("/set_wifi_client", SetClientWiFi_);
  HTTP.on("/set_admin", SetAdmin);
  HTTP.on("/set_connection_attempts", SetConnection_attempts);
  
}

void SetAdmin(){
    if(HTTP.arg("login") == admin_login && HTTP.arg("password") == admin_password){
      admin_login = HTTP.arg("new_login");
      admin_password = HTTP.arg("new_password");
      writeString(100, admin_login);
      writeString(132,admin_password);

      HTTP.send(200, "text/html", Home_page_getHTML()); 
  }else
    HTTP.send(200, "text/html", Error_page_getHTML());
}
void SetClientWiFi_(){
    if(HTTP.arg("login") == admin_login && HTTP.arg("password") == admin_password){
      ssid = HTTP.arg("ssid");
      password = HTTP.arg("password_");
      writeString(0,ssid);
      writeString(32,password);
      HTTP.send(200, "text/html", Settings_page_getHTML()); 
  }else
    HTTP.send(200, "text/html", Error_page_getHTML());
}
void SetConnection_attempts(){
    if(HTTP.arg("login") == admin_login && HTTP.arg("password") == admin_password && HTTP.arg("connection_attempts").toInt() >= 10 && HTTP.arg("connection_attempts").toInt() <= 500){
      connection_attempts = HTTP.arg("connection_attempts").toInt();
       writeString(64, String(connection_attempts));
      HTTP.send(200, "text/html", Settings_page_getHTML()); 
  }else
    HTTP.send(200, "text/html", Error_page_getHTML());
}
void settings_page(){
  if(HTTP.arg("login") == admin_login && HTTP.arg("password") == admin_password)
    HTTP.send(200, "text/html", Settings_page_getHTML());
  else
    HTTP.send(200, "text/html", Error_page_getHTML());
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
  HTTP.send(200, "text/plain", "temp_m");    // ответить на HTTP запрос
}

void send_data() //обработчик
{
  if (HTTP.arg("s_code") == S_code){
  String mass = "\\" + String(0) + "\\";
  HTTP.send(200, "text/plain", mass);    // ответить на HTTP запрос
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void connection_attempt(){
  if (HTTP.arg("s_code") == S_code){ 
    HTTP.send(200, "text/plain", "Smart House - connection_attempt OK");
    tone(SPIC_PIN,2000,400);
    delay(300);
    tone(SPIC_PIN,2000,200);
  }else{ 
    HTTP.send(200, "text/plain", "s_code_incorrect");
  }
}

void handleNotFound(){
HTTP.send(404, "text/html", NotFound_page_getHTML());
}

void home_page(){
  HTTP.send(200, "text/html", Home_page_getHTML());
}

void restart_(){  
  if (HTTP.arg("s_code") == S_code){
  EEPROM_Clear();

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

void Reset(){
  if(HTTP.arg("login") == admin_login && HTTP.arg("password") == admin_password){
    HTTP.send(200, "text/html", Settings_page_getHTML());
    ESP.restart();   
  }else
    HTTP.send(200, "text/html", Error_page_getHTML());
}

void Reset_(){
  if(HTTP.arg("login") == admin_login && HTTP.arg("password") == admin_password){
    HTTP.send(200, "text/html", Settings_page_getHTML());
    WiFi.mode(WIFI_OFF);
    setup();  
  }else
    HTTP.send(200, "text/html", Error_page_getHTML());
}
