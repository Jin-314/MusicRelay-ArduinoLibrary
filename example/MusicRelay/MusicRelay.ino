static uint8_t buff[20] = {0};

int parts[10] = {0};
uint8_t index = 0;
uint8_t cnt1 = 0;
signed char inByte = 0;

void setup() {
  //Serial Initialize  
  Serial.begin(2000000);
  DDRD = B11111100;
  DDRB = B00001111;
}

void loop() {
  bool flug[10] = {false};
  unsigned long pretime[10] = {0};
  unsigned long mtime = 0;
  uint8_t partIdx = 0;
  byte byted[10] = {0}, byteb[10] = {0};
  uint8_t cnt2 = 0;
  int onTime[10] = {0};

  while(1){
    String eventType = "";
    char message[5];
    uint8_t tmp;
    mtime = micros();
    //同時に鳴らすパートの数分繰り返す
    for(byte i = 0; i < partIdx; i++){
      if(parts[i] > 0){
        int diff = mtime - pretime[i];
        //各パートごとに鳴らすか鳴らさないか判定
        if(!flug[i] && diff < onTime[i]){
          flug[i] = true;
          PORTD |= byted[i];
          PORTB |= byteb[i];
        }else if(flug[i] && diff > onTime[i]){
          flug[i] = false;
          PORTD &= ~byted[i];
          PORTB &= ~byteb[i];
        }else if(diff > parts[i]){
          pretime[i] = mtime;
        }
      }
    }
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
              parts[index - 1] = 0;
              partIdx = CountParts();
              onTime[index - 1] = 0;
              byted[index - 1] = 0;
              byteb[index - 1] = 0;
            }else{
              cnt2++;
            }
            break;
          case 2:                   //Final data is period
            parts[index - 1] = decorder();
            partIdx = CountParts();
            //個数制御、空いてるリレーはどんどん鳴らす
            for(byte j = 0; (tmp = (index + 1) + j * partIdx) < 12; j++){
                if(tmp < 10)
                  if(tmp < 8)
                    byted[index - 1] |= 1 << tmp;
                  else
                    byteb[index - 1] |= 1 << (tmp - 8);
            }
            /*//個数制御なしver
            if(index - 1 < 8)
              byted[index - 1] |= 1 << (i + 1);
            else
              byteb[index - 1] |= 1 << (i - 9);*/
            float duty[10] = {0};
            //デューティ比設定
            if(parts[index - 1] <= 3500 && parts[index - 1] >= 2000){        
              duty[index - 1] = 100.00 - map(parts[index - 1], 2000, 3500, 20, 70);
            }else if(parts[index - 1] <= 6000 && parts[index - 1] > 3500){
              duty[index - 1] = 100.00 - map(parts[index - 1], 3500, 6000, 55, 75);
            }else if(parts[index - 1] <= 8000 && parts[index - 1] > 6000){
              duty[index - 1] = 100.00 - map(parts[index - 1], 6000, 8000, 70, 80);
            }else if(parts[index - 1] <= 15000 && parts[index - 1] > 8000){
              duty[index - 1] = 100.00 - map(parts[index - 1], 8000, 15000, 80, 90);
            }else{
              if(parts[index - 1] > 15000)
                duty[index - 1] = 10;
              else
                duty[index - 1] = 90;
            }
            duty[index - 1] /= 100.00;
            onTime[index - 1] = (float)parts[index - 1] * duty[index - 1];
            cnt2 = 0;
            break;
        }
        cnt1 = 0;
      }
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
