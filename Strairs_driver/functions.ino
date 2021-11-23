
void inc_brightness(byte pin)
{
  for (int i=0; i<4096; i+=16)
  {
    pwm.setPWM(pin, 0 ,i);
    delay(wait_between_straits);
  }
}

//###########################################################################

void dec_brightness(byte pin)
{
   for (int i=4096; i>-2; i-=16)
  {
    pwm.setPWM(pin, 0, i);
    delay(wait_between_straits);
  }
}

//###########################################################################

// This function will be called when the button1 was pressed 1 time (and no 2. button press followed).
void click1()
{
  Serial.println("Button 1 click.");
  for (int j=0; j<16; j++) inc_brightness(j);
  turned_on = true;
  delay(duration_one_click);                          //durtation to turn off
  for (int jk=0; jk<16;jk++) dec_brightness(jk);
  turned_on = false;
} // click1

//###########################################################################

// This function will be called often, while the button1 is pressed for a long time.
void longPressStart1() 
{
    if (PWM_active == false)
    {
      for (int i=0; i<16; i++) pwm.setPWM(i, 0, PWM_all_ON);
      PWM_active=true;
      turned_on = true;
      delay(500);
      return 0;
    }
    if (PWM_active == true)
    {
      for (int j=0; j<16; j++) pwm.setPWM(j, 0, 0);
      PWM_active=false;
      turned_on = false;
      delay(500);
      return 0;
    }
}// longPressStart1

//###########################################################################

void click2()
{
  Serial.println("Button 2 click.");
    for (int j=15; j>-1; j--) inc_brightness(j);
    turned_on = true;
    delay(duration_one_click);                        //durtation to turn off
    for (int jk=15; jk>-1; jk--) dec_brightness(jk);
    turned_on = false;
} // click2

//###########################################################################

void longPressStart2()
{
    if (PWM_active == false)
    {
      for (int i=0; i<16; i++) pwm.setPWM(i, 0, PWM_all_ON);
      PWM_active=true;
      turned_on = true;
      delay(500);
      return 0;
    }
    if (PWM_active == true)
    {
      for (int j=0; j<16; j++) pwm.setPWM(j, 0, 0);
      PWM_active=false;
      turned_on = false;
      delay(500);
      return 0;
    } // longPressStart2
}

//###########################################################################

void allTurnOFF()
{
  for (uint8_t pwmnum=0; pwmnum < 16; pwmnum++)
   {
    pwm.setPWM(pwmnum, 0, 0);
    turned_on = false;
   }
} 

//###########################################################################

void allTurnON()
{
  for (uint8_t pwmnum=0; pwmnum < 16; pwmnum++)
  {
    pwm.setPWM(pwmnum, 0, 4095);
    turned_on = true;
   }
} 
    
//###########################################################################

void doubleclick1()
 {
  if (turned_on == true)
  {
    allTurnOFF();
  } 
  else 
  {
    allTurnON();
  }
 }

//###########################################################################

void doubleclick2()
 {
  if (turned_on == true)
  {
    allTurnOFF();
  } 
  else 
  {
    allTurnON();
  }
 }

//###########################################################################

void randomize()
{
  randomSeed(analogRead(0));
  byte led_no = random(0, 15);
  inc_brightness(led_no);
  delay(wait_between_straits);
  dec_brightness(led_no);
}

//###########################################################################
