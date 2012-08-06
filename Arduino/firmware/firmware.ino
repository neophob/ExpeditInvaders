/*
 * ExpeditInvaders firmware, Copyright (C) 2012 michael vogt <michu@neophob.com>
 * Tested on Teensy and Arduino
 * 
 * ------------------------------------------------------------------------
 *
 * This is the SPI version, unlike software SPI which is configurable, hardware 
 * SPI works only on very specific pins. 
 *
 * On the Arduino Uno, Duemilanove, etc., clock = pin 13 and data = pin 11. 
 * For the Arduino Mega, clock = pin 52, data = pin 51. 
 * For the ATmega32u4 Breakout Board and Teensy, clock = pin B1, data = B2. 
 *
 * ------------------------------------------------------------------------
 *
 * This file is part of ExpeditInvaders.
 *
 * ExpeditInvaders is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * ExpeditInvaders is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * 

Module Placement
----------------
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
 
 If you need some Modules and want to support my work, check out http://pixelinvaders.ch/
 
 
 TODO:
 -more modes
 -switch display
 -switch colorset
 -save setting to eeprom after some time...
 */

//the lpd6803 library needs the timer1 library
#include <TimerOne.h>
#include <SPI.h>
#include <Neophob_LPD6803.h>
#include <PS2Keyboard.h>

#define NR_OF_PIXELS 40

//one pixel uses 3 leds
#define LED_GROUP 3
#define BUFFER_SIZE 14  //NR_OF_PIXELS/BUFFER_SIZE

const uint8_t ledPin = 9;

//use serail debug or not
#define USE_SERIAL_DEBUG 1

//initialize pixels 9*20
Neophob_LPD6803 strip = Neophob_LPD6803(NR_OF_PIXELS);
byte buffer[BUFFER_SIZE];

PS2Keyboard keyboard;
const int DataPin = 3;
const int IRQpin =  2;


// --------------------------------------------
//     led flash
// --------------------------------------------
void synchronousBlink() {
  digitalWrite(ledPin, HIGH);
  delay(20);
  digitalWrite(ledPin, LOW);  
}

// --------------------------------------------
//     create initial image
// --------------------------------------------
void clearModuleBuffer() {
  for (int i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
  }    
  // Update the strip, to start they are all 'off'
  strip.show();
}

// --------------------------------------------
//      setup
// --------------------------------------------
void setup() {
#ifdef USE_SERIAL_DEBUG
  Serial.begin(115200);
  Serial.println("Init Strip");
#endif

  //cpu use and SPI clock must be adjusted
  strip.setCPUmax(64);  // start with 50% CPU usage. up this if the strand flickers or is slow  
//  strip.begin(SPI_CLOCK_DIV128);        // Start up the LED counterm 0.125MHz - 8uS
//  strip.begin(SPI_CLOCK_DIV64);        // Start up the LED counterm 0.25MHz - 4uS
//  strip.begin(SPI_CLOCK_DIV32);        // Start up the LED counterm 0.5MHz - 2uS
  strip.begin(SPI_CLOCK_DIV16);        // Start up the LED counterm 1.0MHz - 1uS

#ifdef USE_SERIAL_DEBUG
  Serial.println("Clear Module Buffer");
#endif
  clearModuleBuffer();      // display some colors
  
#ifdef USE_SERIAL_DEBUG
  Serial.println("Init ColorSet");
#endif  
//  unsigned long initialColor[3] = { 0xff0000, 0x00ff00, 0x0000ff }; //RGB
//  unsigned long initialColor[3] = { 0xdc323c, 0xf0cb58, 0x3c825e }; //Rasta
  unsigned long initialColor[3] = { 0xd3517d, 0x15a0bf, 0xffc062 }; //CGA  
//  unsigned long initialColor[3] = { 0x008c53, 0x2e00e4, 0xdfea00 }; //Brazil  
  
  initColorSet(initialColor);
  initContent();
  
  //we-are-ready indicator
  pinMode(ledPin, OUTPUT);  
  synchronousBlink();
  delay(50);
  synchronousBlink();

#ifdef USE_SERIAL_DEBUG
  Serial.println("Init keyboard!");
#endif    
  keyboard.begin(DataPin, IRQpin);

#ifdef USE_SERIAL_DEBUG
  Serial.println("Setup done!");
#endif  
}

// --------------------------------------------
//      main loop
// --------------------------------------------
void loop() {
  //create 8bit buffer  
  generateContent(); 

  handleKeyboard();
/*unsigned int c =  Color(i,i,i);
  i++;
  if (i>255) i=0;
  for (int i=0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, c);
  }
  strip.show();
  delay(20);
*/
}


