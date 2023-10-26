#include <SoftwareSerial.h>
#include <Servo.h>
#include <PID_v1.h>
#include <AccelStepper.h>
long anglex[9] = { 1, 20, 30};
long angley[9] = { 1, 20, 30};
long anglex1[9] = { 1, 20, 30};
long angley1[9] = { 1, 20, 30};
Servo myServo;
Servo esc1;
Servo esc2;
Servo esc3;
Servo esc4;
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];
bool newData = false;
char button_value[0];
unsigned int l_value = 0;
unsigned int r_value = 0;
signed int l_y_value = 0;
signed int r_x_value = 0;
int pwm;
const int stepPin1 = 45;
const int dirPin1 = 43;
const int stepPin3 = 33;
const int dirPin3 = 31;
const int stepPin4 = 27;
const int dirPin4 = 25;
long angle1, angle2, angle3, angle4;
const int stepPin2 = 39;
const int dirPin2 = 37;
const int stepsPerRev = 3200;
int dcm1 = 52;
int dcm2 = 50;
int dcm3 = 48;
int dcm4 = 46;
int pin1 = 44;
int pin2 = 42;
int pin3 = 40;
int pin4 = 38;
int johnsonr1 = 36;
int johnsonr2 = 34;
int johnsonl1 = 32;
int johnsonl2 = 30;
int limitswitch1 = 55;
int limitswitch2 = 56;
int limitswitch3 = 57;
int limitswitch4 = 58;
int limitswitch5 = 59;
int limitswitch6 = 60;
int limitswitch7 = 61;
int limitswitch8 = 62;
int limitswitch9 = 63;
int limitswitch10 = 64;
bool enter = true;
bool pidset;
int pin = 2;
bool servo = false;
int state;
int count = 0;
int count1 = 0;
int count2 = 0;
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
bool receiveComplete1 = false;
bool receiveComplete2 = false;
double distance1 = 0;
double strength1 = 0;
double distance2 = 0;
double strength2 = 0;
int servopos;
int interval1 = 2000;
int currenttime = 0;
int previoustime = 0;
bool shoot = true;
AccelStepper stepper1(AccelStepper::DRIVER, stepPin1, dirPin1, 41);
AccelStepper stepper2(AccelStepper::DRIVER, stepPin2, dirPin2, 35);
AccelStepper stepper3(AccelStepper::DRIVER, stepPin3, dirPin3, 29);
AccelStepper stepper4(AccelStepper::DRIVER, stepPin4, dirPin4, 23);
PID PIDX(&distance1, &outputx, &set_posx, kpx, kdx, kix, DIRECT);
//PID PIDY(&distance2, &outputy, &set_posy, kpy, kdy, kiy, DIRECT);

void setup() {
  pins();
}

void loop() {

  //GETTING PS4 DATA
  ps4_data();

// SPLITTING PS4 DATA
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    split_data();
    newData = false;
  }
  // digitalRead(limitswitch1);
  // digitalRead(limitswitch2);
  int leftpickmax = digitalRead(limitswitch3);
  int leftpickmin = digitalRead(limitswitch4);
  int johnny1 = digitalRead(limitswitch5);
  int johnny2 = digitalRead(limitswitch6);
  // digitalRead(limitswitch5);
  // digitalRead(limitswitch6);
  // digitalRead(limitswitch7);
  // digitalRead(limitswitch8);
  // digitalRead(limitswitch9);
  // digitalRead(limitswitch10);
  // pidset = true;
  Serial.print(button_value);
  Serial.print(',');
  Serial.print(l_value);
  Serial.print(',');
  Serial.print(r_value);
  Serial.print(',');
  Serial.print(l_y_value);
  Serial.print(',');
  Serial.println(r_x_value);
  myServo.write(90);
// PICKUP MECHANISM FOR LEFT 
  if (button_value[0] == 'O') { 
    digitalWrite(pin1, HIGH);
    digitalWrite(dcm1, LOW);
    digitalWrite(dcm2, HIGH);
  } 

  // PICKUP MECHANISM FOR RIGHT 
  else if (button_value[0] == 'C') {
    digitalWrite(pin2, HIGH);
    digitalWrite(dcm3, LOW);
    digitalWrite(dcm4, HIGH);
  }

// LOADING MECHANISM FOR LEFT 
   else if (button_value[0] == 'B') {
    digitalWrite(pin1, LOW);
    digitalWrite(dcm1, HIGH);
    digitalWrite(dcm2, LOW);
  } 
  
// LOADING MECHANISM FOR RIGHT   
  else if (button_value[0] == 'D') {
    digitalWrite(pin2, LOW);
    digitalWrite(dcm3, HIGH);
    digitalWrite(dcm4, LOW);
  } 
  
// EXPANDING AND CONTRACTION OUR ROBOT
  else if (button_value[0] == 'K') {
    if(count%2==0){
    digitalWrite(johnsonl1, HIGH);
    digitalWrite(johnsonl2, LOW);
    digitalWrite(johnsonr1, HIGH);
    digitalWrite(johnsonr2, LOW);
    }
    else{
    digitalWrite(johnsonl1, LOW);
    digitalWrite(johnsonl2, HIGH);
    digitalWrite(johnsonr1, LOW);
    digitalWrite(johnsonr2, HIGH);
    }
  }
  count++;

