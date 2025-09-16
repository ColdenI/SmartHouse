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
