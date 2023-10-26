#include <AccelStepper.h>
#include <Servo.h>
#include <FastLED.h>
#include <PID_v1.h>
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
#define pick1_C 47
#define pick1_CC 49

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
boolean lay = false;
int layout =1;
double distance1;
double strength1;
double distance2;
double strength2;
double deg = 0;
bool pidset = false;
bool setx = true;
bool sety = false;
bool checksum = false;
bool receiveComplete1 = false;
bool receiveComplete2 = false;
double set_posx = 121;
double outputx;
double kpx = 7;
double kdx = 0.7;
double kix = 0.2;
double set_posy = 23;
double outputy;
double kpy = 4;
double kdy = 0.8;
double kiy = 0.55;
double set_posd;
double outputd;
double kpd = 2.5;
double kdd = 0.2;
double kid = 0.15;
double currenttime;
double previoustime;
double temptime;
double looptime;
double intervaldeg = 3000;
double intervalx = 6000;
double intervaly = 9000;
double intervalyaw=3000;
int i,j,k;
bool yaw_direct=false;
PID PIDX(&distance1, &outputx, &set_posx, kpx, kdx, kix, DIRECT);
PID PIDY(&distance2, &outputy, &set_posy, kpy, kdy, kiy, DIRECT);
PID PIDDEG(&deg, &outputd, &set_posd, kpd, kdd, kid, DIRECT);
int robot_speed = 255;
long double pitch[5] = { 18.6069, 23.5163, 20.0174, 22.4177, 1}; 
int grab1=51;
int shoot1=53;

const int stepPin1 = 41;  // step1 down
const int dirPin1 = 43;