// SETTING PID OF ROBOT
  if (button_value[0] == 'A') {
    while (pidset == true) {
      while (!receiveComplete1) {
        getTFminiData1(&distance1, &strength1, &receiveComplete1);
      }
      receiveComplete1 = false;
      setposx();
      if(distance1 == abs(40)){
        myServo.write(0);
      }
      servopos = myServo.read();
      if(servopos==0){
        while (!receiveComplete1) {
          getTFminiData1(&distance1, &strength1, &receiveComplete1);
        }
        receiveComplete1 = false;
        setposx();
        if(distance1==abs(40)){
        myServo.write(0);
        servopos = myServo.read();
        if(servopos==90 && distance1==abs(40)){
          break;  
        }
        }
      }
      // if (distance1 == abs(40)) {
      //   servo = true;
      // }
      // if (servo == true) {
      //   myServo.write(90);
      // }
      // servopos = myServo.read();
      // if (distance1 == abs(40) && servopos == 90) {
      // while (!receiveComplete1) {
      //   getTFminiData1(&distance1, &strength1, &receiveComplete1);
      // }
      // receiveComplete1 = false;
      // setposx();


      // }
      Serial.print("Distance1 = ");
      Serial.print(distance1);
    }
  } 
  
// SHOTTING MECHANISM FOR LEFT
  else if (button_value[0] == 'I') {
    digitalWrite(pin3, HIGH);
    delay(500);
    digitalWrite(pin3, LOW);
  } 
  
// SHOTTING MECHANISM FOR RIGHT
  else if (button_value[0] == 'J') {
    digitalWrite(pin4, HIGH);
    delay(500);
    digitalWrite(pin4, LOW);
  } 
  
// STARTING AND STOPPING OF BLDC MOTOR
  else if (button_value[0] == 'E') {
    if (count2 % 2 == 0) {
      esc1.write(150);
      esc2.write(150);
      esc3.write(150);  // speed ranges from 40 to 150
      esc4.write(150);
      //delay(5000); // 1 second = 1000 so 15 second =15000
    } else {
      esc1.write(30);
      esc2.write(30);
      esc3.write(30);
      esc4.write(30);
    }
  }
  count2++;
  
// SHOTTING TO THE TYPE-1 -- POLE-1 RIGHT MECHANISM
   if (button_value[0] == 'h') {
    angle1 = anglex[0];
    angle2 = angley[0];
    stepangle1(angle1);
    stepangle2(angle2);
}

// SHOTTING TO THE TYPE-1 -- POLE-2 RIGHT MECHANISM
  else if (button_value[0] == 'e') {
    angle1 = anglex[1];
    angle2 = angley[1];
    stepangle1(angle1);
    stepangle2(angle2);
}

// SHOTTING TO THE TYPE-1 -- POLE-3 LEFT MECHANISM 
  else if (button_value[0] == 'b') {
    angle1 = anglex[2];
    angle2 = angley[2];
    stepangle1(angle1);
    stepangle2(angle2);
}

// SHOTTING TO THE TYPE-2 -- POLE-4 RIGHT MECHANISM 
 else if (button_value[0] == 'f') {
    angle3 = anglex[0];
    angle4 = angley[0];
    stepangle3(angle3);
    stepangle4(angle4);
}

// SHOTTING TO THE TYPE-2 -- POLE-5 LEFT MECHANISM 
else if (button_value[0] == 'd') {
    angle3 = anglex[1];
    angle4 = angley[1];
    stepangle3(angle3);
    stepangle4(angle4);
}

// SHOTTING TO THE TYPE-3 -- POLE-6 LEFT MECHANISM 
else if (button_value[0] == 'a') {
    angle3 = anglex[2];
    angle4 = angley[2];
    stepangle3(angle3);
    stepangle4(angle4);
}

// MOVEMENTS USING ANALOG STICK
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
  
// LIMIT SWITCH WORKING
  else {
    pidset = true;
    if (leftpickmax == 0) {
      digitalWrite(dcm1, LOW);
      digitalWrite(dcm2, LOW);
      digitalWrite(dcm3, LOW);
      digitalWrite(dcm4, LOW);
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
    }
    if (leftpickmin == 0) {
      digitalWrite(dcm1, LOW);
      digitalWrite(dcm2, LOW);
      digitalWrite(dcm3, LOW);
      digitalWrite(dcm4, LOW);
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
    }
    if (johnny1 == 0) {
      digitalWrite(johnsonl1, LOW);
      digitalWrite(johnsonl2, LOW);
    }
    if (johnny2 == 0) {
      digitalWrite(johnsonr1, LOW);
      digitalWrite(johnsonr2, LOW);
    }
    Hold();
  }
}


// INTERRUPT GENERATIONS (YET TO IMPLEMENT)
void InterruptFunction() {
  //pidset=false;
  // digitalWrite(pin,LOW);
  // loop();
  digitalWrite(13, HIGH);
  Hold();
  pidset = false;
}