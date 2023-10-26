const int stepPin = 3; 
const int dirPin = 2; 
int angle = 0;
int step_angle = 0;
int temp_angle = 0;
int steps = 0;
 
void setup() {
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()>0){
  angle = Serial.parseInt();
  step_angle = angle - temp_angle;
  steps = (step_angle*200)/360;
  if(angle!=0)
   {  
    if(steps > 0)
    {
     clockwise(steps);
    }
    if(steps < 0)
    {
     anticlockwise(steps);
    }
    temp_angle = angle;
    Serial.print("Angle:");
    Serial.println(angle);
   }
  }
}

void clockwise(int s){
  digitalWrite(dirPin,HIGH);
  for(int x = 0; x < abs(s); x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500);
  }
}

void anticlockwise(int s){
  digitalWrite(dirPin,LOW);
  for(int x = 0; x < abs(s); x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(500);
  
  
  
  
  }
} 
