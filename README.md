# ExpeditInvaders

Check out the **Blog** entry about ExpeditInvaders: http://neophob.com/2012/08/expeditinvaders-the-spiced-up-ikea-shelf/

If you like ExpeditInvaders and want to support me, check out my **Shop** at: http://pixelinvaders.ch/?page_id=390

# HowTo

## Needed Hardware
* Ikea Expedit Shelf
* Arduino board
* 40 LED Modules
* 12V PSU (for example an old ATX PSU)
* PS2 Keyboard

## Needed Arduino Libraries
* EEPROM (default library)
* SPI (default library)
* PS2 Keyboard (http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html)
* LPD6803 (https://github.com/neophob/neophob_lpd6803spi)
* TimerOne (http://arduino.cc/playground/Code/Timer1)


## Module Placement
    The IKEA Expedit shelf with 40 LED Modules looks like this:
       +----------+----------+----------+----------+
       |          |          |          |          |
       |          |          |          |          |
       |          |          |          |          |       
       | 40 39 38 | 37 36 35 | 34 33 32 | 31 30 29 |
       +----------+----------+----------+----------+
       | 17 18 19 | 20 21 22 | 23 24 25 | 26 27 28 |
    16 |          |          |          |          |
    15 |          |          |          |          |       
    14 |          |          |          |          |
       +----------+----------+----------+----------+
       | 13 12 11 | 10 09 08 | 07 06 05 | 04 03 02 |
       |          |          |          |          |
       |          |          |          |          | 01       
       |          |          |          |          | |\
       +----------+----------+----------+----------+ | \
       |          |          |          |          | |  +12V PSU
       |          |          |          |          | |
       |          |          |          |          | Arduino      
       |          |          |          |          |
       +----------+----------+----------+----------+
    Module 1,14,15,16 will be blank
