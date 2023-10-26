// #include <AccelStepper.h>

// // Define stepper motor pins
// const int DIR_PIN =43 ;
// const int STEP_PIN = 45;

// // Create AccelStepper object
// AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN,41);

// long angle = 0;
// long temp_angle = 0;
// long steps = 0;
// long step_angle=0;

// void setup() {
//   // Set maximum speed and acceleration
//   stepper.setMaxSpeed(1000);
//   stepper.setAcceleration(100);

//   // Set initial position to zero
// //  stepper.setCurrentPosition(stepper.move(steps));

//   // Set pin modes for step and direction pins
//   pinMode(STEP_PIN, OUTPUT);
//   pinMode(DIR_PIN, OUTPUT);
//   // Initialize serial communication
//   Serial.begin(9600);
// }

// void loop() {
//   // Check if there is serial data available
//   if (Serial.available() > 0) {
//     // Read the incoming angle value
//     angle = Serial.parseInt();
//     step_angle=angle-temp_angle;
//     Serial.print("Step Angle:");
//     Serial.println(step_angle);
//     // Calculate the number of steps required to move to the new angle
//     steps = (step_angle * 200) / 360;
//     Serial.print("Steps:");
//     Serial.println(steps);
//     if (angle != 0) {
//       if (steps < 0) {
//         // Move the motor clockwise
//         digitalWrite(DIR_PIN, HIGH);
//         stepper.move(steps);
//         while (stepper.distanceToGo() != 0) {
//           stepper.run();
//         }
//         temp_angle = angle;
//       }
//       else if (steps > 0) {
//         // Move the motor anticlockwise
//         digitalWrite(DIR_PIN, LOW);
//         stepper.move(steps);
//         while (stepper.distanceToGo() != 0) {
//           stepper.run();
//         }
//         temp_angle = angle;
//       }
//       // Update the current angle

//       // Print the current angle to the serial monitor
//       Serial.print("Angle: ");
//       Serial.println(angle);
//     }
//   }
// }


#include <MobaTools.h>
//#include <AccelStepper.h>
const int stepPin = 45; 
const int dirPin = 43; 
const int enPin = 41; 

int Angle = 0;

int motorspeed = 300;                         
const int stepsPerRev = 200;                   
MoToStepper stepper1(stepsPerRev, STEPDIR);  

void setup() {
    Serial.begin(115200);
    stepper1.attach(stepPin, dirPin);
    stepper1.setSpeed(motorspeed);              
    stepper1.attachEnable(enPin,100,HIGH);  
}

void loop() {
  while(Serial.available()>0)
  {
    Angle = Serial.parseInt();
  }
  stepper1.write(Angle);
}