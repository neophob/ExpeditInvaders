/*  PS2Keyboard library example
  
  PS2Keyboard now requries both pins specified for begin()

  keyboard.begin(data_pin, irq_pin);
  
  Valid irq pins:
     Arduino:      2, 3
     Arduino Mega: 2, 3, 18, 19, 20, 21
     Teensy 1.0:   0, 1, 2, 3, 4, 6, 7, 16
     Teensy 2.0:   5, 6, 7, 8
     Teensy++ 1.0: 0, 1, 2, 3, 18, 19, 36, 37
     Teensy++ 2.0: 0, 1, 2, 3, 18, 19, 36, 37
     Sanguino:     2, 10, 11
  
  for more information you can read the original wiki in arduino.cc
  at http://www.arduino.cc/playground/Main/PS2Keyboard
  or http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html
  
  Like the Original library and example this is under LGPL license.
  
  Modified by Cuninganreset@gmail.com on 2010-03-22
  Modified by Paul Stoffregen <paul@pjrc.com> June 2010
*/
   


void handleKeyboard() {
  if (keyboard.available()) {
    
    // read the next key
    char c = keyboard.read();
    
    if (c == PS2_UPARROW) {
      mode++;
      if (mode > MAX_MODE) {
         mode = 0; 
      }
#ifdef USE_SERIAL_DEBUG      
      Serial.print("[Up], mode: ");
      Serial.println(mode);
#endif
    }
    
    if (c == PS2_RIGHTARROW) {
      colorMode++;
      if (colorMode > MAX_COLOR_MODE) {
        colorMode = 0;
      }
      
      unsigned long initialColor[3] = { 0xff0000, 0x00ff00, 0x0000ff }; //RGB
      switch (colorMode) {
         case 1:
               initialColor[0] = 0xdc323c;  //Rasta
               initialColor[1] = 0xf0cb58;
               initialColor[2] = 0x3c825e;
               break; 
         case 2:
               initialColor[0] = 0xd3517d;  //CGA
               initialColor[1] = 0x15a0bf;
               initialColor[2] = 0xffc062;
               break; 
         case 3:
               initialColor[0] = 0x008c53;  //Brazil
               initialColor[1] = 0x2e00e4;
               initialColor[2] = 0xdfea00;  
               break; 
      }
#ifdef USE_SERIAL_DEBUG      
      Serial.print("[Right] load new color: ");
      Serial.println(colorMode);      
#endif
      initColorSet(initialColor);
      
    }
    // check for some of the special keys
/*    if (c == PS2_ENTER) {
      Serial.println();
    } else if (c == PS2_TAB) {
      Serial.print("[Tab]");
    } else if (c == PS2_ESC) {
      Serial.print("[ESC]");
    } else if (c == PS2_PAGEDOWN) {
      Serial.print("[PgDn]");
    } else if (c == PS2_PAGEUP) {
      Serial.print("[PgUp]");
    } else if (c == PS2_LEFTARROW) {
      Serial.print("[Left]");
    } else if (c == PS2_RIGHTARROW) {
      Serial.print("[Right]");
    } else if (c == PS2_UPARROW) {
      Serial.print("[Up]");
    } else if (c == PS2_DOWNARROW) {
      Serial.print("[Down]");
    } else if (c == PS2_DELETE) {
      Serial.print("[Del]");
    } else {
      
      // otherwise, just print all normal characters
      Serial.print(c);
    }*/
  }
}
