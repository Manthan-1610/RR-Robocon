#include <AccelStepper.h>
#include <Servo.h>
#include <FastLED.h>

CRGB leds[26];
Servo esc1;
Servo esc2;

int pwm;
#define M1_pwm 5
#define M1_DIR 28
#define M2_pwm 4
#define M2_DIR 26
#define M3_pwm 3
#define M3_DIR 24
#define M4_pwm 2
#define M4_DIR 22


long double position[1];
int f_pwm, b_pwm, l_pwm, r_pwm, lr_pwm, rr_pwm;
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];
boolean newData = false;
bool temp = true;
char button_value[0];
unsigned int l_value = 0;
unsigned int r_value = 0;
signed int l_y_value = 0;
signed int r_x_value = 0;



int robot_speed = 150;
long double pitch[6] = { 20, 23.5163, 20.0174, 22.4177, 1, 17.5 };

int shoot1 = 53;
double angle;
const int stepPin1 = 41;  // step1 down
const int dirPin1 = 43;
bool esc1b;
int e1=0;
AccelStepper stepper1(AccelStepper::DRIVER, stepPin1, dirPin1, 45);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial3.begin(115200);

  pinMode(M1_DIR, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M3_DIR, OUTPUT);
  pinMode(M4_DIR, OUTPUT);
  pinMode(M1_pwm, OUTPUT);
  pinMode(M2_pwm, OUTPUT);
  pinMode(M3_pwm, OUTPUT);
  pinMode(M4_pwm, OUTPUT);

  pinMode(shoot1, OUTPUT);

  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);

  stepper1.setMaxSpeed(5000);
  stepper1.setAcceleration(5000);
  FastLED.addLeds<WS2811, 6, GRB>(leds, 26).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);
  fill_solid(leds, 26, CRGB::Red);
  FastLED.show();
  esc1.attach(6);
  esc2.attach(7);
  esc1.write(30);
  esc2.write(30);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  ps4_data();

  if (newData == true) {
    strcpy(tempChars, receivedChars);
    split_data();
    newData = false;
  }

    movement();
    if (button_value[0] == 'J') digitalWrite(shoot1, HIGH);
    else digitalWrite(shoot1, LOW);

    if(button_value[0] != 'E') esc1b=true;
    else if (button_value[0] == 'E' && esc1b == true) {
      e1++;
      if(e1==3){
          e1 = 1;
      }
      esc1b=false;
    
      // if(e1 % 2 != 0){ 
      //   esc1.write(150); 
      //   esc2.write(150);
      //   e1++;
      //   esc1b = false;
      // } 
      // else{
      //   esc1.write(30); 
      //   esc2.write(30);
      //   e1=1;
      //   esc1b = false;
      // }
    } 
    if(e1 == 1) { esc1.write(150); esc2.write(150); }
    else if(e1 == 2){ esc1.write(30); esc2.write(30); }
    else;

    if(button_value[0] == 'K') robot_speed = 50;
    else;
    if (button_value[0] == 'A') {
      // position[0] = (pitch[0] * 60800)/360;
      // stepper1.moveTo(position);
      // stepper1.runSpeedToPosition();
      angle = 20;
      stepangle(angle);
    }
    if (button_value[0] == 'C') {
      // position[0] = (pitch[0] * 60800)/360;
      // stepper1.moveTo(position);
      // stepper1.runSpeedToPosition();
      angle = pitch[4];
      stepangle(angle);
    }
}

void movement() {
  f_pwm = map(l_y_value, 10, 130, 10, robot_speed);
  b_pwm = map(l_y_value, -10, -130, 10, robot_speed);
  l_pwm = map(r_x_value, 10, 130, 10, robot_speed);
  r_pwm = map(r_x_value, -10, -130, 10, robot_speed);
  rr_pwm = map(r_value, 0, 255, 10, robot_speed);
  lr_pwm = map(l_value, 0, 255, 10, robot_speed);
  if (l_value > 10) Left_rotate(lr_pwm);        //l1 button
  else if (r_value > 10) Right_rotate(rr_pwm);  //r1 button
  else if (r_x_value < -10) Left(r_pwm);        //analog right hat
  else if (r_x_value > 10) Right(l_pwm);        // analog right hat
  else if (l_y_value > 10) Forward(f_pwm);      // analog left hat
  else if (l_y_value < -10) Backward(b_pwm);    // analog left hat
  else Hold();
}
