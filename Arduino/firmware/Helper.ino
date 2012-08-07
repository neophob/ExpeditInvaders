#define EEPROM_HEADER_09 9
#define EEPROM_HEADER_10 10
#define EEPROM_HEADER_11 11

#define EEPROM_POS_MODE 13
#define EEPROM_POS_COLORMODE 14

const byte CONST_I = 'I';
const byte CONST_N = 'N';
const byte CONST_V = 'V';

// --------------------------------------------
//     store current mode to eeprom
// --------------------------------------------
void saveCurrentStateToEeprom() {
#ifdef USE_SERIAL_DEBUG      
    Serial.println("Save current settings to EEPROM");
#endif  
  EEPROM.write(EEPROM_HEADER_09, CONST_I);
  EEPROM.write(EEPROM_HEADER_10, CONST_N);
  EEPROM.write(EEPROM_HEADER_11, CONST_V);
  EEPROM.write(EEPROM_POS_MODE, mode);
  EEPROM.write(EEPROM_POS_COLORMODE, colorMode);  
}

// --------------------------------------------
//     load saved preset from eeprom (if available)x
// --------------------------------------------
void restorePresetStateFromEeprom() {
  //check if data/clk port is stored in the eeprom. First check for header INV 
  byte header1 = EEPROM.read(EEPROM_HEADER_09);
  byte header2 = EEPROM.read(EEPROM_HEADER_10);
  byte header3 = EEPROM.read(EEPROM_HEADER_11);
#ifdef USE_SERIAL_DEBUG      
    Serial.println("Check EEPROM for saved values");
#endif

  if (header1 == CONST_I && header2 == CONST_N && header3 == CONST_V) {
#ifdef USE_SERIAL_DEBUG      
    Serial.println("Use EEPROM settings");
#endif
    
    //load work mode
    mode = EEPROM.read(EEPROM_POS_MODE);
    if (mode>=MAX_MODE) {
      mode=0;
    }
    
    //load color mode
    colorMode = EEPROM.read(EEPROM_POS_COLORMODE);
    if (colorMode>=MAX_COLOR_MODE) {
      colorMode=0;
    }
    loadColorSet(colorMode);

  }
}
