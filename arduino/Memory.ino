// Teensy LC has a very small EEPROM (1/8 kB, in emu mode only)
// So we use a 24LC16 (16kb = 2kB, so not a lot of space but for macro it should be ok)
// The memory should be loaded like this :
// => On setup, put in RAM the content (Teensy LC has 62kB of RAM, which is quite large and enough for storing all the eeprom content)
// => After an update of macro
// The memory is updated only when using the "update macro" mode
// The memory content is stored separately for each macro page
// Titles for 3 macro pages are stored as "page 4"
// Helps for 3 macro pages are stored as "page 5"
// The play mode for macro is stored as a bit array
// The backlight level is also stored

// Data model :
// => char[0] = TOKEN CHAR 
// => char[1] = backlightLevel
// => char[2] to char[514] = macro page 0
// => char[515] to char[1027] = macro page 1
// => char[1028] to char[1540] = macro page 2
// => char[1541] to char[1768] = macro page titles
// => char[1769] to char[1999] = macro page helps
// => char[2000] to char[2004] = bit for cmd modes

// A delay of 5 is required after each byte write for compliance

#define LAST_ADDRESS      2005 // Maximum address
#define MACRO_PAGE_SIZE   511
#define TITLES_PAGE_SIZE  127
#define HELPS_PAGE_SIZE   127
#define MODES_ADDRESS     2000

byte TOKEN_CHAR = 2; // ASCII start of text
byte CMD_SEPARATOR = 31; // ASCII unit separator

String currentPage[5];
String currentTitle;
String currentHelp;
byte currentModesValue;

c24LC16B memory = c24LC16B();

void setupMemory(){
  Wire.begin();
}

// The default memory content
void initMemoryIfRequired(){

  byte header = memory.read_byte(0);
  
  Serial.print("Checking memory . Get value : ");
  Serial.println(header);

  if(header != TOKEN_CHAR){

    Serial.println("Memory is not initialized yet. Erase and write new value");

    // Token char
    memory.write(0, TOKEN_CHAR);
    delay(5);

    // Default level
    writeBacklightLevel(227);

    // Page 0
    initMacroPage(0, "git status", "git add -A", "git commit -m \":construction:", "git push", "git pull");
    initModes(0, true, true, false, true, true);
    
    // Page 1
    initMacroPage(1, "sudo docker ps", "sudo docker ps -a", "sudo docker start ", "sudo docker exec -i -t ", " /bin/sh");
    initModes(1, true, true, true, false, false);
    
    // Page 2
    initMacroPage(2, "ls -alh", "ps -ef", "ls", "ls", "ls");
    initModes(2, true, true, true, true, true);
    
    // Page titles
    initTitles(" PAGE : GIT", " PAGE : DOCKER", " PAGE : LINUX");
    
    // Page helps
    initHelp("sta/ad/c/pus/pul", "ps/psa/st/ex..ex", "ll/ps/?/?/?");
    // ................
    
  } else {
     Serial.println("Memory is already initialized. Does nothing");
  }
}

void initMacroPage(uint8_t pageNumber, char *cmdOne, char *cmdTwo, char *cmdThree, char *cmdFour, char *cmdFive){
  resetPage(pageNumber, MACRO_PAGE_SIZE);
  char pageCmds[MACRO_PAGE_SIZE];
  sprintf(pageCmds, "%s%c%s%c%s%c%s%c%s", cmdOne, CMD_SEPARATOR, cmdTwo, CMD_SEPARATOR, cmdThree, CMD_SEPARATOR, cmdFour, CMD_SEPARATOR, cmdFive);
  writePage(pageNumber, pageCmds, sizeof(pageCmds));
  delay(20);
}

void initTitles(char *titleOne, char *titleTwo, char *titleThree){
  resetPage(3, TITLES_PAGE_SIZE);
  char titles[TITLES_PAGE_SIZE];
  sprintf(titles, "%s%c%s%c%s", titleOne, CMD_SEPARATOR, titleTwo, CMD_SEPARATOR, titleThree);
  writePage(3, titles, sizeof(titles)); 
  delay(20);
}

void initHelp(char *helpOne, char *helpTwo, char *helpThree){
  resetPage(4, HELPS_PAGE_SIZE);
  char helps[HELPS_PAGE_SIZE];
  sprintf(helps, "%s%c%s%c%s", helpOne, CMD_SEPARATOR, helpTwo, CMD_SEPARATOR, helpThree);
  writePage(4, helps, sizeof(helps)); 
  delay(20);
}

