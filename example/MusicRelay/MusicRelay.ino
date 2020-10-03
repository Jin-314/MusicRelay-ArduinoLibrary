int pin[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
String eventType = "";
static int buff[20] = {0};
int parts[10] = {0};
int index = 0;
int cnt1 = 0;
int cnt2 = 0;
char inByte = 0;
unsigned long pretime[10] = {0};
void setup() {
  //Serial Initialize  
  Serial.begin(2000000);
  for(int i = 0; i < 10; i++){
    pinMode(pin[i], OUTPUT);
  }
}

void loop() {
  unsigned long mtime = micros();
  char message[5];
  int partIdx = CountParts();
  for(int i = 0; i < partIdx; i++){
    if(parts[i] > 0){
      if(mtime - pretime[i] < (parts[i] / 2)){
        digitalWrite(pin[i], HIGH);
      }else if(mtime - pretime[i] < parts[i]){
        digitalWrite(pin[i], LOW);
      }else{
        pretime[i] = mtime;
      }      
    }
  }
  while(Serial.available()){
    
    inByte = Serial.read();
      
    if(inByte != 44){
      if(cnt2 == 1){
        message[cnt1] = inByte;
      }else{
        buff[cnt1] = inByte - '0';
      }
      cnt1++;
    }else{
      switch(cnt2){
        case 0:
          index = decorder();
          cnt2++;
          break;
        case 1:
          message[cnt1] = '\0';
          eventType = message;
          if(eventType == "OFF"){
            cnt2 = 0;
            parts[index - 1] = 0;
          }else{
            cnt2++;
          }
          break;
        case 2:
          parts[index - 1] = decorder();
          cnt2 = 0;
          break;
      }
      cnt1 = 0;
    }
  }
   //delayMicroseconds(50);
}

//decode ascii to number
int decorder(){
  
  int result = 0;
  
  for(int i = 0; i < cnt1; i++){
    int exponent = (cnt1 - 1) - i;
    double tmp = pow(10, exponent);
    result += buff[i] * tmp;
    buff[i] = 0;
  }
  
  return result;
}

int CountParts(){
  int i;
  for(i = 0; i < 10; i++){
    if(!parts[i]){
      if(i < 9){
        for(int j = 1; j < 10 - i; j++){
          if(parts[i + j] == 0 && j + 1 == 9 - i){
            return i;
          }
          if(parts[i + j] != 0){
            break;
          }
        }
      }else{
        return i;
      }
    }
  }
  return 0;
}
