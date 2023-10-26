void Forward(int pwm) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, HIGH);
  analogWrite(M4_pwm, pwm-abs(10*pwm/255));
  analogWrite(M1_pwm, pwm-abs(4*pwm/255));
  analogWrite(M2_pwm, pwm);
  analogWrite(M3_pwm, pwm-abs(6*pwm/255));
}

void Backward(int pwm) {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, HIGH);
  digitalWrite(M3_DIR, HIGH);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_pwm, pwm-abs(10*pwm/255));
  analogWrite(M1_pwm, pwm-abs(4*pwm/255));
  analogWrite(M2_pwm, pwm);
  analogWrite(M3_pwm, pwm-abs(6*pwm/255));
}

void Left(int pwm) {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, HIGH);
  digitalWrite(M4_DIR, HIGH);
  analogWrite(M4_pwm, pwm-abs(10*pwm/255));
  analogWrite(M1_pwm, pwm-abs(4*pwm/255));
  analogWrite(M2_pwm, pwm);
  analogWrite(M3_pwm, pwm-abs(6*pwm/255));
}

void Right(int pwm) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, HIGH);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_pwm, pwm-abs(10*pwm/255));
  analogWrite(M1_pwm, pwm-abs(4*pwm/255));
  analogWrite(M2_pwm, pwm);
  analogWrite(M3_pwm,pwm-abs(6*pwm/255));
}

void Forward_left(int pwm) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, HIGH);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_pwm, 0);
  analogWrite(M1_pwm, (pwm-abs(4*pwm/255)));
  analogWrite(M2_pwm, 0);
  analogWrite(M3_pwm, (pwm-abs(6*pwm/255)));
}

void Forward_right(int pwm) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, HIGH);
  analogWrite(M4_pwm, (pwm-abs(10*pwm/255)));
  analogWrite(M1_pwm, 0);
  analogWrite(M2_pwm, pwm);
  analogWrite(M3_pwm, 0);
}

void Backward_left(int pwm) {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, HIGH);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_pwm, (pwm-abs(10*pwm/255)));
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
  analogWrite(M1_pwm, (pwm-abs(4*pwm/255)));
  analogWrite(M2_pwm, 0);
  analogWrite(M3_pwm, (pwm-abs(6*pwm/255)));
}

void Right_rotate(int pwm) {
  digitalWrite(M1_DIR, HIGH);
  digitalWrite(M2_DIR, HIGH);
  digitalWrite(M3_DIR, HIGH);
  digitalWrite(M4_DIR, HIGH);
  analogWrite(M4_pwm, pwm-abs(10*pwm/255));
  analogWrite(M1_pwm, pwm-abs(4*pwm/255));
  analogWrite(M2_pwm, pwm);
  analogWrite(M3_pwm, pwm-abs(6*pwm/255));
}

void Left_rotate(int pwm) {
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, LOW);
  analogWrite(M4_pwm, pwm-abs(10*pwm/255));
  analogWrite(M1_pwm, pwm-abs(4*pwm/255));
  analogWrite(M2_pwm, pwm);
  analogWrite(M3_pwm, pwm-abs(6*pwm/255));
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
