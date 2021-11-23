


void all_to_pwm_max(int pwm_min, int pwm_max)
{
  if ((pwm_min >= 0) && (pwm_max > pwm_min) && (pwm_max <= 4095))
  {
    
    for (int i = pwm_min; i <= pwm_max; i += speed) 
    
    {
      for (byte pwmnum = 0; pwmnum < 16; pwmnum++) 
      {
        // pwm1.setPWM(pwmnum, 0, (i + (4096/16)*pwmnum) % 4096 );
        if (i <= pwm_max)
          {
            pwm1.setPWM(pwmnum, 0, i);
          }
      }
    }
    light_flag = true;
    current_pwm = pwm_max;
    dbl_blink();
  }
}




void all_to_pwm_min(int pwm_min, int pwm_max)
{
  if ((pwm_min >= 0) && (pwm_max > pwm_min) && (pwm_max <= 4095))
  {
    
    for (int i = pwm_max; i >= pwm_min; i -= speed) 
     {
      for (byte pwmnum = 0; pwmnum < 16; pwmnum++) 
      {
        // pwm1.setPWM(pwmnum, 0, (i + (4096/16)*pwmnum) % 4096 );
        pwm1.setPWM(pwmnum, 0, i);
       
        // Serial.println("PWM: " + String(i));
        
      }
    }
    light_flag = false;
    current_pwm = pwm_min;
    dbl_blink();
  }
}






void all_off()
{
  for (uint8_t pwmnum=0; pwmnum < 16; pwmnum++) 
  {
    // pwm1.setPWM(pwmnum, 0, (i + (4096/16)*pwmnum) % 4096 );
    pwm1.setPWM(pwmnum, 0, 0);
  }
  light_flag = false;
  current_pwm = 0;
}


void click1()
{
  if (light_flag == true)
  {
    all_to_pwm_min(0, current_pwm);
  }
  else
  {
    all_to_pwm_max(0, 4095);
  }
}

void click2()
{
  if (light_flag == true)
  {
    all_to_pwm_min(0, current_pwm);
  }
  else
  {
    all_to_pwm_max(0, 4095);
  }
}



void doubleclick1()
{
dbl_blink();
}
void doubleclick2()
{
dbl_blink();  
}
void longPressStart1(){}
void longPressStart2(){}


void dbl_blink()
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
