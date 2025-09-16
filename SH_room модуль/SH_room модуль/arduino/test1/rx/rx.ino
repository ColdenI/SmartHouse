void setup(){
  Serial.begin(115200);

pinMode(13,OUTPUT);
  
}



void loop(){
  if(Serial.available() > 1){
    char a = Serial.read();
    int v = Serial.parseInt();

    switch(a){
      case 'a':
        digitalWrite(13,v);
      break;
    }
  }
}
