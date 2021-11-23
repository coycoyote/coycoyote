#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "OneButton.h"

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40); //PWM driver no.1 for 16 LEDS
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41); //PWM driver no.2 for 1 last LED


OneButton button1(A1, true);            // button 1 assigned to A1 board pin
OneButton button2(A2, true);            // button 2 assigned to A2 board pin
bool light_flag = false;
uint16_t current_pwm;
byte speed = 15;
byte LED = 13;                //number of status LED on Arduino PCB (for NANO it is 13)
byte number_of_leds = 17;     //total number of LEDS
int duration_time = 5000;
byte minimum_pwm = 100;       //minimum power for LEDS
int maximum_pwm = 4095;       //maximum power for LEDS


// *************************************************************************************

void setup() {
  Serial.begin(115200);
  Serial.println("Staris drvier 1.2");
  pwm1.begin();           // PWM1 initialization
  pwm2.begin();           // PWM2 initialization
  pwm1.setPWMFreq(1000);  // This is the maximum PWM frequency
  pwm2.setPWMFreq(1000);  // This is the maximum PWM frequency
  
  pinMode(LED, OUTPUT);   // PIN initialization for LED status on PCB

  button1.attachClick(click1);                                //short click for button 1
  button1.attachDoubleClick(doubleclick1);                    //double click for button 1
  button1.attachLongPressStart(longPressStart1);              //long click for button 1
  //  button1.attachLongPressStop(longPressStop1);            //LongPressStop for use in future
  //  button1.attachDuringLongPress(longPress1);              //DuringLongPress for use in future

  // link the button 2 functions.
  button2.attachClick(click2);
  button2.attachDoubleClick(doubleclick2);
  button2.attachLongPressStart(longPressStart2);
  //  button2.attachLongPressStop(longPressStop2);
  //  button2.attachDuringLongPress(longPress2);
  all_off();            // Turn OFF for all LEDS when device is starting
  light_flag = false;   // Information for system that all LEDS are turned OFF
  current_pwm = 0;      // Information for system that PWM is set to 0
}
 
void loop() 
{
     button1.tick();
     delay(10);
     button2.tick();
     delay(10);
     
}
