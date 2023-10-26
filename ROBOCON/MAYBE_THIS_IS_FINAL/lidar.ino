void getTFminiData1(double* distance1, double* strength1, bool* complete) {
  static char i = 0;
  char j = 0;
  int checksum = 0; 
  static int rx[9];

  if(Serial.available()) {  
    rx[i] = Serial.read();
    if(rx[0] != 0x59) {
      i = 0;
    } else if(i == 1 && rx[1] != 0x59) {
      i = 0;
    } else if(i == 8) {
      for(j = 0; j < 8; j++) {
        checksum += rx[j];
      }
      if(rx[8] == (checksum % 256)) {
        *distance1 = rx[2] + rx[3] * 256;
        *strength1 = rx[4] + rx[5] * 256;
        *complete = true;
      }
      i = 0;
    } else {
      i++;
    } 
  }  
}
void getTFminiData2(double* distance2, double* strength2, bool* complete) {
  static char i = 0;
  char j = 0;
  int checksum = 0; 
  static int rx[9];

  if(Serial2.available()) {  
    rx[i] = Serial2.read();
    if(rx[0] != 0x59) {
      i = 0;
    } else if(i == 1 && rx[1] != 0x59) {
      i = 0;
    } else if(i == 8) {
      for(j = 0; j < 8; j++) {
        checksum += rx[j];
      }
      if(rx[8] == (checksum % 256)) {
        *distance2 = rx[2] + rx[3] * 256;
        *strength2 = rx[4] + rx[5] * 256;
        *complete = true;
      }
      i = 0;
    } else {
      i++;
    } 
  }  
}