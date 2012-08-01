
int colors[3];

//get array size
#define nrOfColorsInArray (sizeof(colors)/sizeof(int)) 

byte boarderCount;
byte arrayCount;

void initColorSet(int col[3]) {
  memcpy(colors, col, sizeof(col));
  arrayCount = nrOfColorsInArray;
  boarderCount = 255 / arrayCount;
}

int getSmoothColor(byte pos) {
  byte ofs=0;
  while (pos>boarderCount) {
    pos -= boarderCount;
    ofs++;
  }

  byte targetOfs = ofs+1;
  return calcSmoothColor(colors[targetOfs%arrayCount], colors[ofs%arrayCount], pos);
}

int calcSmoothColor(int col1, int col2, int pos) {
  int b= col1&255;
  int g=(col1>>8)&255;
  int r=(col1>>16)&255;
  int b2= col2&255;
  int g2=(col2>>8)&255;
  int r2=(col2>>16)&255;

  int mul=pos*arrayCount;
  int oppositeColor = 255-mul;
  r=(r*mul)/255;
  g=(g*mul)/255;
  b=(b*mul)/255;
  r+=(r2*oppositeColor)/255;
  g+=(g2*oppositeColor)/255;
  b+=(b2*oppositeColor)/255;

  return (r << 16) | (g << 8) | (b);
}

void applyColorSet() {
  byte srcOfs = -1;
  
  for (int i=0; i < strip.numPixels(); i++) {
    if (i%LED_GROUP==0) {
      srcOfs++;
    }
    strip.setPixelColor(i, getSmoothColor(buffer[srcOfs]));    
  }
  strip.show();    
}

