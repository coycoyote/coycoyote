
#include <EEPROM.h>

#define DEVICE_RESPONSE "STS Controller v.1.0"
#define FIRMWARE "version 1.0"

// ======GLOBAL VARIABLES ========
float a = 0.0;
float b = 0.0;
float fluctuation = 0.0;
float power_supply = 4.99;
String inputString;
String readString;

void setup()
{
  analogReference(DEFAULT); 
  EEPROM.get(0, power_supply);
  if (power_supply == 0 || power_supply ==0xFF)
    {
      EEPROM.put(0, 5.0);
    }

  EEPROM.get(16, a);
    if (a == 0xFF)
    {
      EEPROM.put(16, 0.0);
    }

  EEPROM.get(32, b);
    if (b == 0xFF)
    {
      EEPROM.put(32, 0.0);
    }

//EEPROM.put(0, 5.0);
//EEPROM.put(16, 0.0);
//EEPROM.put(32, 0.0);
    
  initializeSerial();
}

void loop()
{

}
