void initializeSerial()
{
  Serial.begin(9600);
  Serial.setTimeout(2000);
  inputString = "";
}  
//===========================================
// Interrupt serial event
void serialEvent()
{
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read(); 
    if (inChar == '\n') {
      serialCommand(inputString); 
      inputString = "";
    } 
    else {
      inputString += inChar;
    }
  }  
}
//===========================================
void serialCommand(String command)
{
  String param = command.substring(2); 

  switch(command.charAt(0)) {
  case '#':
  {
    Serial.println(DEVICE_RESPONSE);
    Serial.println(FIRMWARE);
    break;
  }
case 'A':
  {
    a = param.toFloat();
    if (power_supply > 0 && power_supply <= 6 && a >= 0)
    {
      EEPROM.put(16, a);
      analogWrite(5, 255*(a + fluctuation)/power_supply);
      Serial.print(String(a));
      break;
    } else {Serial.println("Power supply value not set correctly. Please use 'F x.x' command to set this value."); break;}
  }
  case 'B':
  {
    b = param.toFloat();
    if (power_supply > 0 && power_supply <= 6 && b >= 0)
    {
      EEPROM.put(32, b);
      analogWrite(6, 255*(b + fluctuation)/power_supply);
      Serial.print(String(b));
      break;
   } else {Serial.println("Power supply value not set correctly. Please use 'F x.x' command to set this value."); break;}
  }
  case 'a':
    EEPROM.get(16, a);
      Serial.print(String(a));
      break;
  case 'b':
    EEPROM.get(32, b);
      Serial.print(String(b));
      break;

  case 'F':
      if (param.toFloat()>=1&& param.toFloat() < 6)
      {
        power_supply = param.toFloat();
        EEPROM.put(0, power_supply);
        Serial.print(String(power_supply));
        break;
      } else {Serial.println("Value for Power supply not acceptable !"); break;}
      
    case 'f':
        EEPROM.get(0, power_supply);
        Serial.print(String(power_supply));
        break;

  default:
    Serial.print("ERR:");      
    Serial.print(byte(command.charAt(1)), DEC); 
  }
  Serial.print('\n');
}
