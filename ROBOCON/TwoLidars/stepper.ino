long double temp_angle1 = 0;
long double  steps1 = 0;
long double step_angle1 = 0;
long double temp_angle2 = 0;
long double steps2 = 0;
long double step_angle2 = 0;

long double temp_angle3 = 0;
long double steps3 = 0;
long double step_angle3 = 0;
long double temp_angle4 = 0;
long double steps4 = 0;
long double step_angle4 = 0;

//base stepper 1
void stepangle(int angle1) {

  step_angle1 = angle1 - temp_angle1;
  // Calculate the number of steps required to move to the new angle
  steps1 = ((step_angle1) * 60800) / 360;

  if (angle1 != 0) {
    if (steps1 < 0) {
      // Move the motor clockwise
      digitalWrite(dirPin1, HIGH);
      stepper1.move(steps1);
      while (stepper1.distanceToGo() != 0) {
        stepper1.run();
      }
    } else if (steps1 > 0) {
      // Move the motor anticlockwise
      digitalWrite(dirPin1, LOW);
      stepper1.move(steps1);
      while (stepper1.distanceToGo() != 0) {
        stepper1.run();
      }
      temp_angle1 = angle1;
    }
    // Update the current angle
    temp_angle1 = angle1;
    // Print the current angle to the serial monitor
    Serial.print("Angle1: ");
    Serial.println(angle1);
  }
}