#include <RelayController.h>

//Relay instance
int pin[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
Relay Relay(pin, 10);                               

static int buff[20] = {0};
int partNum = 0;
int tmp = 0;
int ompu =0;
int parts[10] = {0};
int counter1 = 0;
int counter2 = 0;
int inByte = 0;

void setup() {
  //Serial Initialize  
  Serial.begin(115200);
}

void loop() {
  while(Serial.available()){
    
    inByte = Serial.read();
      
    if(inByte != 44){
      
      buff[counter1] = inByte - '0';
      
      counter1++;
      
    }else{
      switch(counter2){
        case 0:
          partNum = decorder();
          counter2++;
          break;
        case 1:
          tmp = decorder();
          counter2++;
          break;
        case 2:
          ompu = decorder();
          counter2++;
          break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
          parts[counter2 - 3] = decorder();
          //Serial.println(parts[0]);
          counter2++;
          break;
      }
      counter1 = 0;
    }
    delayMicroseconds(100);
  }
  
  //Relay Attach
  switch(partNum - 2){
    case 1:
      Relay.sing(parts[0], ompu, tmp);
      break;
    case 2:
      Relay.sing(parts[0], parts[1], ompu, tmp);
      break;
    case 4:
      Relay.sing(parts[0], parts[1], parts[2], parts[3], ompu, tmp);
      break;
    case 5:
      Relay.sing(parts[0], parts[1], parts[2], parts[3], parts[4], ompu, tmp);
      break;
    case 10:
      Relay.sing(parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6], parts[7], parts[8], parts[9], ompu, tmp);
      break;
   }
   counter2 = 0;
   for(int i = 0; i < 10; i++){
     parts[i] = 0;
   }
   partNum = 0;
   tmp = 0;
   ompu = 0;
   counter2 = 0;
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
