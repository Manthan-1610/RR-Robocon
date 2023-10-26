#include <SoftwareSerial.h>
#include <PID_v1.h>
SoftwareSerial portOne(66, 67);
SoftwareSerial portTwo(68, 69);

#define BLed 40
#define GLed 41
#define M1_PWM 12
#define M1_DIR 50
#define M2_PWM 11
#define M2_DIR 51
#define M3_PWM 10
#define M3_DIR 52
#define M4_DIR 53
#define M4_PWM 9

int DIR;
int pwm;
int max_pwm = 50;//actual distance measurements of LiDAR
int i;
double set_posx = 42;
double outputx;
double kpx = 9;
double kdx = 0.7;
double kix = 0.4;
double set_posy = 43;
double outputy;
double kpy = 9;
double kdy = 0.7;
double kiy = 0.4;
double set_posd;
double outputd;
double kpd = 6;
double kdd = 0;
double kid = 0.55;
double distance1 = 0;
double strength1 = 0;
boolean receiveComplete1 = false;
double arr[10];
double distance2 = 0;
double strength2 = 0;
boolean receiveComplete2 = false;
double deg;
unsigned long currenttime;
unsigned long previoustime = 0;
unsigned long interval;
double var = 0;
boolean ans = false;
int time = 0;
double avg = 0;
double sum = 0;
//double currentime;
//double prevvioustime;
//double interval;
PID PIDX(&distance1, &outputx, &set_posx, kpx, kdx, kix, DIRECT);
PID PIDY(&distance2, &outputy, &set_posy, kpy, kdy, kiy, DIRECT);
PID PIDDEG(&deg, &outputd, &set_posd, kpd, kdd, kid, DIRECT);

void setup() {
  Serial.begin(115200);
  portOne.begin(115200);
  portTwo.begin(115200);
  Serial2.begin(9600);
  PIDX.SetMode(AUTOMATIC);
  PIDY.SetMode(AUTOMATIC);
  PIDDEG.SetMode(AUTOMATIC);
  PIDX.SetOutputLimits(-255, 255);
  PIDY.SetOutputLimits(-255, 255);
  PIDDEG.SetOutputLimits(-255, 255);
}

void loop() {
  if (Serial2.available() > 0) {
    delay(4);
    sum = 0;
    avg = 0;
    for (int i = 0; i < 10; i++) {
      String x = Serial2.readStringUntil('\n');
      var = x.toInt();
      if (var < 40 && var > -40) {
        deg = var;
        arr[i] = deg;
        sum = sum + arr[i];
      }
    }
    avg = sum / 10;
    Serial.print("Sum=");
    Serial.println(sum);
    Serial.print("Degree=");
    Serial.println(deg);
  }
  Serial.print("Average=");
  Serial.println(avg);
  setdegree();
  //if(avg==0){
  while (!receiveComplete1) {
    getTFminiData(&portOne, &distance1, &strength1, &receiveComplete1);
  }
  setposx();
  receiveComplete1 = false;
  while (!receiveComplete2) {
    getTFminiData(&portTwo, &distance2, &strength2, &receiveComplete2);
  }
  setposy();
  receiveComplete2 = false;
  //}
  Serial.print("Distance1 = ");
  Serial.print(distance1);
  Serial.print("Distance2 = ");
  Serial.println(distance2);
  timelimit(4000);
  if ((distance1 <= 43 && distance1 >= 41) && (distance2 <= 43 && distance2 >= 41) ) {
    if (time == 1 && (avg == 0)) {
      kpd = 0;
      kdd = 0;
      kid = 0;
      kpx = 0;
      kdx = 0;
      kix = 0;
      kiy = 0;
      kpy = 0;
      kdy = 0;
      max_pwm = 0;
      Hold();
    }
  }
}

void timelimit(double interval)
{
  currenttime = millis();
  if (currenttime - previoustime <= interval)
  {
    time = 1;
  }
  else
  {
    time = 0;
  }
  previoustime = currenttime;
}

