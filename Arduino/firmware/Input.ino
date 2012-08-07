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
  //key pressed?
  if (!keyboard.available()) {
    return; 
  }

  // read the next key
  char c = keyboard.read();

  switch (c) {
  case PS2_UPARROW:
    mode++;
    if (mode > MAX_MODE) {
      mode = 0; 
    }
#ifdef USE_SERIAL_DEBUG      
    Serial.print("[Up], mode: ");
    Serial.println(mode);
#endif
    break;
    
  case PS2_RIGHTARROW:
    colorMode++;
    if (colorMode > MAX_COLOR_MODE) {
      colorMode = 0;
    }
    loadColorSet(colorMode);
    break;
    
  default:
#ifdef USE_SERIAL_DEBUG      
    Serial.print("Hex Keycode: ");
    Serial.println(c, HEX);
#endif
    break;
  }


}


