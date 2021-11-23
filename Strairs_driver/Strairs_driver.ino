//STAIRS DRIVER by BallD 2020
// utf-8

#include "OneButton.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

OneButton button1(A1, true);            // button 1 assigned to A1 board pin
OneButton button2(A2, true);            // button 2 assigned to A2 board pin

// byte pinOut = 2;                  // pins may be 3,5,6,9,10,11
// byte pwmValue = 0;                // value may be 0 to 255

//####################### GLOBAL SETUP ##############################################

int duration_one_click = 3000;    //milli seconds when 1 click is active
byte j=2;                         //first PWM pin in Arduino board
byte wait_between_straits = 1;    //ms beetween next straits
int PWM_all_ON = 256;             //PWM value for all LEDs when long press is active
byte numers_of_stairs = 16;        // not used yet
bool PWM_active = false;
bool turned_on = false;

void setup(){
//  pinMode (2, OUTPUT);  
//  pinMode (3, OUTPUT);  
//  pinMode (4, OUTPUT);  
//  pinMode (5, OUTPUT);  
//  pinMode (6, OUTPUT);  
//  pinMode (7, OUTPUT);  
//  pinMode (8, OUTPUT);  
//  pinMode (9, OUTPUT);  
//  pinMode (10, OUTPUT);  
//  pinMode (11, OUTPUT);  
//  pinMode (12, OUTPUT);
//  pinMode (13, OUTPUT);
    pwm.begin();
    allTurnOFF();
      pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(120);  // This is the maximum PWM frequency
   Wire.setClock(400000);
  // link the button 1 functions.
  button1.attachClick(click1);
  button1.attachDoubleClick(doubleclick1);
  button1.attachLongPressStart(longPressStart1);
//  button1.attachLongPressStop(longPressStop1);
//  button1.attachDuringLongPress(longPress1);

  // link the button 2 functions.
  button2.attachClick(click2);
  button2.attachDoubleClick(doubleclick2);
  button2.attachLongPressStart(longPressStart2);
//  button2.attachLongPressStop(longPressStop2);
//  button2.attachDuringLongPress(longPress2);
  //Serial.begin(115200);
}
void loop()
{
  button1.tick();
  button2.tick();
  delay(10);
//  Serial.println(digitalRead(2));
}