void setdegree() {
  PIDDEG.SetMode(AUTOMATIC);
  PIDDEG.SetTunings(kpd, kdd, kid);
  PIDDEG.Compute();
  pwm_cap(outputd);
  if (outputd > 0) {
    Left_rotate(pwm);
  }
  else if (outputd < 0) {
    Right_rotate(pwm);
  }
}

void setposy()
{
  PIDY.SetMode(AUTOMATIC);
  PIDY.SetTunings(kpy, kdy, kiy);
  PIDY.Compute();
  pwm_cap(outputy);
  if (outputy > 0 && outputy < 900)
  {
    Forward(pwm);
  }
  else if (outputy < 0)
  {
    Backward(pwm);
  }
}

void setposx()
{
  PIDX.SetMode(AUTOMATIC);
  PIDX.SetTunings(kpx, kdx, kix);
  PIDX.Compute();
  pwm_cap(outputx);
  if (outputx > 0)
  {
    Right(pwm);
  }
  else if (outputx < 0)
  {
    Left(pwm);
  }
}

void pwm_cap(int output) {
  if (output >= max_pwm || output <= -max_pwm)
  {
    pwm = max_pwm;
  }
  else
  {
    pwm = abs(output);
  }
}

void getTFminiData(SoftwareSerial* port, double* distance, double* strength, boolean* complete) {
  static char i = 0;
  char j = 0;
  int checksum = 0;
  static int rx[9];

  port->listen();
  if (port->available()) {
    rx[i] = port->read();
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
void Forward(int pwm) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, HIGH);
  analogWrite(M4_PWM, pwm);
  analogWrite(M1_PWM, pwm);
  analogWrite(M2_PWM, pwm);
  analogWrite(M3_PWM, pwm);

}
void Backward(int pwm) {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, HIGH);
  digitalWrite(M3_DIR, HIGH);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_PWM, pwm);
  analogWrite(M1_PWM, pwm);
  analogWrite(M2_PWM, pwm);
  analogWrite(M3_PWM, pwm);
}
void Right(int pwm) {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, HIGH);
  digitalWrite(M4_DIR, HIGH);
  analogWrite(M4_PWM, pwm);
  analogWrite(M1_PWM, pwm);
  analogWrite(M2_PWM, pwm);
  analogWrite(M3_PWM, pwm);
}
void Left(int pwm) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, HIGH);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_PWM, pwm);
  analogWrite(M1_PWM, pwm);
  analogWrite(M2_PWM, pwm);
  analogWrite(M3_PWM, pwm);
}
void Forward_left(int pwm) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, HIGH);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_PWM, 0);
  analogWrite(M1_PWM, pwm);
  analogWrite(M2_PWM, 0);
  analogWrite(M3_PWM, pwm);
}
void Forward_right(int pwm) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, HIGH);
  analogWrite(M4_PWM, pwm);
  analogWrite(M1_PWM, 0);
  analogWrite(M2_PWM, pwm);
  analogWrite(M3_PWM, 0);
}
void Backward_left(int pwm) {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, HIGH);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_PWM, pwm);
  analogWrite(M1_PWM, 0);
  analogWrite(M2_PWM, pwm);
  analogWrite(M3_PWM, 0);
}
void Backward_right(int pwm) {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, HIGH);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_PWM, 0);
  analogWrite(M1_PWM, pwm);
  analogWrite(M2_PWM, 0);
  analogWrite(M3_PWM, pwm);
}
void Right_rotate(int pwm) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, HIGH);
  digitalWrite(M3_DIR, HIGH);
  digitalWrite(M4_DIR, HIGH);
  analogWrite(M4_PWM, pwm);
  analogWrite(M1_PWM, pwm);
  analogWrite(M2_PWM, pwm);
  analogWrite(M3_PWM, pwm);
}
void Left_rotate(int pwm) {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_PWM, pwm);
  analogWrite(M1_PWM, pwm);
  analogWrite(M2_PWM, pwm);
  analogWrite(M3_PWM, pwm);
}
void Hold() {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_PWM, 0);
  analogWrite(M1_PWM, 0);
  analogWrite(M2_PWM, 0);
  analogWrite(M3_PWM, 0);
}
