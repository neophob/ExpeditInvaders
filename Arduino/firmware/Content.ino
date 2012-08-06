byte bufferRnd[BUFFER_SIZE];

void initContent() {
  for (int i=0; i < BUFFER_SIZE; i++) {
    bufferRnd[i] = random(0, 255);
  }
}

#define MAX_MODE 3
byte n;
byte mode = 3;

#define MAX_COLOR_MODE 3
byte colorMode = 0;

// --------------------------------------------
//     do some animation 
// --------------------------------------------
void generateContent() {
//  delay(20);

  for (int i=0; i < BUFFER_SIZE; i++) {
    switch (mode) {
    case 0: //random color animation
      buffer[i] = bufferRnd[i]+n;
      break;     
    case 1: //ordered color animation
      buffer[i] = n+i;
      break;     
    case 2: //solid color animation
      buffer[i] = n;
      break;     
    case 3: //checkboard
      buffer[i] = n+(128*(i%2));
      break;     
    }

  }
  n++;
  
  //convert it to colorized 15bit buffer and blank some pixels
  applyColorSet();


}