AccelStepper stepper1(AccelStepper::DRIVER, stepPin1, dirPin1, 45);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(9600);
  Serial2.begin(115200);
  Serial3.begin(115200);
  PIDX.SetMode(AUTOMATIC);
  PIDY.SetMode(AUTOMATIC);
  PIDX.SetOutputLimits(-100, 100);
  PIDY.SetOutputLimits(-100, 100);
  PIDDEG.SetOutputLimits(-100, 100);
  pinMode(M1_DIR, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M3_DIR, OUTPUT);
  pinMode(M4_DIR, OUTPUT);
  pinMode(M1_pwm, OUTPUT);
  pinMode(M2_pwm, OUTPUT);
  pinMode(M3_pwm, OUTPUT);
  pinMode(M4_pwm, OUTPUT);
  pinMode(grab1,OUTPUT);
  pinMode(shoot1,OUTPUT);
  pinMode(pick1_C,OUTPUT);
  pinMode(pick1_CC,OUTPUT);
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);

  stepper1.setMaxSpeed(5000);
  FastLED.addLeds<WS2811, 6, GRB>(leds, 26).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(255);
  fill_solid(leds,26,CRGB::Red);
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
    if (button_value[0] != 'O') {
    lay = true;
  }
  if (button_value[0] == 'O' && lay == true) {
    layout++;
    if (layout == 3) {
      layout = 1;
    }
    lay = false;
  }
  if(layout==1){
      if (temp == true)
    {
      int red = 160;
      int green = 32;
      int blue = 240;
      Serial3.print('<');
      Serial3.print(red);
      Serial3.print(',');
      Serial3.print(blue);
      Serial3.print(',');
      Serial3.print(green);
      Serial3.print(',');
      Serial3.print('0');
      Serial3.print(',');
      Serial3.print('0');
      Serial3.print(',');
      Serial3.print('>');
      Serial3.println();
      temp = false;
    }
    movement();
    if(button_value[0]=='E'){ digitalWrite(pick1_C,HIGH); digitalWrite(pick1_CC,LOW);}
    else if(button_value[0]=='G'){ digitalWrite(pick1_C,LOW); digitalWrite(pick1_CC,HIGH);}
    else{digitalWrite(pick1_C,LOW); digitalWrite(pick1_CC,LOW);}

    if(button_value[0]=='F')      digitalWrite(grab1,HIGH);
    else if(button_value[0]=='H') digitalWrite(grab1,LOW);

    if(button_value[0] == 'L') pidset=true;
    }
    else if(layout==2){
      if (temp == false)
    {
      int red = 255;
      Serial3.print('<');
      Serial3.print(red);
      Serial3.print(',');
      Serial3.print('0');
      Serial3.print(',');
      Serial3.print('0');
      Serial3.print(',');
      Serial3.print('0');
      Serial3.print(',');
      Serial3.print('0');
      Serial3.print(',');
      Serial3.print('>');
      Serial3.println();
      temp = true;
    }
    if(button_value[0]=='K'){
      esc1.write(150);
      esc2.write(150);
      }
    else if(button_value[0]=='M'){
      esc1.write(30);
      esc2.write(30);
      }
    if(r_value>100) digitalWrite(shoot1,HIGH);
    else digitalWrite(shoot1,LOW);

    if(button_value[0] == 'L') i=0;
    else;

    if(button_value[0]=='A'){
      // angle=pitch[0];
      // stepangle(angle);
      set_posd=-3.09;
      yaw_direct=true;
    }
    else if(button_value[0]=='B'){
      // angle=pitch[1];
      // stepangle(angle);
      set_posd=43.36;
      yaw_direct=true;
    }
    else if(button_value[0]=='C'){
      // angle=pitch[2];
      // stepangle(angle);
      set_posd=39.04;
      yaw_direct=true;
    }
    else if(button_value[0]=='D'){
      // angle=pitch[3];
      // stepangle(angle);
      set_posd=67.29;
      yaw_direct=true;
    }
    else if(button_value[0]=='I'){
      // angle=pitch[4];
      // stepangle(angle);
      set_posd=0;
      yaw_direct=true;
    }
    else;
      }
    while (pidset == true) {
    while (!receiveComplete1) {
      getTFminiData1(&distance1, &strength1, &receiveComplete1);
    }
    receiveComplete1 = false;
    // Serial.println(distance);
    while (!receiveComplete2) {
      getTFminiData2(&distance2, &strength2, &receiveComplete2);
    }
    receiveComplete2 = false;
    get_degree();

    currenttime = millis();
    if (i == 0) {
      temptime = currenttime;
      i = 1;
    }
    looptime = currenttime - temptime;
    set_posd=0;
    if (looptime <= intervaldeg) { 
      setdegree(); 
      Serial.print("setting degree"); 
      Serial.println(deg);
    } 
    else{
     if (looptime <= intervalx){
        Serial.print("setting x");
        Serial.println(distance1);
        setposx();
      } 
    else{
       if (looptime <= intervaly){
          Serial.print("setting y");
          Serial.println(distance2);
          setposy();
        } 
        else{
          pidset = false;
        }
      }
    }
  }
    while(yaw_direct == true){
    get_degree();
      currenttime = millis();
      if (i == 0) {
      temptime = currenttime;
      i = 1;
      }
      looptime = currenttime - temptime;
      PIDDEG.SetControllerDirection(DIRECT);
      if (looptime <= intervalyaw) { setdegree(); Serial.print("setting degree"); Serial.println(deg);}
      else yaw_direct=false;
  }
}

void get_degree(){
  while (Serial1.available()) {
      String x = Serial1.readStringUntil('\n');
      deg = x.toDouble();
    }
}

void movement(){
   f_pwm = map(l_y_value, 10, 130, 10, robot_speed);
   b_pwm = map(l_y_value, -10, -130, 10, robot_speed);
   l_pwm = map(r_x_value, 10, 130, 10, robot_speed);
   r_pwm = map(r_x_value, -10, -130, 10, robot_speed);
   rr_pwm = map(r_value, 0, 255, 10, robot_speed);
   lr_pwm = map(l_value, 0, 255, 10, robot_speed);
    if (l_value > 10) Left_rotate(lr_pwm); //l1 button
    else if (r_value > 10) Right_rotate(rr_pwm); //r1 button
    else if (r_x_value < -10) Left(r_pwm); //analog right hat
    else if (r_x_value > 10) Right(l_pwm); // analog right hat
    else if (l_y_value > 10) Forward(f_pwm); // analog left hat
    else if (l_y_value < -10) Backward(b_pwm); // analog left hat
    else Hold();
  }
  