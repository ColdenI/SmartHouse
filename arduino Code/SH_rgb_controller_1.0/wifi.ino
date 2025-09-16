void WIFIinit(){
  WiFi.mode(WIFI_STA);

  // Подключаемся к сети WiFi
  if(IS_DEBUG)Serial.println();
  if(IS_DEBUG)Serial.println();
  if(IS_DEBUG)Serial.print("Connecting to ");
  if(IS_DEBUG)Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Ожидание подключения
  int iii = 0;
  while (WiFi.status() != WL_CONNECTED) {
    
    delay(1500);
    if(IS_DEBUG)Serial.print(".");
    tone(SPIC_PIN,500,100);
    iii++;
    if (iii>=connection_attempts) break;
  }
  if (WiFi.status()== WL_CONNECTED){
    SO_conect();
    if(IS_DEBUG)Serial.println("");
    if(IS_DEBUG)Serial.println("WiFi connected");
    // Запуск сервера
    HTTP.begin();
    if(IS_DEBUG)Serial.println("Server started");
    // Вывод полученного IP адреса
    if(IS_DEBUG)Serial.println(WiFi.localIP());
    
  }
  else Config_mode();


}

void Config_mode(){
  if(IS_DEBUG)Serial.println("Config mode");
  SO_conect2();
  portalStart();
  bool is_config_mode = 1;
  while(is_config_mode){
    
      if (millis() - myTimer2 >= 6000) {   // ищем разницу (500 мс)
        myTimer2 = millis();              // сброс таймера
        tone(SPIC_PIN,600,200);
        tone(SPIC_PIN,900,200);
        if(IS_DEBUG)Serial.print(".");
    }
    if (portalTick()) {
      if(IS_DEBUG)Serial.println(portalStatus());
      if (portalStatus() == SP_SUBMIT) {
        if(IS_DEBUG)Serial.println(portalCfg.SSID);
        ssid = portalCfg.SSID;
        if(IS_DEBUG)Serial.println(portalCfg.pass);
        password = portalCfg.pass;
        is_config_mode = 0;
        writeString(0,ssid);
        writeString(32,password);
        // забираем логин-пароль
      }
  
      // сработает однократно при действии
      // точка будет автоматически выключена
    }
  }
 WIFIinit();
}
