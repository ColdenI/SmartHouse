
void button_tick(){
  button.tick();

  if(button.isSingle()){
    if(Mode != 0) Mode = 0;
    else Mode = 2;
  }

  if(button.isDouble()){
    if(Mode == 1)Mode = 2;
    if(Mode == 2)Mode = 3;
    if(Mode == 3){
      Mode = 1;
      set_l(random(1, 255), random(1, 255), random(1, 255));
    }
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
      isAutoOff = 0;
      set_l(0,0,0);
      Mode = 0;
    }
  }
}

void auto_tick(){
  if(isAuto && Mode != 0){
    if (millis() - AutoL_Timer >= Auto_Time) {  
      AutoL_Timer = millis();     
      Mode = random(2, 3);
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


// EEPROM

void reader(){
  ssid = read_String(0);
  password = read_String(32);
  if(IS_DEBUG)Serial.println(ssid);
  if(IS_DEBUG)Serial.println(password);

  Mode = 0;
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







int bri(int br){
  switch(br){
    case 1: return 10;   break;
    case 2: return 9;   break;
    case 3: return 8;   break;
    case 4: return 7;   break;
    case 5: return 6;   break;
    case 6: return 5;   break;
    case 7: return 4;   break;
    case 8: return 3;   break;
    case 9: return 2;   break;
    case 10: return 1;   break;
  }
}

void set_l(int R, int G, int B){
  if(R == 0 && G == 0 && B == 0) Mode = 0;
  int r = R / bri(brig);
  int g = G / bri(brig);
  int b = B / bri(brig);
  analogWrite(R_PIN, r);
  analogWrite(G_PIN, g);
  analogWrite(B_PIN, b);
}


void gradient_tick(){
  if ( millis() - timer_grad >= bri(speed) * 2){
    timer_grad = millis();
    gradient_i += 1;
    if(gradient_i > 1530) gradient_i = 0;
    colorWheel(gradient_i);
  }
}

void jump_tick(){
  if ( millis() - timer_jump >= bri(speed) * 100){
    timer_jump = millis();
    jump_i += random(200, 600);
    if(jump_i > 1530) jump_i = 1;
    colorWheel(jump_i);
  }
}

void colorWheel(int color) {
  // включает цвет по цветовому колесу, принимает 0-1530
  byte _r, _g, _b;
  if (color <= 255) {                       // красный макс, зелёный растёт
    _r = 255;
    _g = color;
    _b = 0;
  }
  else if (color > 255 && color <= 510) {   // зелёный макс, падает красный
    _r = 510 - color;
    _g = 255;
    _b = 0;
  }
  else if (color > 510 && color <= 765) {   // зелёный макс, растёт синий
    _r = 0;
    _g = 255;
    _b = color - 510;
  }
  else if (color > 765 && color <= 1020) {  // синий макс, падает зелёный
    _r = 0;
    _g = 1020 - color;
    _b = 255;
  }
  else if (color > 1020 && color <= 1275) {   // синий макс, растёт красный
    _r = color - 1020;
    _g = 0;
    _b = 255;
  }
  else if (color > 1275 && color <= 1530) { // красный макс, падает синий
    _r = 255;
    _g = 0;
    _b = 1530 - color;
  }

  set_l(255 - _r, 255 - _g, 255 - _b);
}


void mode_tick(){
  switch(Mode){
    case 1: set_l(color_R, color_G, color_B); break;
    case 2: gradient_tick(); break;
    case 3: jump_tick(); break;
  }
}
