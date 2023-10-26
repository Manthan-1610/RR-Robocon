void setdegree() {
  PIDDEG.SetMode(AUTOMATIC);
  PIDDEG.SetTunings(kpd, kdd, kid);
  PIDDEG.Compute();
  pwm_cap(outputd);
  if (outputd > 0) {
    Left_rotate(pwm);
  }
  else if (outputd < 0) {
    Right_rotate(pwm);
  }
}
void setposy()
{
  PIDY.SetMode(AUTOMATIC);
  PIDY.SetTunings(kpy, kdy, kiy);
  PIDY.Compute();
  pwm_cap(outputy);
  if (outputy > 0)
  {
    Backward(pwm);
  }
  else if (outputy < 0)
  {
    Forward(pwm);
  }
}
void setposx()
{
  
  PIDX.SetMode(AUTOMATIC);
  PIDX.SetTunings(kpx, kdx, kix);
  PIDX.Compute();
  pwm_cap(outputx);
  if (outputx > 0)
  {
    Right(pwm);
  }
  else if (outputx < 0)
  {
    Left(pwm);
  }
}


void pwm_cap(int output) {
  if (output >= robot_speed || output <= -robot_speed)
  {
    pwm = robot_speed;
  }
  else
  {
    pwm = abs(output);
  }
}
