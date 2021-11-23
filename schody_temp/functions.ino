
bool light_flag = false;
bool full_light_flag = false;
byte pwm = 20; //zwiększać o pełne dziesiątki 30,40,50 itp. 
byte max_pwm=250;

void Send()
{
  for (int Out = 0; Out < 18; Out++)
  {
    shiftOut(SDI, CKI, MSBFIRST, Buffer[Out]);
  }
  delayMicroseconds(500);
}

//###########################################################################

void click1()
{
  if (light_flag == true) {
    all_PWM_off(pwm);
  }
  else {
    all_PWM_on(pwm);
  }
} // click1

//###########################################################################

void longPressStart1()
{
  stairs_down(2);
}// longPressStart1

//###########################################################################

void click2()
{
  if (light_flag == true) {
    all_PWM_off(pwm);
  }
  else {
    all_PWM_on(pwm);
  }
} // click2

//###########################################################################

void longPressStart2()
{
  stairs_up(2);
}

//###########################################################################

void allTurnOFF()
{
  for (int Out = 0; Out < 18; Out++) Buffer[Out] = 0x00;
  Send();
}

//###########################################################################

void doubleclick1()
{
  if (full_light_flag == true) {
    all_PWM_off(max_pwm);
    full_light_flag = false;
  }
  else {
    all_PWM_on(max_pwm);
    full_light_flag = true;
  }
}

//###########################################################################

void doubleclick2()
{
  if (full_light_flag == true) {
    all_PWM_off(max_pwm);
    full_light_flag = false;
  }
  else {
    all_PWM_on(max_pwm);
    full_light_flag = true;
  }
}

//###########################################################################

void all_PWM_on(byte pwm)
{
  for (int i = 0; i < pwm; i++)
  {
    for (int Out = 0; Out < LEDS; Out++)
    {
      Buffer[Out] = i;
    }
    Send();
    delay(10);
  }
  light_flag = true;
}

// #########################################################################

void stairs_up(byte speed)
{
  if (full_light_flag == true)all_PWM_off(max_pwm);
  if (light_flag == true) all_PWM_off(pwm);
  for (int Out = 0; Out < LEDS; Out++)
  {
    for (int i = 0; i <= max_pwm; i += speed) {
      Buffer[Out] = i;
      Send();
      delay(1);
    }
  }
    delay(time1);
    for (int i = max_pwm; i > pwm; i--)
    
  {
    for (int Out = 0; Out < LEDS; Out++)
    {
      Buffer[Out] = i;
    }
 
    Send();
    delay(40);
  }
  
  delay(time_  - time1);
  for (int Out = 0; Out < LEDS; Out++)
  {
    for (int i = pwm; i >= 0; i -= speed) {
      Buffer[Out] = i;
      Send();
      delay(20);
      
    }
  }
  light_flag = false;
  full_light_flag = false;
}

// #########################################################################

void stairs_down(byte speed)
{
  if (full_light_flag == true)all_PWM_off(max_pwm);
  if (light_flag == true) all_PWM_off(pwm);
  for (int Out = LEDS - 1; Out >= 0; Out--)
  {
    for (int i = 0; i < max_pwm; i += speed) {
      Buffer[Out] = i;
      Send();
     delay(1);
    }
  }
    delay(time1);
    for (int i = max_pwm; i > pwm; i--)
  {
    for (int Out = 0; Out < LEDS; Out++) 
    {
      Buffer[Out] = i;
    }
    Send();
    delay(40);
  }

  delay(time_ - time1);
  for (int Out = LEDS - 1; Out >= 0; Out--)
  {
    for (int i = pwm; i >= 0; i -= speed) {
      Buffer[Out] = i;
      Send();
      delay(20);     
    }
  }
  light_flag = false;
  full_light_flag = false;
}

// #########################################################################

void all_PWM_off(byte pwm)
{
  for (int i = pwm; i > -1; i--)
  {
    for (int Out = 0; Out < LEDS; Out++)
    {
      Buffer[Out] = i;
    }
    Send();
    delay(10);
  }
  light_flag = false;
  full_light_flag = false;
}
