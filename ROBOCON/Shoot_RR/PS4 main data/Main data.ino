#include <SoftwareSerial.h>
#include <Servo.h>
#include <PID_v1.h>
Servo myServo;
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];
boolean newData = false;
char button_value[0];
unsigned int l_value = 0;
unsigned int r_value = 0;
signed int l_y_value = 0;
signed int r_x_value = 0;
int pwm;
int max_pwm=70;
int pin1,dcm1,dcm2;
boolean pidset;
int pin = 2;
int state;
int count = 0;
double set_posx = 42;
double outputx;
double kpx = 9;
double kdx = 0.7;
double kix = 0.4;
double set_posy = 42;
double outputy;
double kpy = 9;
double kdy = 0.7;
double kiy = 0.4;
boolean receiveComplete1 = false;
boolean receiveComplete2 = false;
double distance1 = 0;
double strength1 = 0;
double distance2 = 0;
double strength2 = 0;
int servopos;
PID PIDX(&distance1, &outputx, &set_posx, kpx, kdx, kix, DIRECT);
PID PIDY(&distance2, &outputy, &set_posy, kpy, kdy, kiy, DIRECT);
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  myServo.attach(9);
  PIDX.SetMode(AUTOMATIC);
  PIDY.SetMode(AUTOMATIC);
  PIDX.SetOutputLimits(-255, 255);
  PIDY.SetOutputLimits(-255, 255);
  attachInterrupt(digitalPinToInterrupt(pin), InterruptFunction, HIGH);
  pinMode(13,OUTPUT);
  pinMode(pin,INPUT);
}

void loop() {
  //label:
  ps4_data();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    split_data();
    newData = false;
  }
  pidset=true; 
  Serial.print(button_value);
  Serial.print(',');
  Serial.print(l_value);
  Serial.print(',');
  Serial.print(r_value);
  Serial.print(',');
  Serial.print(l_y_value);
  Serial.print(',');
  Serial.println(r_x_value);

  if (l_value > 10) {
    int lrpwm = map(l_value, 10, 255, 0, 150);
    Left_rotate(lrpwm);
  } else if (r_value > 10) {
    int rrpwm = map(r_value, 10, 255, 0, 150);
    Right_rotate(rrpwm);
  } else if (l_y_value < -10) {
    int bpwm = map(l_y_value, -10, -127, 0, 150);
    Backward(bpwm);
  } else if (l_y_value > 10) {
    int fpwm = map(l_y_value, 10, 127, 0, 150);
    Forward(fpwm);
  } else if (r_x_value > 10) {
    int rpwm = map(r_x_value, 10, 127, 0, 150);
    Right(rpwm);
  } else if (r_x_value < -10) {
    int lpwm = map(r_x_value, -10, -127, 0, 150);
    Left(lpwm);
  }
  if (button_value[0] == 'A') {
    if (count % 2 == 0) {
      digitalWrite(pin1, HIGH);
      digitalWrite(dcm1, LOW);
      digitalWrite(dcm2, HIGH);
      delay(2000);
      digitalWrite(dcm1, LOW);
      digitalWrite(dcm2, LOW);
      delay(200);
      digitalWrite(pin1, LOW);
    } else {
      //    digitalWrite(pin1,LOW);
      digitalWrite(dcm1, HIGH);
      digitalWrite(dcm2, LOW);
      delay(2000);
      digitalWrite(dcm1, HIGH);
      digitalWrite(dcm2, HIGH);
      // delay(200);
      digitalWrite(pin1, HIGH);
    }
    count++;
  } else if (button_value[0] == 'B') {
    Serial2.println("B");
  //   while(pidset){
  //   while (!receiveComplete1) {
  //     getTFminiData1(&distance1, &strength1, &receiveComplete1);
  //   }
  //   receiveComplete1 = false;
  //   setposx();
  //   if (distance1 < 43 && distance1 > 39) {
  //     myServo.write(90);
  //   }
  //   servopos = myServo.read();
  //   if (distance1 < 43 && distance1 > 39 && servopos == 90) {
  //     while (!receiveComplete2) {
  //       getTFminiData2(&distance2, &strength2, &receiveComplete2);
  //     }
  //     setposy();
  //     receiveComplete2 = false;
  //   }
  //   Serial.print("Distance1 = ");
  //   Serial.print(distance1);
  //   Serial.print("Distance2 = ");
  //   Serial.print(distance2);
  // }
}
 else {
    Hold();
  }
}
 void InterruptFunction(){
  //pidset=false;
  // digitalWrite(pin,LOW);
  // loop();
  digitalWrite(13,HIGH);
  Hold();
  pidset = false;
}