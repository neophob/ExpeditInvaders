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
 */

//the lpd6803 library needs the timer1 library
#include <TimerOne.h>
#include <SPI.h>
#include <Neophob_LPD6803.h>

#define NR_OF_PIXELS 20

//one pixel uses 3 leds
#define LED_GROUP 3
#define BUFFER_SIZE 7  //NR_OF_PIXELS/BUFFER_SIZE

const uint8_t ledPin = 9;

//initialize pixels 9*20
Neophob_LPD6803 strip = Neophob_LPD6803(NR_OF_PIXELS);
byte buffer[BUFFER_SIZE];

byte g_errorCounter;
int j,k;


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
void showInitImage() {
  for (int i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel( i % 96));
  }    
  // Update the strip, to start they are all 'off'
  strip.show();
}


// --------------------------------------------
//      setup
// --------------------------------------------
void setup() {
  //cpu use and SPI clock must be adjusted
  strip.setCPUmax(25);  // start with 50% CPU usage. up this if the strand flickers or is slow  
  strip.begin(SPI_CLOCK_DIV128);        // Start up the LED counterm 0.125MHz - 8uS
//  strip.begin(SPI_CLOCK_DIV64);        // Start up the LED counterm 0.25MHz - 4uS
//  strip.begin(SPI_CLOCK_DIV32);        // Start up the LED counterm 0.5MHz - 2uS
//  strip.begin(SPI_CLOCK_DIV16);        // Start up the LED counterm 1.0MHz - 1uS
  showInitImage();      // display some colors
  int initialColor[] = { 0xff0000, 0x00ff00, 0x0000ff };
  initColorSet(initialColor);
  
  //we-are-ready indicator
  pinMode(ledPin, OUTPUT);  
  synchronousBlink();
  delay(50);
  synchronousBlink();
}

// --------------------------------------------
//      main loop
// --------------------------------------------
void loop() {
  generateContent(); 
  applyColorSet();
}


