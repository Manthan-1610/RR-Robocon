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
int max_pwm = 60;//actual distance measurements of LiDAR
int i;
double set_posx = 42;
double outputx;
double kpx = 11;
double kdx = 1.2;
double kix = 0.4;
double set_posy = 43;
double outputy;
double kpy = 9;
double kdy = 0.8;
double kiy = 0.3;
double set_posd = 0;
int outputd;
double kpd = 10;
double kdd = 0;
double kid = 1;
double distance1 = 0;
double strength1 = 0;
double currenttimed=0;
double previoustimed=0;
double timechanged=0;
double current_posd;
double errord;
double dtermd;
double previouserrord;
double itermd;
boolean receiveComplete1 = false;
boolean degree=true;
double distance2 = 0;
double strength2 = 0;
boolean receiveComplete2 = false;
int deg;
unsigned long currenttime;
unsigned long previoustime = 0;
unsigned long interval;
PID PIDX(&distance1, &outputx, &set_posx, kpx, kdx, kix, DIRECT);
PID PIDY(&distance2, &outputy, &set_posy, kpy, kdy, kiy, DIRECT);
//PID PIDDEG(&deg, &outputd, &set_posd, kpd, kdd, kid, DIRECT);

void setup() {
  Serial.begin(115200);
  portOne.begin(115200);
  portTwo.begin(115200);
  Serial2.begin(9600);
  PIDX.SetMode(MANUAL);
  PIDY.SetMode(AUTOMATIC);
 // PIDDEG.SetMode(AUTOMATIC);
  PIDX.SetOutputLimits(-255, 255);
  PIDY.SetOutputLimits(-255, 255);
//  PIDDEG.SetOutputLimits(-255, 255);
}

void loop() {
   if (Serial2.available() > 0) {
    delay(10);
    String x = Serial2.readStringUntil('\n');
    deg = x.toInt();
  }
  setdegree();
 
  //setdeg();
  
  while (!receiveComplete1) {
    getTFminiData(&portOne, &distance1, &strength1, &receiveComplete1);
  }
  receiveComplete1 = false;
  
  while (!receiveComplete2) {
    getTFminiData(&portTwo, &distance2, &strength2, &receiveComplete2);
  }
  receiveComplete2 = false;
if(deg==0){
setposx();
if(distance1<=41 && distance2>=39){
setposy();
}
}
else{
  continue;                   
  }
  currenttime = millis();

  Serial.print("distance x =  ");
  Serial.print(distance1);
  Serial.print("output = ");
  Serial.print(outputx);
    Serial.print("Degree =");
  Serial.println(deg);

  if (distance1 == 40 && distance2 == 40)
  {
    Hold();
  }

}
void timelimit(int interval)
{
  if (currenttime - previoustime <= interval)
  {
    int timelimit = 1;
  }
  else
  {
    int timelimit = 0;
  }

}
//void setdeg()
//{
//  PIDDEG.SetMode(AUTOMATIC);
//  PIDDEG.SetTunings(kpd, kdd, kid);
//  PIDDEG.Compute();
//  if(outputd<30 && outputd>-30){
//  pwm_cap(outputd);
//  if (outputd > 0)
//  {
//    Left_rotate(pwm);
//  }
//  else if (outputd < 0)
//  {
//    Right_rotate(pwm);
//  }
//}
//}
void setdegree(){
  pidoutputd(set_posd,kpd,kdd,kix);
  if(outputd<30 && outputd>-30){
    pwm_cap(outputd);
    if(outputd>0){
      Left_rotate(pwm);
      }
      else if(outputd<0){
        Right_rotate(pwm);
        }
    }
  }
void pidoutputd(int set_posd, double kpd, double kdd, double kid)
{
  currenttimed = micros();
  timechanged = (currenttimed - previoustimed) / 1000000;
  previoustimed = currenttimed;
  current_posd = deg;
  errord = set_posd - current_posd;
  dtermd = (errord - previouserrord) / (timechanged * 100);
  itermd = itermd + errord * timechanged;
  outputd = kpd * errord + kdd * dtermd + kid * itermd;
  previouserrord = errord;
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
    int output_array[2];
    int x;
    for (x = 0; x < 3; x++);
    {
      output_array[x] = output;
    }
    int avgoutput = abs((output_array[0] + output_array[1] + output_array[2]) / 3);
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
