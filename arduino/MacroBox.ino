#include <c24LC16B.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include "Keyboard.h"


// Display pins (Liquid Crystal + Backlight level)
#define LCD_RS_PIN    12
#define LCD_EN_PIN    11
#define LCD_D4_PIN    5
#define LCD_D5_PIN    4
#define LCD_D6_PIN    3
#define LCD_D7_PIN    2
#define LCD_LIGHT_PIN 10

// Mode switch pin (small switch)
#define MODE_PIN      1

// Macro page switch (3 pos switch)
#define PAGE_I_PIN    7
#define PAGE_II_PIN   8

// LED pins (through ULN2003)
#define LED_1_PIN     20
#define LED_2_PIN     17
#define LED_3_PIN     16
#define LED_4_PIN     6
#define LED_5_PIN     9

// Keys pins (buttons)
#define KEY_1_PIN     23
#define KEY_2_PIN     22
#define KEY_3_PIN     21
#define KEY_4_PIN     15
#define KEY_5_PIN     14


void setup() {

  Serial.begin(9600);
  setupKeysAndLeds();
  setupModeSwitchs();
  setupMemory();
  setupDisplay();
  setupUsbKeyboard();
  
  // Check memory content. Apply default macro if needed
  initMemoryIfRequired();
  
  setAllLedsOff();

  setBacklightLevel(readBacklightLevel());
  updateBacklight();
  
  checkModes();
}

void loop() {
  
  if(isMacroPageChanged()){
    macroPageChangedAction();
  } 
  
  else if(isWorkingModeChanged()){
    workingModeChangedAction();
  } 
  
  else if(isKeyPressed()){
    keyPressedAction();
  } 

  delay(20);
  
  checkModes();
  updateKeys();
  setAllLedsOff();
}

// Action - macro page swtich changed - load new page
void macroPageChangedAction(){
  loadPage(getCurrentMacroPage());
  updatePageDisplay(getCurrentPageTitle(), getCurrentPageHelp());
}

// Action - edit switch changed - go to edit mode
void workingModeChangedAction(){
  fadLedsFast();
  // TODO : set edit mode
}

// Action - macro key pressed - play macro
void keyPressedAction(){
  commandOnKeyboard(getCurrentPageContentForKey(getCurrentPressedKey()), getCurrentPageModeForKey(getCurrentPressedKey()));
  activateLedWithBlink(getCurrentPressedKey(),2);
}