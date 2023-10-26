void getTFminiData1(double * distance, double * strength, boolean * complete) {
  static char i = 0;
  char j = 0;
  int checksum = 0;
  static int rx[9];

  //  port->listen();
  if (Serial1.available()) {
    rx[i] = Serial1.read();
    if (rx[0] != 0x59) {
      i = 0;
    } else if (i == 1 && rx[1] != 0x59) {
      i = 0;
    } else if (i == 8) {
      for (j = 0; j < 8; j++) {
        checksum += rx[j];
      }
      if (rx[8] == (checksum % 256)) {
        *distance = rx[2] + rx[3] * 256;
        *strength = rx[4] + rx[5] * 256;
        *complete = true;
      }
      i = 0;
    } else {
      i++;
    }
  }
}
void getTFminiData2(double * distance, double * strength, boolean * complete) {
  static char i = 0;
  char j = 0;
  int checksum = 0;
  static int rx[9];

  //  port->listen();
  if (Serial1.available()) {
    rx[i] = Serial1.read();
    if (rx[0] != 0x59) {
      i = 0;
    } else if (i == 1 && rx[1] != 0x59) {
      i = 0;
    } else if (i == 8) {
      for (j = 0; j < 8; j++) {
        checksum += rx[j];
      }
      if (rx[8] == (checksum % 256)) {
        *distance = rx[2] + rx[3] * 256;
        *strength = rx[4] + rx[5] * 256;
        *complete = true;
      }
      i = 0;
    } else {
      i++;
    }
  }
}