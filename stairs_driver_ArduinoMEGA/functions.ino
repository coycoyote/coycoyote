
void stairs_up()
{
   for (byte pwmnum = 0; pwmnum <= number_of_leds; pwmnum++)
  {
    delay(100);
    for (int i = current_pwm; i <= maximum_pwm; i += speed)
    {
      if (pwmnum == number_of_leds)
      {
        pwm2.setPWM(0, 0, i);
      }
      else
      {
        pwm1.setPWM(pwmnum, 0, i);
      }
    }
  }
  delay(duration_time);
  all_to_pwm_min(minimum_pwm, maximum_pwm, speed, false);
  light_flag = true;
  dbl_blink();
}

// *********************************************************************

void stairs_down()
{
   for (int pwmnum = number_of_leds; pwmnum >= 0; pwmnum--)
  {
    delay(100);
    for (int i = current_pwm; i <= maximum_pwm; i += speed)
    {
      if (pwmnum==number_of_leds)
      {
        pwm2.setPWM(0, 0, i);
      }
      else
      {  
        pwm1.setPWM(pwmnum, 0, i);
      }
    }
  }
  delay(duration_time);
  all_to_pwm_min(minimum_pwm, maximum_pwm, speed, false);
  light_flag = true;
  
  dbl_blink();
}

// *********************************************************************

void all_to_pwm_max(int pwm_min, int pwm_max, byte sp)
{
  int del = 1;
  if ((pwm_min >= 0) && (maximum_pwm > pwm_min) && (pwm_max <= maximum_pwm))
  {
    if (pwm_max - maximum_pwm <4095 or pwm_min>0) {del = 2;}
    for (int i = pwm_min; i <= pwm_max; i += sp) 
    {
      for (byte pwmnum = 0; pwmnum < number_of_leds; pwmnum++) 
      {
        
        if (i <= pwm_max)
          {
            pwm1.setPWM(pwmnum, 0, i);
            pwm2.setPWM(0, 0, i);
          }
      delay(del);
      }
    }
    light_flag = true;
    current_pwm = pwm_max;
    dbl_blink();
  }
}

// *********************************************************************

void all_to_pwm_min(int pwm_min, int pwm_max, byte sp, bool delay_flag)
{
 byte del = 1;
 if (delay_flag == true) { delay(10000); }
  if ((pwm_min >= 0) && (maximum_pwm > pwm_min) && (pwm_max <= maximum_pwm))
  {
    if (pwm_max < maximum_pwm or pwm_min>0) {del = 5;}
    for (int i = pwm_max; i >= pwm_min; i -= sp) 
     {
      for (byte pwmnum = 0; pwmnum < number_of_leds; pwmnum++) 
      {
        pwm1.setPWM(pwmnum, 0, i);
        pwm2.setPWM(0, 0, i);
        
      }
      delay(del);
    }
    light_flag = false;
    current_pwm = pwm_min;
    dbl_blink();
  }
}

// *********************************************************************

void all_off()
{
  for (uint8_t pwmnum=0; pwmnum < number_of_leds; pwmnum++) 
  {
    if (pwmnum == 17)
    {
      pwm2.setPWM(0, 0, 0);
    }
    else
    {
      pwm1.setPWM(pwmnum, 0, 0);
      pwm2.setPWM(0, 0, 0);
    }
  }
  light_flag = false;
  current_pwm = 0;
  dbl_blink();
}

// *********************************************************************

void click1()
{
  if (light_flag == true)
  {
    all_to_pwm_min(0, current_pwm, speed, false);
    all_off();
  }
  else
  {
    all_to_pwm_max(0, minimum_pwm, speed);
  }
}

// *********************************************************************

void click2()
{
  if (light_flag == true)
  {
    all_to_pwm_min(0, current_pwm, speed, true);
    all_off();
  }
  else
  {
    all_to_pwm_max(0, minimum_pwm, speed);
  }
}

// *********************************************************************

void doubleclick1()
{
  stairs_up();
}
// *********************************************************************

void doubleclick2()
{
  stairs_down();
}
// *********************************************************************

void longPressStart1()
{
  if (light_flag == true)
  {
    all_to_pwm_min(0, current_pwm, speed, false);
    all_off();
  }
  else
  {
    all_to_pwm_max(0, maximum_pwm, speed);
  }

}
// *********************************************************************

void longPressStart2()
{
  if (light_flag == true)
  {
    all_to_pwm_min(0, current_pwm, speed, false);
    all_off();
  }
  else
  {
    all_to_pwm_max(0, maximum_pwm, speed);
  }
}
// *********************************************************************

void dbl_blink()
// Function used to confirm that task was finished.
// When status LED blinked 3 times it is information that function was executed and finished.
// !!! Used only for debugging !!!
{
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100); 
  digitalWrite(LED, LOW);
}
