#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "OneButton.h"

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);


OneButton button1(A1, true);            // button 1 assigned to A1 board pin
OneButton button2(A2, true);            // button 2 assigned to A2 board pin
bool light_flag = false;
uint16_t current_pwm;
byte speed = 15;
byte LED = 13;
byte number_of_leds = 17;
int duration_time = 5000;
byte minimum_pwm = 100;
int maximum_pwm = 4095;


// *************************************************************************************

void setup() {
  Serial.begin(115200);
  Serial.println("Staris drvier 1.0");
  pwm1.begin();
  pwm2.begin();
  pwm1.setPWMFreq(1000);  // This is the maximum PWM frequency
  pwm2.setPWMFreq(1000);  // This is the maximum PWM frequency
  
  pinMode(LED, OUTPUT);
  // save I2C bitrate
//  uint8_t twbrbackup = TWBR;
  // must be changed after calling Wire.begin() (inside pwm.begin())
 // TWBR = 12; // upgrade to 400KHz!
  
  
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
  all_off();
  light_flag = false;
  current_pwm = 0;
}
 
void loop() 
{
     button1.tick();
     delay(10);
     button2.tick();
     delay(10);
     
}
