void tool_for_eeprom(int a, int b){
  for (int i = a; i < b; i++){
    writeString(i,"0");
  }
}


void debug(){
  //Serial.print(!digitalRead(SENSOR_PIN));
  //Serial.print("flag = ");Serial.print(is_Flag);Serial.print("invert = ");Serial.print(is_Invert);Serial.print("Mode = ");Serial.print(Mode);Serial.print("   key = ");Serial.print(is_ON);Serial.print( "   delayKEY = ");Serial.print( delays );Serial.print( "   delayEEPROM = ");Serial.println(EEdel);
}

void sensor_tick(){
    if(S1.Mode == 1){
      if (butt_1.isSingle()){ 
        S1.is_ON =!S1.is_ON;
        digitalWrite(RELE_PIN_1, S1.is_ON); 
      }
    }
    if(S2.Mode == 1){
      if (butt_2.isSingle()){ 
        S2.is_ON =!S2.is_ON;
        digitalWrite(RELE_PIN_2, S2.is_ON); 
      }
    }
    if(S3.Mode == 1){
      if (butt_3.isSingle()){ 
        S3.is_ON =!S3.is_ON;
        digitalWrite(RELE_PIN_3, S3.is_ON); 
      }
    }
    
  
  if (butt_1.isDouble()) {
    S1.Mode=1;
    EEPROM_update();
     S1.myTimer1 = millis();
    tone(SPIC_PIN,1000,100);
  }
   if (butt_2.isDouble()) {
    S2.Mode=1;
    EEPROM_update();
     S2.myTimer1 = millis();
    tone(SPIC_PIN,1000,100);
  }
   if (butt_3.isDouble()) {
    S3.Mode=1;
    EEPROM_update();
     S3.myTimer1 = millis();
    tone(SPIC_PIN,1000,100);
  }

  
  if (butt_1.isTriple()){
    S1.Mode=2;
    EEPROM_update();
     S1.myTimer1 = millis();
    tone(SPIC_PIN,1000,100);
    delay(300);
    tone(SPIC_PIN,1000,100);
  }
  if (butt_2.isTriple()){
    S2.Mode=2;
    EEPROM_update();
     S2.myTimer1 = millis();
    tone(SPIC_PIN,1000,100);
    delay(300);
    tone(SPIC_PIN,1000,100);
  }
  if (butt_3.isTriple()){
    S3.Mode=2;
    EEPROM_update();
     S3.myTimer1 = millis();
    tone(SPIC_PIN,1000,100);
    delay(300);
    tone(SPIC_PIN,1000,100);
  }


  if(S1.Mode==2)
    if (millis() - S1.myTimer1 >= S1.delays) {   // ищем разницу (500 мс)
      S1.myTimer1 = millis();              // сброс таймера
      S1.is_ON =!S1.is_ON;
      digitalWrite(RELE_PIN_1, S1.is_ON);
    }
  if(S2.Mode==2)
    if (millis() - S2.myTimer1 >= S2.delays) {   // ищем разницу (500 мс)
      S2.myTimer1 = millis();              // сброс таймера
      S2.is_ON =!S2.is_ON;
      digitalWrite(RELE_PIN_2, S2.is_ON);
    }
  if(S3.Mode==2)
    if (millis() - S3.myTimer1 >= S3.delays) {   // ищем разницу (500 мс)
      S3.myTimer1 = millis();              // сброс таймера
      S3.is_ON =!S3.is_ON;
      digitalWrite(RELE_PIN_3, S3.is_ON);
    }

  butt_1.tick();
  butt_2.tick();
  butt_3.tick();
}


//SOUNDS

void SO_start(){
  tone(SPIC_PIN,1000,300);
  delay(300);
  tone(SPIC_PIN,300,300);
  delay(300);
  tone(SPIC_PIN,2000,300); 
}

void SO_conect(){
  tone(SPIC_PIN,2000,300);
  delay(300);
  tone(SPIC_PIN,300,300);
  delay(300);
  tone(SPIC_PIN,2000,300); 
  tone(SPIC_PIN,1000,300);
  delay(300);
  tone(SPIC_PIN,300,300);
  delay(300);
  tone(SPIC_PIN,2000,300); 
  delay(800);
  tone(SPIC_PIN,2000,200);
  delay(300);
  tone(SPIC_PIN,2000,200);
}

void SO_conect2(){
  tone(SPIC_PIN,300,100); 
  delay(300);
  tone(SPIC_PIN,200,200); 
  delay(700);
  
  tone(SPIC_PIN,1000,300); 
  tone(SPIC_PIN,700,300);
  delay(300);
  tone(SPIC_PIN,200,300);
  delay(300);
  tone(SPIC_PIN,1000,300); 
}



// EEPROM

