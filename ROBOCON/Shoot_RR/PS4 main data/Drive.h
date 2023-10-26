#define M1_pwm 2
#define M1_DIR 22
#define M2_pwm 3
#define M2_DIR 24
#define M3_pwm 4
#define M3_DIR 26
#define M4_pwm 5
#define M4_DIR 28
void Forward(int pwm) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, HIGH);
  analogWrite(M4_pwm, pwm);
  analogWrite(M1_pwm, pwm);
  analogWrite(M2_pwm, pwm);
  analogWrite(M3_pwm, pwm);
}

void Backward(int pwm) {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, HIGH);
  digitalWrite(M3_DIR, HIGH);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_pwm, pwm);
  analogWrite(M1_pwm, pwm);
  analogWrite(M2_pwm, pwm);
  analogWrite(M3_pwm, pwm);
}

void Right(int pwm) {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, HIGH);
  digitalWrite(M4_DIR, HIGH);
  analogWrite(M4_pwm, pwm);
  analogWrite(M1_pwm, pwm);
  analogWrite(M2_pwm, pwm);
  analogWrite(M3_pwm, pwm);
}

void Left(int pwm) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, HIGH);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_pwm, pwm);
  analogWrite(M1_pwm, pwm);
  analogWrite(M2_pwm, pwm);
  analogWrite(M3_pwm, pwm);
}

void Forward_left(int pwm) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, HIGH);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_pwm, 0);
  analogWrite(M1_pwm, pwm);
  analogWrite(M2_pwm, 0);
  analogWrite(M3_pwm, pwm);
}

void Forward_right(int pwm) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, HIGH);
  analogWrite(M4_pwm, pwm);
  analogWrite(M1_pwm, 0);
  analogWrite(M2_pwm, pwm);
  analogWrite(M3_pwm, 0);
}

void Backward_left(int pwm) {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, HIGH);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_pwm, pwm);
  analogWrite(M1_pwm, 0);
  analogWrite(M2_pwm, pwm);
  analogWrite(M3_pwm, 0);
}

void Backward_right(int pwm) {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, HIGH);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_pwm, 0);
  analogWrite(M1_pwm, pwm);
  analogWrite(M2_pwm, 0);
  analogWrite(M3_pwm, pwm);
}

void Right_rotate(int pwm) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, HIGH);
  digitalWrite(M3_DIR, HIGH);
  digitalWrite(M4_DIR, HIGH);
  analogWrite(M4_pwm, pwm);
  analogWrite(M1_pwm, pwm);
  analogWrite(M2_pwm, pwm);
  analogWrite(M3_pwm, pwm);
}

void Left_rotate(int pwm) {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_pwm, pwm);
  analogWrite(M1_pwm, pwm);
  analogWrite(M2_pwm, pwm);
  analogWrite(M3_pwm, pwm);
}

void Hold() {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_pwm, 0);
  analogWrite(M1_pwm, 0);
  analogWrite(M2_pwm, 0);
  analogWrite(M3_pwm, 0);
}
