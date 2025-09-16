void tool_for_eeprom(int a, int b){
  for (int i = a; i < b; i++){
    writeString(i,"0");
  }
}


void debug(){

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
void EEPROM_Clear(){
  Serial.println("EEPROM CLEAR! - RUN");
  tool_for_eeprom(0, 170);
      writeString(0, "Wi-Fi");
      writeString(32, "12345678");
      writeString(64, "0");
      writeString(70, "0");
      //writeString(100, "admin");
      //writeString(132, "admin");
      
  Serial.println("EEPROM CLEAR! - END & RESTART");
  //ESP.restart();
}

void EEPROM_Read(){
  Serial.println("EEPROM READ - RUN");
  ssid = read_String(0);
  password = read_String(32);
  connection_attempts = read_String(64).toInt();
  //admin_login = read_String(100);
  //admin_password = read_String(132);

  Serial.println("EEPROM READ - END");
  myTimer1 = millis();
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

String splitCommand(String text, char splitChar, int index_) {
    int splitCount = countSplitCharacters(text, splitChar);
    String returnValue[splitCount];
    int index = -1;
    int index2;

    for(int i = 0; i < splitCount - 1; i++) {
        index = text.indexOf(splitChar, index + 1);
        index2 = text.indexOf(splitChar, index + 1);

        if(index2 < 0) index2 = text.length() - 1;
        returnValue[i] = text.substring(index, index2);
    }

    return returnValue[index_];
}
int countSplitCharacters(String text, char splitChar) {
    int returnValue = 0;
    int index = -1;

    while (index > -1) {
        index = text.indexOf(splitChar, index + 1);

        if(index > -1) returnValue+=1;
    }

    return returnValue;
}
