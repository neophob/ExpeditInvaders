byte bufferRnd[BUFFER_SIZE];

void initContent() {
  for (int i=0; i < BUFFER_SIZE; i++) {
    bufferRnd[i] = random(0, 255);
  }
}

#define MAX_MODE 5
byte n;
byte mode = 3;


// --------------------------------------------
//     do some animation 
// --------------------------------------------
void generateContent() {
  delay(256);

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
    case 4: //weird
      buffer[i] = n+(32*(i%4));
      break;     
    case 5: //
      buffer[i] = n+(16*(i%8));
      break;     
    }

  }
  n++;
  
  //convert it to colorized 15bit buffer and blank some pixels
  applyColorSet();


}





