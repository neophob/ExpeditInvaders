// readCapacitivePin
//  Input: Arduino pin number
//  Output: A number, from 0 to 17 expressing
//  how much capacitance is on the pin
//  When you touch the pin, or whatever you have
//  attached to it, the number will get higher
uint8_t readCapacitivePin(int pinToMeasure){
  // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.
  byte bitmask;
  if ((pinToMeasure >= 0) && (pinToMeasure <= 7)){
    port = &PORTD;
    ddr = &DDRD;
    bitmask = 1 << pinToMeasure;
    pin = &PIND;
  }
  if ((pinToMeasure > 7) && (pinToMeasure <= 13)){
    port = &PORTB;
    ddr = &DDRB;
    bitmask = 1 << (pinToMeasure - 8);
    pin = &PINB;
  }
  if ((pinToMeasure > 13) && (pinToMeasure <= 19)){
    port = &PORTC;
    ddr = &DDRC;
    bitmask = 1 << (pinToMeasure - 13);
    pin = &PINC;
  }
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;
  // Now see how long the pin to get pulled up
  int cycles = 17;
  for(int i = 0; i < 16; i++){
    if (*pin & bitmask){
      cycles = i;
      break;
    }
  }
  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to 
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return cycles;
}



#define FLIP_VALUE 8

boolean triggered=false;
unsigned long lastCheck = 0;

// --------------------------------------------
//    check input
// --------------------------------------------
boolean isFingerConnectedToPin(int pin, int checkIntervall) {
  
  //check if the intervall passed, if not return false
  unsigned long now = millis();
  if (now - lastCheck < checkIntervall) {
    return false; 
  }
  
  //intervall passed...
  lastCheck = now;
  
  uint8_t val = readCapacitivePin(pin);

#ifdef USE_SERIAL_DEBUG
  Serial.print("Value: ");
  Serial.print(val);
  Serial.print(" Triggered: ");
  Serial.println(triggered);
#endif

  if (val >= FLIP_VALUE && triggered == false) {
#ifdef USE_SERIAL_DEBUG
    Serial.println("set flag true");
#endif
    triggered = true;
    return true;
  } 
  else if (val < FLIP_VALUE && triggered) {
    triggered = false;
  }

  return false;
} 



