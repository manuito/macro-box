// USB support (keyboard)

void setupUsbKeyboard(){
   Keyboard.begin();
}

void commandOnKeyboard(String cmd, bool mode){
  if(mode){
    Keyboard.println(cmd);
  } else {
    Keyboard.print(cmd);
  }
}

