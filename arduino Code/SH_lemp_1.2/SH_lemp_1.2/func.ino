void alarm_clock(){
  schedule.tick();
  
  if (millis() - TimerAlarmClock >= 500 && schedule.isOn) {  
      TimerAlarmClock = millis();     
      
      tone(SPIC_PIN,2000,100);
      schedule.ni++;
      schedule.nii++;
      
      if(schedule.nii >= 8){
        if(schedule.isInvLamp) set_Lemp(!is_lemp);
        schedule.nii = 0;
      }
      if(schedule.ni >= 240){
        schedule.Destroy();
      }
  }

  if (btA.isPress() && IS_RADIO_P){
    schedule.Destroy();
    if(IS_DEBUG)Serial.println("A");
  }
}



void radio_tick(){
  btA.tick();
  btB.tick();
  btC.tick();
  btD.tick();



  
  if (btA.isPress()){
    set_Lemp(!is_lemp);
    if(IS_DEBUG)Serial.println("A");
  }

  if (btB.isPress()){
    if(IS_DEBUG)Serial.println("B");
    if(Mode_l == 0){
      set_Mode(random(1,30));
    }else{
      set_Mode(0);
      isAuto = 0;
    }
  }

  if (btC.isPress()){
    if(IS_DEBUG)Serial.println("C");
    set_Mode(random(1,30));

      if (btD.isPress()){
     Restart();
  }
  }

  if (btD.isPress()){
    if(IS_DEBUG)Serial.println("D");
      isAuto = 0;
      set_Mode(0);
      set_Lemp(0);
  }
  
}

void tool_for_eeprom(int a, int b){
  for (int i = a; i < b; i++){
    writeString(i,"0");
  }
}

void auto_off_tick(){
  if(isAutoOff){
    if (millis() - AutoOff_Timer >= AutoOff_Time) {  
      // AutoOff_Timer = millis();
      isAuto = 0;     
      set_Mode(0);
      set_Lemp(0);
      isAutoOff = 0;
    }
  }
}

void auto_tick(){
  if(isAuto && Mode_l != 0){
    if (millis() - AutoL_Timer >= Auto_Time) {  
      AutoL_Timer = millis();     
      Serial.print(random(1, 30));
    }   
  }
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


void set_Mode(int val){
  Mode_l = val;
  isAuto = 0;
  Serial.print(val);
}

void set_Lemp(bool val){
  is_lemp = val;
  digitalWrite(RELE_PIN, is_lemp);
  
}


// EEPROM

void reader(){
  ssid = read_String(0);
  password = read_String(32);
  if(IS_DEBUG)Serial.println(ssid);
  if(IS_DEBUG)Serial.println(password);

  is_lemp = 0;
  Mode_l = 2;
  isAuto = 0;
  
  String str_;
 
  str_ = read_String(65);
  if (str_ == "0") isAuto = 0;
  else if (str_ == "1") isAuto = 1;

  str_ = read_String(66);
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

}

void EEPROM_update(){
    
  String str_;
  int inn = 0;

  str_ = read_String(65);
  if (str_ == "0") inn = 0;
  else if (str_ == "1") inn = 1;

  
  if (inn != isAuto){
    if (isAuto == 0) writeString(65, "0");
    else if (isAuto == 1) writeString(65, "1");

  }

  inn = 0;
  str_ = read_String(66);
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
      case 1: writeString(66, "1"); break;
      case 2: writeString(66, "2"); break;
      case 3: writeString(66, "3"); break;
      case 4: writeString(66, "4"); break;
      case 5: writeString(66, "5"); break;
      case 6: writeString(66, "6"); break;
      case 7: writeString(66, "7"); break;
      case 8: writeString(66, "8"); break;
      case 9: writeString(66, "9"); break;
      case 10: writeString(66, "10"); break;
      case 11: writeString(66, "11"); break;
      case 12: writeString(66, "12"); break;
      case 13: writeString(66, "13"); break;
      case 14: writeString(66, "14"); break;
      case 15: writeString(66, "15"); break;
      case 16: writeString(66, "16"); break;
      case 17: writeString(66, "17"); break;
      case 18: writeString(66, "18"); break;
      case 19: writeString(66, "19"); break;
      case 20: writeString(66, "20"); break;
      case 21: writeString(66, "21"); break;
      case 22: writeString(66, "22"); break;
      case 23: writeString(66, "23"); break;
      case 24: writeString(66, "24"); break;
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
