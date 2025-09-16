void WIFIinit(){
  WiFi.mode(WIFI_STA);

  // Подключаемся к сети WiFi
  Serial.print("\n\nConnecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Ожидание подключения
  int iii = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1500);
    Serial.print(".");
    tone(SPIC_PIN,500,100);
    iii++;
    if (iii >= connection_attempts) break;
  }
  
  if (WiFi.status()== WL_CONNECTED){
    SO_conect();
    Serial.println("\nWiFi connected");
    // Запуск сервера
    HTTP.begin();
    Serial.println("Server started");
    // Вывод полученного IP адреса
    local_ip = WiFi.localIP().toString().c_str(); 
    Serial.println(WiFi.localIP());
  }
  else {
    writeString(70, "1");
    delay(100);
    ESP.restart();
  }


}
 
void Config_mode(){
  Serial.println("Config mode");
  SO_conect2();
 
  WiFi.mode(WIFI_AP);
  WiFi.softAP("SmartHouse UGRNy" + splitCommand(S_code, '-', 1));
  HTTP.begin();
  writeString(70, "0");
}
