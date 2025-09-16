void tool_for_eeprom(int a, int b){
  for (int i = a; i < b; i++){
    writeString(i,"0");
  }
}

bool isPressButton(){
  relay.Sensor.tick();

  return relay.Sensor.isPress();
}

bool isHoldButton(){
  relay.Sensor.tick();

  return relay.Sensor.isHold();
}



void debug(){
  //Serial.print(!digitalRead(SENSOR_PIN));
  Serial.print("flag = ");Serial.print(relay.is_Flag);Serial.print("invert = ");Serial.print(relay.is_Invert);Serial.print("Mode = ");Serial.print(relay.Mode);Serial.print("   key = ");Serial.print(relay.is_ON);Serial.print( "   delayKEY = ");Serial.print( relay.delays );Serial.print( "   delayEEPROM = ");Serial.println(relay.EEdel);
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

  relay.is_ON = 1;  
  relay.EEdel = 2;
  relay.Mode = 1;
  
  String str_;
 
  str_ = read_String(65);
  if (str_ == "1") relay.Mode = 1;
  else if (str_ == "2") relay.Mode = 2;
  else if (str_ == "3") relay.Mode = 3;
  else if (str_ == "4") relay.Mode = 1;  // !!!!!!!!!

  str_ = read_String(66);
  if (str_ == "0") relay.is_ON = 0;
  else if (str_ == "1") relay.is_ON = 1;
  relay.setON(relay.is_ON);

  str_ = read_String(67);
  if (str_ == "1") relay.EEdel = 1;
  else if (str_ == "2") relay.EEdel = 2;
  else if (str_ == "3") relay.EEdel = 3;
  else if (str_ == "4") relay.EEdel = 4;
  else if (str_ == "5") relay.EEdel = 5;
  else if (str_ == "6") relay.EEdel = 6;
  else if (str_ == "7") relay.EEdel = 7;
  else if (str_ == "8") relay.EEdel = 8;
  else if (str_ == "9") relay.EEdel = 9;
  else if (str_ == "10") relay.EEdel = 10;
  else if (str_ == "11") relay.EEdel = 11;
  else if (str_ == "12") relay.EEdel = 12;

  switch(relay.EEdel){
    case 1: relay.delays=300000; break;
    case 2: relay.delays=600000; break;
    case 3: relay.delays=1800000; break;
    case 4: relay.delays=3600000; break;
    case 5: relay.delays=7200000; break;
    case 6: relay.delays=10800000; break;
    case 7: relay.delays=18000000; break;
    case 8: relay.delays=28800000; break;
    case 9: relay.delays=36000000; break;
    case 10: relay.delays=43200000; break;
    case 11: relay.delays=61200000; break;
    case 12: relay.delays=86400000; break;
  }

  str_ = read_String(68);
  if (str_ == "0") relay.is_Flag = 0;
  else if (str_ == "1") relay.is_Flag = 1;

  str_ = read_String(69);
  if (str_ == "0") relay.is_Invert = 0;
  else if (str_ == "1") relay.is_Invert = 1;


  str_ = read_String(70);
  if (str_ == "1") time_Zone = 1;
  else if (str_ == "2") time_Zone = 2;
  else if (str_ == "3") time_Zone = 3;
  else if (str_ == "4") time_Zone = 4;
  else if (str_ == "5") time_Zone = 5;
  else if (str_ == "6") time_Zone = 6;
  else if (str_ == "7") time_Zone = 7;
  else if (str_ == "8") time_Zone = 8;
  else if (str_ == "9") time_Zone = 9;
  else if (str_ == "10") time_Zone = 10;
  else if (str_ == "11") time_Zone = 11;
  else if (str_ == "12") time_Zone = 12;
  else if (str_ == "13") time_Zone = 13;
  else if (str_ == "14") time_Zone = 14;
  else if (str_ == "15") time_Zone = 15;
  else if (str_ == "16") time_Zone = 16;
  else if (str_ == "17") time_Zone = 17;
  else if (str_ == "18") time_Zone = 18;
  else if (str_ == "19") time_Zone = 19;
  else if (str_ == "20") time_Zone = 20;
  else if (str_ == "21") time_Zone = 21;
  else if (str_ == "22") time_Zone = 22;
  else if (str_ == "23") time_Zone = 23;
  else if (str_ == "24") time_Zone = 24;

  
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
  relay.myTimer1 = millis();
}

void EEPROM_update(){
    
  String str_;
  int inn = 0;

  str_ = read_String(65);
  if (str_ == "1") inn = 1;
  else if (str_ == "2") inn = 2;
  else if (str_ == "3") inn = 3;
  else if (str_ == "4") inn = 4;
  
  if (inn != relay.Mode){
    if (relay.Mode == 1) writeString(65, "1");
    else if (relay.Mode == 2) writeString(65, "2");
    else if (relay.Mode == 3) writeString(65, "3");
    else if (relay.Mode == 4) writeString(65, "4");
  }

  inn = 0;
  str_ = read_String(66);
  if (str_ == "0") inn = 0;
  else if (str_ == "1") inn = 1;

  if (inn != relay.is_ON){
    if (relay.is_ON == 0) writeString(66, "0");
    else if (relay.is_ON == 1) writeString(66, "1");
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

  if (inn != relay.EEdel){
    switch(relay.EEdel){
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
    if (relay.is_Flag == 0) writeString(68, "0");
    if (relay.is_Flag == 1) writeString(68, "1");
  //}

  inn = 0;
  str_ = read_String(69);
  if (str_ == "0") relay.is_Invert = 0;
  else if (str_ == "1") relay.is_Invert = 1;

  if (inn != relay.is_Invert){
    if (relay.is_Invert == 0) writeString(69, "0");
    if (relay.is_Invert == 1) writeString(69, "1");
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
  else if (str_ == "13") inn = 13;
  else if (str_ == "14") inn = 14;
  else if (str_ == "15") inn = 15;
  else if (str_ == "16") inn = 16;
  else if (str_ == "17") inn = 17;
  else if (str_ == "18") inn = 18;
  else if (str_ == "19") inn = 19;
  else if (str_ == "20") inn = 20;
  else if (str_ == "21") inn = 21;
  else if (str_ == "22") inn = 22;
  else if (str_ == "23") inn = 23;
  else if (str_ == "24") inn = 24;
  

  
  if (inn != time_Zone){
    switch(time_Zone){
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
      case 13: writeString(70, "13"); break;
      case 14: writeString(70, "14"); break;
      case 15: writeString(70, "15"); break;
      case 16: writeString(70, "16"); break;
      case 17: writeString(70, "17"); break;
      case 18: writeString(70, "18"); break;
      case 19: writeString(70, "19"); break;
      case 20: writeString(70, "20"); break;
      case 21: writeString(70, "21"); break;
      case 22: writeString(70, "22"); break;
      case 23: writeString(70, "23"); break;
      case 24: writeString(70, "24"); break;
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