void initModes(uint8_t pageNumber, bool md1, bool md2, bool md3, bool md4, bool md5){
  byte value = 0;

  // Define bit values
  bitWrite(value, 0, md1 ? 1 : 0);
  bitWrite(value, 1, md2 ? 1 : 0);
  bitWrite(value, 2, md3 ? 1 : 0);
  bitWrite(value, 3, md4 ? 1 : 0);
  bitWrite(value, 4, md5 ? 1 : 0);
  
  Serial.print("Mode bit value is ");
  Serial.println(value); 
  
  memory.write(MODES_ADDRESS + pageNumber, value);
  delay(5);
}

void loadModes(uint8_t pageNumber){
  currentModesValue = memory.read_byte(MODES_ADDRESS + pageNumber);
}

uint8_t readBacklightLevel(){
  delay(5);
  return (uint8_t) memory.read_byte(1);
}

void writeBacklightLevel(uint8_t level){
  memory.write(1, (byte) 227);
  delay(5);
}

uint16_t getPageAddress(uint8_t pageNumber){
  
  switch (pageNumber) {
    case 0: 
      return 2;
    case 1: 
      return 515;
    case 2: 
      return 1028;
    case 3: 
      return 1541;
    case 4: 
      return 1769;
  }  
  return 2;
}

void loadPage(uint8_t pageNumber){
  
  Serial.print("Loading current page : ");
  Serial.println(pageNumber);
  
  String loadedPage[5];
  readPage(pageNumber,loadedPage, MACRO_PAGE_SIZE, 5);

  String titles[3];
  readPage(3, titles, TITLES_PAGE_SIZE, 3);

  String helps[3];
  readPage(4, helps, HELPS_PAGE_SIZE, 3);

  loadModes(pageNumber);
  
  currentPage[0] = loadedPage[0];
  currentPage[1] = loadedPage[1];
  currentPage[2] = loadedPage[2];
  currentPage[3] = loadedPage[3];
  currentPage[4] = loadedPage[4];
  currentTitle = titles[pageNumber];
  currentHelp = helps[pageNumber];
}

String getCurrentPageTitle(){ 
  return currentTitle;
}

String getCurrentPageHelp(){ 
  return currentHelp;
}

String getCurrentPageContentForKey(uint8_t key){ 
  return currentPage[key - 1];
}

bool getCurrentPageModeForKey(uint8_t key){
  bool mode = bitRead(currentModesValue, key - 1) == 1;
  Serial.print("Mode for key ");
  Serial.print(key);
  Serial.print(" is ");
  Serial.println(mode);

  return mode;
}

void writePage(uint8_t pageNumber, char* content, uint16_t ctSize){
  
  uint16_t addr = getPageAddress(pageNumber);

  Serial.print("Write page ");
  Serial.print(pageNumber);
  Serial.print(" from ");
  Serial.print(addr);
  Serial.print(" to ");
  Serial.println(addr + ctSize);
  
  delay(5);
  
  for (int i = 0; i < ctSize; i++){
    memory.write(i + addr, (byte) content[i]);
    delay(5);
  }
}

void resetPage(uint8_t pageNumber, int pageSize){
  
  uint16_t addr = getPageAddress(pageNumber);
  uint16_t addrEnd = addr + pageSize;
  
  Serial.print("Reset page ");
  Serial.print(pageNumber);
  Serial.print(" from ");
  Serial.print(addr);
  Serial.print(" to ");
  Serial.println(addrEnd);
  
    delay(5);
  for (int i = addr; i < addrEnd; i++){
    memory.write(i, (byte) 0);
    delay(5);
  }
}

void readPage(uint8_t pageNumber, String *macroPage, int pageSize, uint8_t tMax){
  
  delay(5);
  
  uint16_t addr = getPageAddress(pageNumber);
  uint16_t addrEnd = addr + pageSize;
  uint16_t addrLast = addrEnd - 1;

  Serial.print("Read page ");
  Serial.println(pageNumber);

  // Now split pageValue
  uint8_t t=0;
  byte current;
  String cmd = "";
  bool completed = false;

  for (uint16_t i=addr; i < addrEnd && t < tMax; i++){ 
    current = memory.read_byte(i);
    
    if(current == 0){
      completed = true;
    }
    
    if(current == CMD_SEPARATOR || i == addrLast) { 
      macroPage[t] = cmd; 
      Serial.print("Part ");
      Serial.print(t);
      Serial.print(" = ");
      Serial.println(cmd);
      t++; 
      cmd = "";
      completed = false;
    } else if(!completed){
      cmd.concat((char) current);
    }
  }
}
