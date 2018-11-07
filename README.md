# macro-box

A macro keyboad in a box ...

(Sorry, not painted yet) : 

![box](docs/box.jpg?raw=true "box")

## Details 

This project is a simple USB "keyboad" extension, using standard modules / components

* Custom made box. 
* Teensy LC (Arm M0+ 48Mhz, USB support)
* 1 standard 2x16 LCD Display (using standard LiquidCrystal library)
* 5 "keys" (standard buttons) with status leds
* A 3 position switch for "macro page selection". 3 pages x 5 buttons = 15 supported macros
* A 2 position switch (behind) for "edit mode". The macro can be edited directly from the box (not implemented yet)
* Custom boards for electronic integration (Level shifter for display control, ULN2003 for LED power, various support NPN / Resistors)
* 24LC16 Serial EEPROM for macro storage

![diag](docs/diag.jpg?raw=true "diag")

## Prerequisite for building

Programmed with Arduino IDE. Need to install Teensyduino extension first. 
The library used for 24LC16 is https://github.com/blins/c24LC16B (the only one which seems to work with this exact configuration)

Entrypoint is MacroBox.ino

## Schematics

TODO
