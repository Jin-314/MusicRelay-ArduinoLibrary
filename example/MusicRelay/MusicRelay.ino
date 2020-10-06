int pin[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
static int buff[20] = {0};
typedef struct {
  int period;
  unsigned long mtime;
  unsigned long pretime;
  double duty;
  bool flug;
} partData;
partData parts[10] = {0, 0, 0, 0, false};
int index = 0;
int cnt1 = 0;
int cnt2 = 0;
signed char inByte = 0;

void setup() {
  //Serial Initialize  
  Serial.begin(2000000);
  //TIMSK0= 0;
  for(int i = 0; i < 10; i++){
    pinMode(pin[i], OUTPUT);
  }
}

void loop() {
  int partIdx = CountParts();
  //同時に鳴らすパートの数分繰り返す
  for(int i = 0; i < partIdx; i++){
    if(parts[i].period > 0){
      parts[i].mtime = micros();
      //各パートごとに鳴らすか鳴らさないか判定
      if(!parts[i].flug && 
            parts[i].mtime - parts[i].pretime < (double)parts[i].period * (parts[i].duty / 100)){
        for(int j = 0; j * partIdx < 10; j++){
          if(i + j * partIdx < 8)
            PORTD = _BV(i + j * partIdx);
          else
            PORTB = _BV(i + j * partIdx);
        }
        parts[i].flug = true;
      }else if(parts[i].flug && 
            parts[i].mtime - parts[i].pretime > (double)parts[i].period * (parts[i].duty / 100)){
        for(int j = 0; j * partIdx < 10; j++){
          if(i + j * partIdx < 8)
            PORTD = ~_BV(i + j * partIdx);
          else
            PORTB = ~_BV(i + j * partIdx);
        }
        parts[i].flug = false;
      }else if(parts[i].mtime - parts[i].pretime > parts[i].period){
        parts[i].pretime = parts[i].mtime;
      }      
    }
  }
}

void serialEvent(){
  String eventType = "";
  char message[5];
  //シリアルに音階の周期が送られてきたら適宜変更
  while((inByte = Serial.read()) != -1){
    
    if(inByte != 44){
      if(cnt2 == 1){
        message[cnt1] = inByte;
      }else{
        buff[cnt1] = inByte - '0';
      }
      cnt1++;
    }else{
      switch(cnt2){
        case 0:                   //First data is index
          index = decorder();
          cnt2++;
          break;
        case 1:                   //The next data is kind of Events
          message[cnt1] = '\0';
          eventType = message;
          if(eventType == "OFF"){
            cnt2 = 0;
            parts[index - 1].period = 0;
          }else{
            cnt2++;
          }
          break;
        case 2:                   //Final data is period
          parts[index - 1].period = decorder();
          //デューティ比設定
          if(parts[index - 1].period <= 3500 && parts[index - 1].period >= 2000){        
            parts[index - 1].duty = 100.00 - map(parts[index - 1].period, 2000, 3500, 20, 70);
          }else if(parts[index - 1].period <= 6000 && parts[index - 1].period > 3500){
            parts[index - 1].duty = 100.00 - map(parts[index - 1].period, 3500, 6000, 55, 75);
          }else if(parts[index - 1].period <= 8000 && parts[index - 1].period > 6000){
            parts[index - 1].duty = 100.00 - map(parts[index - 1].period, 6000, 8000, 70, 80);
          }else if(parts[index - 1].period <= 15000 && parts[index - 1].period > 8000){
            parts[index - 1].duty = 100.00 - map(parts[index - 1].period, 8000, 15000, 80, 90);
          }else{
            if(parts[index - 1].period > 15000)
              parts[index - 1].duty = 10;
            else
              parts[index - 1].duty = 90;
          }
          cnt2 = 0;
          break;
      }
      cnt1 = 0;
    }
  }
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
    if(!parts[i].period){
      if(i < 9){
        for(int j = 1; j < 10 - i; j++){
          if(parts[i + j].period == 0 && j + 1 == 9 - i){
            return i;
          }
          if(parts[i + j].period != 0){
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
