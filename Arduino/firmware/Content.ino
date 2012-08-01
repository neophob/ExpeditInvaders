
unsigned int Color(byte r, byte g, byte b) {
  //Take the lowest 5 bits of each value and append them end to end
  return( ((unsigned int)g & 0x1F )<<10 | ((unsigned int)b & 0x1F)<<5 | (unsigned int)r & 0x1F);
}

// --------------------------------------------
//     Input a value 0 to 127 to get a color value.
//     The colours are a transition r - g -b - back to r
// --------------------------------------------
unsigned int Wheel(byte WheelPos) {
  byte r,g,b;
  switch(WheelPos >> 5) {
  case 0:
    r=31- WheelPos % 32;   //Red down
    g=WheelPos % 32;      // Green up
    b=0;                  //blue off
    break; 
  case 1:
    g=31- WheelPos % 32;  //green down
    b=WheelPos % 32;      //blue up
    r=0;                  //red off
    break; 
  case 2:
    b=31- WheelPos % 32;  //blue down 
    r=WheelPos % 32;      //red up
    g=0;                  //green off
    break; 
  }
  return(Color(r,g,b));
}

// --------------------------------------------
//     do some animation 
// --------------------------------------------
void generateContent() {
  delay(1);

  k++;
  if (k>50) {
    k=0;
    j++;
    if (j>255) {  // 3 cycles of all 96 colors in the wheel
      j=0; 
    }

    for (int i=0; i < BUFFER_SIZE; i++) {
      strip.setPixelColor(i, Wheel((i + j) % 96));
      buffer[i] = (i+j)%0xff;
    }
  }
}


