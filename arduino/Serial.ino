// TODO : here support for USB controlled macro edition tool

char cmdBuffer[4];

bool checkCommand(){
  if (Serial.available()) {
    Serial.readBytes(cmdBuffer, Serial.available());
    Serial.print("ACK");
    return true;
  }
  return false;
}


