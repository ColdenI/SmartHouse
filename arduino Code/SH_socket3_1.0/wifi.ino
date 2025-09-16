void WIFIinit(){
  WiFi.mode(WIFI_STA);

  // Подключаемся к сети WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Ожидание подключения
  int iii = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(600);
    Serial.print(".");
    tone(SPIC_PIN,700,200);
    iii++;
    if (iii>=connection_attempts) break;
  }
  if (WiFi.status()== WL_CONNECTED){
    SO_conect();
    Serial.println("");
    Serial.println("WiFi connected");
    // Запуск сервера
    HTTP.begin();
    Serial.println("Server started");
    // Вывод полученного IP адреса
    Serial.println(WiFi.localIP());

  }
  else Config_mode();


}

void Config_mode(){
  Serial.println("Config mode");
  SO_conect2();
  portalStart();
  bool is_config_mode = 1;
  while(is_config_mode){
      if (millis() - myTimer2 >= 4000) {   // ищем разницу (500 мс)
        myTimer2 = millis();              // сброс таймера
        tone(SPIC_PIN,600,200);
        tone(SPIC_PIN,900,200);
        Serial.print(".");
    }
    if (portalTick()) {
      Serial.println(portalStatus());
      if (portalStatus() == SP_SUBMIT) {
        Serial.println(portalCfg.SSID);
        ssid = portalCfg.SSID;
        Serial.println(portalCfg.pass);
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
