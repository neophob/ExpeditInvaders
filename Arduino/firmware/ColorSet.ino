
unsigned long colors[3];

//get array size
#define nrOfColorsInArray (sizeof(colors)/sizeof(unsigned long)) 

byte boarderCount;
byte arrayCount;

//----------------------------
//Color 8bit to 5 bit
//----------------------------
unsigned int Color(byte r, byte g, byte b) {
  //Take the lowest 5 bits of each value and append them end to end
  return( ((unsigned int)g >> 3 )<<10 | ((unsigned int)b >> 3)<<5 | (unsigned int)r >> 3);
}

//----------------------------
//init color set
//----------------------------
void initColorSet(unsigned long col[]) {
  //TODO works not
  memcpy(colors, col, nrOfColorsInArray*sizeof(unsigned long));
#ifdef USE_SERIAL_DEBUG
  Serial.print("initColorSet src: ");
  Serial.print(col[2]);
  Serial.print(", dst: ");
  Serial.println(colors[2]);
#endif
 /* 
 colors[0] = 0xff0000;
 colors[1] = 0x00ff00;
 colors[2] = 0x0000ff;
 */  
  colors[0] = 0xd3517d;
  colors[1] = 0x15a0bf;
  colors[2] = 0xffc062;

  arrayCount = nrOfColorsInArray;
  boarderCount = 255 / arrayCount;
#ifdef USE_SERIAL_DEBUG
  Serial.print("boarderCount: ");
  Serial.println(boarderCount);
#endif 
}

//----------------------------
//calc smooth color
//----------------------------
unsigned int getSmoothColor(byte pos) {
  byte ofs=0;
  while (pos>boarderCount) {
    pos -= boarderCount;
    ofs++;
  }

  byte targetOfs = ofs+1;
  return calcSmoothColor(colors[targetOfs%arrayCount], colors[ofs%arrayCount], pos);
}

//----------------------------
//calc smooth color
//----------------------------
unsigned int calcSmoothColor(unsigned long col1, unsigned long col2, int pos) {
#ifdef USE_SERIAL_DEBUG
  Serial.print("calcSmoothColor col1: ");
  Serial.print(col1, HEX);
  Serial.print(", col2: ");
  Serial.print(col2, HEX);
  Serial.print(", pos: ");
  Serial.println(pos);
#endif  

  unsigned int b= col1&255;
  unsigned int g=(col1>>8)&255;
  unsigned int r=(col1>>16)&255;
  unsigned int b2= col2&255;
  unsigned int g2=(col2>>8)&255;
  unsigned int r2=(col2>>16)&255;

  unsigned int mul=pos*arrayCount;
  unsigned int oppositeColor = 255-mul;

  r=(r*mul)/255;
  g=(g*mul)/255;
  b=(b*mul)/255;
  r+=(r2*oppositeColor)/255;
  g+=(g2*oppositeColor)/255;
  b+=(b2*oppositeColor)/255;

  //change next line
  return Color(r,g,b);
}

//----------------------------
//apply color
//----------------------------
void applyColorSet() {
  byte srcOfs = -1;

  for (int i=0; i < strip.numPixels(); i++) {
    if (i%LED_GROUP==0) {
      srcOfs++;
    }
    unsigned int col = getSmoothColor(buffer[srcOfs]);    

#ifdef USE_SERIAL_DEBUG
    Serial.print("Update Pixel ");
    Serial.print(i);
    Serial.print(", set Color: ");
    Serial.println(col, HEX);
#endif  
    strip.setPixelColor(i, col);

  }
  strip.show();    
}


