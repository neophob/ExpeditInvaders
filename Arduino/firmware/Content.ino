byte bufferRnd[BUFFER_SIZE];

void initContent() {
  for (int i=0; i < BUFFER_SIZE; i++) {
    bufferRnd[i] = random(0, 255);
  }
}

// --------------------------------------------
//     do some animation 
// --------------------------------------------
byte n;
void generateContent() {
//  delay(1);

  for (int i=0; i < BUFFER_SIZE; i++) {
    buffer[i] = bufferRnd[i]+n;
  }

  n++;
  n++;
  n++;
  n++;

}


