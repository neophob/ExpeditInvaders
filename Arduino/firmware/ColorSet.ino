
unsigned long colors[3];

//get array size
#define nrOfColorsInArray (sizeof(colors)/sizeof(unsigned long)) 

byte boarderCount;
byte arrayCount;

//----------------------------
// Color, convert 8bit to 5bit
//----------------------------
unsigned int Color(byte r, byte g, byte b) {
  return( ((unsigned int)g >> 3 )<<10 | ((unsigned int)b >> 3)<<5 | (unsigned int)r >> 3);
}

//----------------------------
//init color set
//----------------------------
void initColorSet(unsigned long col[3]) {
  //copy array.. memcpy? never heard of it...
  for (byte b=0; b<3; b++) {
    colors[b] = col[b];
  }

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
unsigned int calcSmoothColor(unsigned long col1, unsigned long col2, byte pos) {
  unsigned int b= col1&255;
  unsigned int g=(col1>>8)&255;
  unsigned int r=(col1>>16)&255;
  unsigned int b2= col2&255;
  unsigned int g2=(col2>>8)&255;
  unsigned int r2=(col2>>16)&255;

  unsigned int mul=pos*arrayCount;        //extend pos to 255, so pos is between 0..255
  unsigned int oppositeColor = 255-mul;

  r=(r*mul + r2*oppositeColor) >> 8;
  g=(g*mul + g2*oppositeColor) >> 8;
  b=(b*mul + b2*oppositeColor) >> 8;

  /*#ifdef USE_SERIAL_DEBUG
   Serial.print("r: ");
   Serial.print(r);
   Serial.print(", g: ");
   Serial.print(g);
   Serial.print(", b: ");
   Serial.println(b);
   #endif  */

  //change next line
  return Color(b,r,g);
}

//----------------------------
//apply color
//----------------------------
void applyColorSet() {
  byte srcOfs = -1;

  for (int i=0; i < strip.numPixels()-1; i++) {
    if (i%LED_GROUP==0) {
      srcOfs++;
    }

    //make sure the blind pixels are ignored
    if (srcOfs==5) {
      srcOfs++;
    }
    unsigned int col = getSmoothColor(buffer[srcOfs]);    

    //the first pixel is unused
    strip.setPixelColor(i+1, col);
  }

  //blank unused modules
  strip.setPixelColor(0, 0);
  strip.setPixelColor(13, 0);
  strip.setPixelColor(14, 0);
  strip.setPixelColor(15, 0);

  strip.show();    
}

//----------------------------
//load colorset
//----------------------------
void loadColorSet(byte colorMode) {
  unsigned long initialColor[3] = { 
    0xff0000, 0x00ff00, 0x0000ff   }; //RGB
 
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

