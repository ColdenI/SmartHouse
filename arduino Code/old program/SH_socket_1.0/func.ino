

void tool_for_eeprom(int a, int b){
  for (int i = a; i < b; i++){
    writeString(i,"0");
  }
}

bool M_FLAG=0;
void modul(){
  if(is_Flag == 1){
    butt1.tick();
    if(butt1.isClick()){
      is_ON =!is_ON;
      digitalWrite(RELE_PIN, is_ON);     
    }

  }else{
     is_ON = digitalRead(MODUL_PIN);
     if (is_Invert) is_ON = !is_ON;
     digitalWrite(RELE_PIN, is_ON);
  }
}


void debug(){
  //Serial.print(!digitalRead(SENSOR_PIN));
  Serial.print("flag = ");Serial.print(is_Flag);Serial.print("invert = ");Serial.print(is_Invert);Serial.print("Mode = ");Serial.print(Mode);Serial.print("   key = ");Serial.print(is_ON);Serial.print( "   delayKEY = ");Serial.print( delays );Serial.print( "   delayEEPROM = ");Serial.println(EEdel);
}

void sensor_tick(){
    if(Mode==1){
      if (butt.isSingle()){ 
        is_ON =!is_ON;
        digitalWrite(RELE_PIN, is_ON); 
    }}
  
  if (butt.isDouble()) {
    Mode=1;
    EEPROM_update();
     myTimer1 = millis();
    tone(SPIC_PIN,1000,100);
  }
  
  if (butt.isTriple()){
    Mode=2;
    EEPROM_update();
     myTimer1 = millis();
    tone(SPIC_PIN,1000,100);
    delay(300);
    tone(SPIC_PIN,1000,100);
  }


 if (butt.hasClicks()){
    if (butt.getClicks() == 4){
        Mode = 3; 
        EEPROM_update();      
        myTimer1 = millis();
        tone(SPIC_PIN,1000,100);
        delay(300);
        tone(SPIC_PIN,1000,100);
        delay(300);
        tone(SPIC_PIN,1000,100);
    }

 }

  if(Mode==2)
    if (millis() - myTimer1 >= delays) {   // ищем разницу (500 мс)
      myTimer1 = millis();              // сброс таймера
      is_ON =!is_ON;
      digitalWrite(RELE_PIN, is_ON);
    }


     butt.tick();
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

  is_ON = 1;  
  EEdel = 2;
  Mode = 1;
  
  String str_;
 
  str_ = read_String(65);
  if (str_ == "1") Mode = 1;
  else if (str_ == "2") Mode = 2;
  else if (str_ == "3") Mode = 3;

  str_ = read_String(66);
  if (str_ == "0") is_ON = 0;
  else if (str_ == "1") is_ON = 1;
  digitalWrite(RELE_PIN, is_ON);

  str_ = read_String(67);
  if (str_ == "1") EEdel = 1;
  else if (str_ == "2") EEdel = 2;
  else if (str_ == "3") EEdel = 3;
  else if (str_ == "4") EEdel = 4;
  else if (str_ == "5") EEdel = 5;
  else if (str_ == "6") EEdel = 6;
  else if (str_ == "7") EEdel = 7;
  else if (str_ == "8") EEdel = 8;
  else if (str_ == "9") EEdel = 9;
  else if (str_ == "10") EEdel = 10;
  else if (str_ == "11") EEdel = 11;
  else if (str_ == "12") EEdel = 12;

  switch(EEdel){
    case 1: delays=300000; break;
    case 2: delays=600000; break;
    case 3: delays=1800000; break;
    case 4: delays=3600000; break;
    case 5: delays=7200000; break;
    case 6: delays=10800000; break;
    case 7: delays=18000000; break;
    case 8: delays=28800000; break;
    case 9: delays=36000000; break;
    case 10: delays=43200000; break;
    case 11: delays=61200000; break;
    case 12: delays=86400000; break;
  }

  str_ = read_String(68);
  if (str_ == "0") is_Flag = 0;
  else if (str_ == "1") is_Flag = 1;

  str_ = read_String(69);
  if (str_ == "0") is_Invert = 0;
  else if (str_ == "1") is_Invert = 1;

  
  /*
  switch(EEdel){
    case 1: delays=300000; break;
    case 2: delays=600000; break;
    case 3: delays=1800000; break;
    case 4: delays=3600000; break;
    case 5: delays=7200000; break;
    case 6: delays=10800000; break;
    case 7: delays=18000000; break;
    case 8: delays=28800000; break;
    case 9: delays=36000000; break;
    case 10: delays=43200000; break;
    case 11: delays=61200000; break;
    case 12: delays=86400000; break;
  }

  */
  myTimer1 = millis();
}

void EEPROM_update(){
    
  String str_;
  int inn = 0;

  str_ = read_String(65);
  if (str_ == "1") inn = 1;
  else if (str_ == "2") inn = 2;
  else if (str_ == "3") inn = 3;
  
  if (inn != Mode){
    if (Mode == 1) writeString(65, "1");
    else if (Mode == 2) writeString(65, "2");
    else if (Mode == 3) writeString(65, "3");
  }

  inn = 0;
  str_ = read_String(66);
  if (str_ == "0") inn = 0;
  else if (str_ == "1") inn = 1;

  if (inn != is_ON){
    if (is_ON == 0) writeString(66, "0");
    else if (is_ON == 1) writeString(66, "1");
  }
  
  inn = 0;
  str_ = read_String(67);
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

  if (inn != EEdel){
    switch(EEdel){
      case 1: writeString(67, "1"); break;
      case 2: writeString(67, "2"); break;
      case 3: writeString(67, "3"); break;
      case 4: writeString(67, "4"); break;
      case 5: writeString(67, "5"); break;
      case 6: writeString(67, "6"); break;
      case 7: writeString(67, "7"); break;
      case 8: writeString(67, "8"); break;
      case 9: writeString(67, "9"); break;
      case 10: writeString(67, "10"); break;
      case 11: writeString(67, "11"); break;
      case 12: writeString(67, "12"); break;
    }
  }

  
  inn = 0;
  str_ = read_String(68);
  if (str_ == "0") inn = 0;
  else if (str_ == "1") inn = 1;

  //if (inn != is_Flag){
    if (is_Flag == 0) writeString(68, "0");
    if (is_Flag == 1) writeString(68, "1");
  //}

  inn = 0;
  str_ = read_String(69);
  if (str_ == "0") is_Invert = 0;
  else if (str_ == "1") is_Invert = 1;

  if (inn != is_Invert){
    if (is_Invert == 0) writeString(69, "0");
    if (is_Invert == 1) writeString(69, "1");
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
