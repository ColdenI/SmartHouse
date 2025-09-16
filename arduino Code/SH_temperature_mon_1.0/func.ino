void tool_for_eeprom(int a, int b){
  for (int i = a; i < b; i++){
    writeString(i,"0");
  }
}


void debug(){
  //Serial.print(!digitalRead(SENSOR_PIN));
  Serial.print("flag = ");Serial.println(String(dht.readTemperature()));
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

  
  myTimer1 = millis();
}

void EEPROM_update(){
    

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
