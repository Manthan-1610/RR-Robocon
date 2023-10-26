void setposy()
{
  PIDY.SetMode(AUTOMATIC);
  PIDY.SetTunings(kpy, kdy, kiy);
  PIDY.Compute();
  pwm_cap(outputy);
  if (outputy > 0 && outputy < 900)
  {
    Forward(pwm);
  }
  else if (outputy < 0)
  {
    Backward(pwm);
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
  if (output >= max_pwm || output <= -max_pwm)
  {
    pwm = max_pwm;
  }
  else
  {
    pwm = abs(output);
  }
}