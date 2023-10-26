#define BLed 40
#define GLed 41
#define M1_PWM 2
#define M1_DIR 22//50
#define M2_PWM 3
#define M2_DIR 24//51
#define M3_PWM 4
#define M3_DIR 26//52
#define M4_PWM 5
#define M4_DIR 28//53
int max_pwm=70;
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