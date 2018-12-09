// Management of LCD Display

#define MAX_BACKLIGHT 255
#define BACKLIGHT_STEP 20

// Init LCD Display
LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN); 

// Backlight level
uint8_t currentBacklight = MAX_BACKLIGHT;

bool fadeSwitch = false;

// Init display (LCD + Backlight)
void setupDisplay() {
  
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  
  // PWM PIN for display backlight
  pinMode(LCD_LIGHT_PIN, OUTPUT);
}

// For fixed light level
void setBacklightLevel(unsigned char val){
  currentBacklight = val;
  updateBacklight();
}

void stepUpBacklightLevel(){
  if(currentBacklight + BACKLIGHT_STEP <= MAX_BACKLIGHT){
    currentBacklight = currentBacklight + BACKLIGHT_STEP;
  }else {
    currentBacklight = MAX_BACKLIGHT;
  }
  updateBacklight();
}

void fadeBacklightLevel(){
  if(fadeSwitch){
    currentBacklight++;
  } else {
    currentBacklight--;
  }
  
  if(currentBacklight >= MAX_BACKLIGHT || currentBacklight <= 0){
    fadeSwitch = !fadeSwitch;
  }

  updateBacklight();
}

void stepDownBacklightLevel(){
  if(currentBacklight - BACKLIGHT_STEP >= 0){
    currentBacklight = currentBacklight - BACKLIGHT_STEP;
  } else {
    currentBacklight = 0;
  }
  updateBacklight();
}

// Apply current backlight level
void updateBacklight(){
  analogWrite(LCD_LIGHT_PIN, currentBacklight);
}

void updatePageDisplay(String title, String help){
  resetDisplay();
  Serial.print("Update page title with ");
  Serial.println(title);
  writeDisplay(false, 0, title);
  writeDisplay(false, 1, help);
}

void resetDisplay(){
  lcd.noAutoscroll();
  lcd.clear();
}

void writeDisplay(String value){
  writeDisplay(true, 0, value);
}

void writeDisplay(bool clear, uint8_t line, String value){
  
  uint8_t len = value.length();
  char charValue[len+1];
  value.toCharArray(charValue, len+1);

  if(clear){
    lcd.clear();
  }
  lcd.setCursor(0, line);
  lcd.print(charValue);
}

