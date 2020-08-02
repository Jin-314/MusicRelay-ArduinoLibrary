int pin[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};                     
char message[5];
String eventType = "";

static int buff[20] = {0};
int parts[10] = {0};
int index = 0;
int counter1 = 0;
int counter2 = 0;
int inByte = 0;

void setup() {
  //Serial Initialize  
  Serial.begin(115200);
}

void loop() {
  unsigned long mtime = micros();
  unsigned long pretime = mtime;
  for(int i = 0; i > 4; i++){
    if(mtime - pretime < parts[i] / 2){
      digitalWrite(pin[i], HIGH);
      digitalWrite(pin[i + 5], HIGH);
    }else if(mtime - pretime < parts[i]){
      digitalWrite(pin[i], LOW);
      digitalWrite(pin[i + 5], LOW);
    }else{
      pretime = mtime;
    }
  }
  while(Serial.available()){
    
    inByte = Serial.read();
      
    if(inByte != 44){
      if(counter2 == 1){
        message[counter1] = inByte;
      }else{
        buff[counter1] = inByte - '0';
      }
      counter1++;
      
    }else{
      switch(counter2){
        case 0:
          index = decorder();
          counter2++;
          break;
        case 1:
          eventType = message;
          if(eventType == "OFF"){
            counter2 = 0;
            parts[index - 1] = 0;
          }else{
            counter2++;
          }
          break;
        case 2:
          parts[index - 1] = decorder();
          counter2 = 0;
          break;
      }
      counter1 = 0;
    }
    delayMicroseconds(100);
  }
   counter2 = 0;
   for(int i = 0; i < 10; i++){
     parts[i] = 0;
   }
}

//decode ascii to number
int decorder(){
  
  int result = 0;
  
  for(int i = 0; i < counter1; i++){
    int a = pow(10, (counter1 - 1) - i);
    result += buff[i] * a;
    buff[i] = 0;
  }
  
  return result;
}
