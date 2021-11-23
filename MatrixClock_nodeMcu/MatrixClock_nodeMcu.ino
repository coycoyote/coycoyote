#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
 
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);



void setup() {
  Serial.begin(9600);
  Serial.println("16 channel PWM test!");
  pwm1.begin();
  pwm1.setPWMFreq(1600);  // This is the maximum PWM frequency
 
  // save I2C bitrate
//  uint8_t twbrbackup = TWBR;
  // must be changed after calling Wire.begin() (inside pwm.begin())
 // TWBR = 12; // upgrade to 400KHz!
 
}
 
void loop() {
  // Drive each PWM in a 'wave'
  for (uint16_t i=0; i<4096; i += 2) 
  {
    for (uint8_t pwmnum=0; pwmnum < 17; pwmnum++) 
    {
      // pwm1.setPWM(pwmnum, 0, (i + (4096/16)*pwmnum) % 4096 );
      pwm1.setPWM(pwmnum, 0, i);
      
    }
  }
}