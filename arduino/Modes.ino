// Management of behavior modes
// Their is 2 working mode + 3 macro pages :
// => Working mode "standard" : using the macro
// => Working mode "edit" : editing the macro
// => The 3 macro pages can be selected on standard or edit mode
// Here are provided mode selection + IO management

uint8_t currentWorkingMode = 0;
uint8_t currentMacroPage = 0;

uint8_t checkedWorkingMode = 9;
uint8_t checkedMacroPage = 9;

void setupModeSwitchs(){
  pinMode(MODE_PIN, INPUT_PULLUP);
  pinMode(PAGE_I_PIN, INPUT_PULLUP);
  pinMode(PAGE_II_PIN, INPUT_PULLUP);
}

uint8_t getCurrentWorkingMode(){
  return currentWorkingMode;
}

uint8_t getCurrentMacroPage(){
  return currentMacroPage;
}

bool isMacroPageChanged(){
  if(checkedMacroPage != currentMacroPage){
    Serial.print("MACRO CHANGED = ");
    Serial.println(currentMacroPage);
    checkedMacroPage = currentMacroPage;
    return true;
  }

  return false;
}

bool isWorkingModeChanged(){
  if(checkedWorkingMode != currentWorkingMode){
    Serial.print("MODE CHANGED = ");
    Serial.println(currentWorkingMode);
    checkedWorkingMode = currentWorkingMode;
    return true;
  }

  return false;
}

void checkModes(){

  currentMacroPage = 0;

  if(digitalRead(PAGE_I_PIN) == 0){
    currentMacroPage = 1;
  }

  if(digitalRead(PAGE_II_PIN) == 0){
    currentMacroPage = 2;
  }
  
  currentWorkingMode = digitalRead(MODE_PIN);
}