void reader(){
  ssid = read_String(0);
  password = read_String(32);
  Serial.println(ssid);
  Serial.println(password);

  S1.is_ON = 1; 
  S2.is_ON = 1;
  S3.is_ON = 1; 
  
  S1.EEdel = 2;
  S2.EEdel = 2;
  S3.EEdel = 2;
  
  S1.Mode = 1;
  S2.Mode = 1;
  S3.Mode = 1;
  
  String str_;
 
  str_ = read_String(65);
  if (str_ == "1") S1.Mode = 1;
  else if (str_ == "2") S1.Mode = 2;

  str_ = read_String(66);
  if (str_ == "1") S2.Mode = 1;
  else if (str_ == "2") S2.Mode = 2;

  str_ = read_String(67);
  if (str_ == "1") S3.Mode = 1;
  else if (str_ == "2") S3.Mode = 2;

  
  digitalWrite(RELE_PIN_1, S1.is_ON);
  digitalWrite(RELE_PIN_2, S2.is_ON);
  digitalWrite(RELE_PIN_3, S3.is_ON);
  

  str_ = read_String(68);
  if (str_ == "1") S1.EEdel = 1;
  else if (str_ == "2") S1.EEdel = 2;
  else if (str_ == "3") S1.EEdel = 3;
  else if (str_ == "4") S1.EEdel = 4;
  else if (str_ == "5") S1.EEdel = 5;
  else if (str_ == "6") S1.EEdel = 6;
  else if (str_ == "7") S1.EEdel = 7;
  else if (str_ == "8") S1.EEdel = 8;
  else if (str_ == "9") S1.EEdel = 9;
  else if (str_ == "10") S1.EEdel = 10;
  else if (str_ == "11") S1.EEdel = 11;
  else if (str_ == "12") S1.EEdel = 12;

  switch(S1.EEdel){
    case 1: S1.delays=300000; break;
    case 2: S1.delays=600000; break;
    case 3: S1.delays=1800000; break;
    case 4: S1.delays=3600000; break;
    case 5: S1.delays=7200000; break;
    case 6: S1.delays=10800000; break;
    case 7: S1.delays=18000000; break;
    case 8: S1.delays=28800000; break;
    case 9: S1.delays=36000000; break;
    case 10: S1.delays=43200000; break;
    case 11: S1.delays=61200000; break;
    case 12: S1.delays=86400000; break;
  }



  str_ = read_String(70);
  if (str_ == "1") S2.EEdel = 1;
  else if (str_ == "2") S2.EEdel = 2;
  else if (str_ == "3") S2.EEdel = 3;
  else if (str_ == "4") S2.EEdel = 4;
  else if (str_ == "5") S2.EEdel = 5;
  else if (str_ == "6") S2.EEdel = 6;
  else if (str_ == "7") S2.EEdel = 7;
  else if (str_ == "8") S2.EEdel = 8;
  else if (str_ == "9") S2.EEdel = 9;
  else if (str_ == "10") S2.EEdel = 10;
  else if (str_ == "11") S2.EEdel = 11;
  else if (str_ == "12") S2.EEdel = 12;

  switch(S2.EEdel){
    case 1: S2.delays=300000; break;
    case 2: S2.delays=600000; break;
    case 3: S2.delays=1800000; break;
    case 4: S2.delays=3600000; break;
    case 5: S2.delays=7200000; break;
    case 6: S2.delays=10800000; break;
    case 7: S2.delays=18000000; break;
    case 8: S2.delays=28800000; break;
    case 9: S2.delays=36000000; break;
    case 10: S2.delays=43200000; break;
    case 11: S2.delays=61200000; break;
    case 12: S2.delays=86400000; break;
  }



  str_ = read_String(72);
  if (str_ == "1") S3.EEdel = 1;
  else if (str_ == "2") S3.EEdel = 2;
  else if (str_ == "3") S3.EEdel = 3;
  else if (str_ == "4") S3.EEdel = 4;
  else if (str_ == "5") S3.EEdel = 5;
  else if (str_ == "6") S3.EEdel = 6;
  else if (str_ == "7") S3.EEdel = 7;
  else if (str_ == "8") S3.EEdel = 8;
  else if (str_ == "9") S3.EEdel = 9;
  else if (str_ == "10") S3.EEdel = 10;
  else if (str_ == "11") S3.EEdel = 11;
  else if (str_ == "12") S3.EEdel = 12;

  switch(S3.EEdel){
    case 1: S3.delays=300000; break;
    case 2: S3.delays=600000; break;
    case 3: S3.delays=1800000; break;
    case 4: S3.delays=3600000; break;
    case 5: S3.delays=7200000; break;
    case 6: S3.delays=10800000; break;
    case 7: S3.delays=18000000; break;
    case 8: S3.delays=28800000; break;
    case 9: S3.delays=36000000; break;
    case 10: S3.delays=43200000; break;
    case 11: S3.delays=61200000; break;
    case 12: S3.delays=86400000; break;
  }




  S1.myTimer1 = millis();
  S2.myTimer1 = millis();
  S3.myTimer1 = millis();
}

