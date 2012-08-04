byte bufferRnd[BUFFER_SIZE];

void initContent() {
  for (int i=0; i < BUFFER_SIZE; i++) {
    bufferRnd[i] = random(0, 255);
  }
}

byte n;
byte mode = 0;

// --------------------------------------------
//     do some animation 
// --------------------------------------------
void generateContent() {
  delay(50);

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
    }

  }

  n++;
  
  //convert it to colorized 15bit buffer and blank some pixels
  applyColorSet();


}





