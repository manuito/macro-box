// Management of keys + associated LEDs

#define MIDDLE_LEVEL  30
#define HIGHT_LEVEL  200

uint8_t currentPressedKey = 0;

void setupKeysAndLeds(){

  // All LEDs 
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_4_PIN, OUTPUT);
  pinMode(LED_5_PIN, OUTPUT);

  // All keys
  pinMode(KEY_1_PIN, INPUT_PULLUP);
  pinMode(KEY_2_PIN, INPUT_PULLUP);
  pinMode(KEY_3_PIN, INPUT_PULLUP);
  pinMode(KEY_4_PIN, INPUT_PULLUP);
  pinMode(KEY_5_PIN, INPUT_PULLUP);
}

void setLedHightLevel(uint8_t number){
    updateLed(number, HIGHT_LEVEL);
}

void setLedMiddleLevel(uint8_t number){
    updateLed(number, MIDDLE_LEVEL);
}

void setLedOff(uint8_t number){
    updateLed(number, 0);
}

void setAllLedsOff(){
  analogWrite(LED_1_PIN, 0);
  analogWrite(LED_2_PIN, 0);
  analogWrite(LED_3_PIN, 0);
  analogWrite(LED_4_PIN, 0);
  analogWrite(LED_5_PIN, 0);
}

void setRangeLedsOff(uint8_t numberStart, uint8_t numberEnd){
  for(int i = numberStart; i < numberEnd + 1; i++){
    setLedOff(i);
  }
}

uint8_t getCurrentPressedKey(){
  return currentPressedKey;
}

bool isKeyPressed(){
  return currentPressedKey != 0 ;
}

void updateKeys(){
  if(digitalRead(KEY_1_PIN) == 0){
    currentPressedKey = 1;
  } else if(digitalRead(KEY_2_PIN) == 0){
    currentPressedKey = 2;
  } else if(digitalRead(KEY_3_PIN) == 0){
    currentPressedKey = 3;
  } else if(digitalRead(KEY_4_PIN) == 0){
    currentPressedKey = 4;
  } else if(digitalRead(KEY_5_PIN) == 0){
    currentPressedKey = 5;
  } else {
    currentPressedKey = 0;
  }
}

void activateLedWithBlink(uint8_t number, uint8_t blinkCount){
  for(uint8_t i = 0; i < blinkCount; i++){
    setLedMiddleLevel(number);
    delay(100);
    setLedHightLevel(number);
    delay(100);
  }
}

// Apply specified led 
void updateLed(uint8_t number, uint8_t level){

  switch (number) {
    case 1: 
      analogWrite(LED_1_PIN, level);
      break;
    case 2: 
      analogWrite(LED_2_PIN, level);
      break;
    case 3: 
      analogWrite(LED_3_PIN, level);
      break;
    case 4: 
      analogWrite(LED_4_PIN, level);
      break;
    case 5: 
      analogWrite(LED_5_PIN, level);
      break;
  }
}

// Fad in / out in less than 1 second
void fadLedsFast(){

  for(int i = 0; i < HIGHT_LEVEL; i++){
    analogWrite(LED_1_PIN, i);
    analogWrite(LED_2_PIN, i);
    analogWrite(LED_3_PIN, i);
    analogWrite(LED_4_PIN, i);
    analogWrite(LED_5_PIN, i);
    delay(1);
  }
  
  for(int i = HIGHT_LEVEL; i >= 0; i--){
    analogWrite(LED_1_PIN, i);
    analogWrite(LED_2_PIN, i);
    analogWrite(LED_3_PIN, i);
    analogWrite(LED_4_PIN, i);
    analogWrite(LED_5_PIN, i);
    delay(1);
  }
}

void demoLeds(){

  for(int i = 1; i < 6; i++){
    setLedMiddleLevel(i);
    delay(200);
  }

  for(int i = 5; i > 0; i--){
    setLedHightLevel(i);
    delay(200);
  }
  
  for(int i = 1; i < 6; i++){
    setLedOff(i);
    delay(200);
  }

  for(int i = 5; i > 0; i--){
    setAllLedsOff();
    setLedHightLevel(i);
    delay(200);
  }

  setAllLedsOff();
}