void EEPROM_update(){
    
  String str_;
  int inn = 0;

  str_ = read_String(65);
  if (str_ == "1") inn = 1;
  else if (str_ == "2") inn = 2;
  
  if (inn != S1.Mode){
    if (S1.Mode == 1) writeString(65, "1");
    else if (S1.Mode == 2) writeString(65, "2");
  }


  str_ = read_String(66);
  if (str_ == "1") inn = 1;
  else if (str_ == "2") inn = 2;
  
  if (inn != S2.Mode){
    if (S2.Mode == 1) writeString(66, "1");
    else if (S2.Mode == 2) writeString(66, "2");
  }


  str_ = read_String(67);
  if (str_ == "1") inn = 1;
  else if (str_ == "2") inn = 2;
  
  if (inn != S3.Mode){
    if (S3.Mode == 1) writeString(67, "1");
    else if (S3.Mode == 2) writeString(67, "2");
  }



  
  inn = 0;
  str_ = read_String(68);
  if (str_ == "1") inn = 1;
  else if (str_ == "2") inn = 2;
  else if (str_ == "3") inn = 3;
  else if (str_ == "4") inn = 4;
  else if (str_ == "5") inn = 5;
  else if (str_ == "6") inn = 6;
  else if (str_ == "7") inn = 7;
  else if (str_ == "8") inn = 8;
  else if (str_ == "9") inn = 9;
  else if (str_ == "10") inn = 10;
  else if (str_ == "11") inn = 11;
  else if (str_ == "12") inn = 12;

  if (inn != S1.EEdel){
    switch(S1.EEdel){
      case 1: writeString(68, "1"); break;
      case 2: writeString(68, "2"); break;
      case 3: writeString(68, "3"); break;
      case 4: writeString(68, "4"); break;
      case 5: writeString(68, "5"); break;
      case 6: writeString(68, "6"); break;
      case 7: writeString(68, "7"); break;
      case 8: writeString(68, "8"); break;
      case 9: writeString(68, "9"); break;
      case 10: writeString(68, "10"); break;
      case 11: writeString(68, "11"); break;
      case 12: writeString(68, "12"); break;
    }
  }


  inn = 0;
  str_ = read_String(70);
  if (str_ == "1") inn = 1;
  else if (str_ == "2") inn = 2;
  else if (str_ == "3") inn = 3;
  else if (str_ == "4") inn = 4;
  else if (str_ == "5") inn = 5;
  else if (str_ == "6") inn = 6;
  else if (str_ == "7") inn = 7;
  else if (str_ == "8") inn = 8;
  else if (str_ == "9") inn = 9;
  else if (str_ == "10") inn = 10;
  else if (str_ == "11") inn = 11;
  else if (str_ == "12") inn = 12;

  if (inn != S2.EEdel){
    switch(S2.EEdel){
      case 1: writeString(70, "1"); break;
      case 2: writeString(70, "2"); break;
      case 3: writeString(70, "3"); break;
      case 4: writeString(70, "4"); break;
      case 5: writeString(70, "5"); break;
      case 6: writeString(70, "6"); break;
      case 7: writeString(70, "7"); break;
      case 8: writeString(70, "8"); break;
      case 9: writeString(70, "9"); break;
      case 10: writeString(70, "10"); break;
      case 11: writeString(70, "11"); break;
      case 12: writeString(70, "12"); break;
    }
  }


  
  inn = 0;
  str_ = read_String(72);
  if (str_ == "1") inn = 1;
  else if (str_ == "2") inn = 2;
  else if (str_ == "3") inn = 3;
  else if (str_ == "4") inn = 4;
  else if (str_ == "5") inn = 5;
  else if (str_ == "6") inn = 6;
  else if (str_ == "7") inn = 7;
  else if (str_ == "8") inn = 8;
  else if (str_ == "9") inn = 9;
  else if (str_ == "10") inn = 10;
  else if (str_ == "11") inn = 11;
  else if (str_ == "12") inn = 12;

  if (inn != S3.EEdel){
    switch(S3.EEdel){
      case 1: writeString(72, "1"); break;
      case 2: writeString(72, "2"); break;
      case 3: writeString(72, "3"); break;
      case 4: writeString(72, "4"); break;
      case 5: writeString(72, "5"); break;
      case 6: writeString(72, "6"); break;
      case 7: writeString(72, "7"); break;
      case 8: writeString(72, "8"); break;
      case 9: writeString(72, "9"); break;
      case 10: writeString(72, "10"); break;
      case 11: writeString(72, "11"); break;
      case 12: writeString(72, "12"); break;
    }
  }

}


void writeString(char add,String data)
{
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
  EEPROM.commit();
}


String read_String(char add)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}
