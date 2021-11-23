#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <MD_MAX72xx.h>

#define CLK 6         
#define DIO 7 

#define keyHor 5
#define keyMin 4 
#define keyPL  3
 
#define DS3231_I2C_ADDRESS 0x68

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES  4
#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    10  // or SS
// MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

#define CHAR_SPACING  1 // pixels between characters
#define BUF_SIZE  75
char message[BUF_SIZE] = {" 00:00\n"};
  
volatile boolean flag;
Adafruit_BMP085 bmp;
 
byte decToBcd(byte val){
  return ( (val/10*16) + (val%10) );
}
 
byte bcdToDec(byte val){
  return ( (val/16*10) + (val%16) );
}
 
void setDateDs3231(byte second,  
                   byte minute,        // 0-59
                   byte hour,          // 1-23
                   byte dayOfWeek,     // 1-7
                   byte dayOfMonth,    // 1-28/29/30/31
                   byte month,         // 1-12
                   byte year)          // 0-99
{
   Wire.beginTransmission(DS3231_I2C_ADDRESS);
   Wire.write(0);
   Wire.write(decToBcd(second));    
   Wire.write(decToBcd(minute));
   Wire.write(decToBcd(hour));     
   Wire.write(decToBcd(dayOfWeek));
   Wire.write(decToBcd(dayOfMonth));
   Wire.write(decToBcd(month));
   Wire.write(decToBcd(year));
   Wire.endTransmission();
}
 
void getDateDs3231(byte *second,
          byte *minute,
          byte *hour,
          byte *dayOfWeek,
          byte *dayOfMonth,
          byte *month,
          byte *year)
{
 
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
 
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
 
  *second     = bcdToDec(Wire.read() & 0x7f);
  *minute     = bcdToDec(Wire.read());
  *hour       = bcdToDec(Wire.read() & 0x3f); 
  *dayOfWeek  = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month      = bcdToDec(Wire.read());
  *year       = bcdToDec(Wire.read());
}
 
void setINT(){  
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0x0E);
  Wire.write(0x0);
  Wire.endTransmission();
}
 
void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(13, OUTPUT);
  pinMode(keyHor, INPUT_PULLUP);
  pinMode(keyMin, INPUT_PULLUP);
  pinMode(keyPL, INPUT_PULLUP);
  mx.begin(); 
  mx.control(MD_MAX72XX::INTENSITY, 0);


  
    if (!bmp.begin())
  {
    Serial.println("Nie odnaleziono czujnika BMP085 / BMP180");
    while (1) {}
  }
}
 
void loop(){

  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year; 
  getDateDs3231(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year); 
  char TimeDisp[]={'0','0','0',':','0','0','0'}; 
  int8_t TempDisp[]={'0','0','.','0','0','o','C'};
  int8_t presDisp[4];
  
  TimeDisp[0] = ' ';
  String a;
  a = String(hour / 10);
  TimeDisp[1] = a.charAt(0);
  a = String(hour % 10);
  TimeDisp[2] = a.charAt(0);
  TimeDisp[3] = ':';
  a = String(minute / 10);
  TimeDisp[4] = a.charAt(0);
  a = String(minute % 10);
  TimeDisp[5] = a.charAt(0);
  TimeDisp[6] =' ';

  float temp = bmp.readTemperature();
  String t;
  
  t=String(int( temp / 10));
  TempDisp[0] = t.charAt(0);
  
  t=String(int (int(temp) % 10));
  TempDisp[1] = t.charAt(0);

  TempDisp[2] = '.';

  t=String((temp-int(temp))*10);
  TempDisp[3] = t.charAt(0);
  
  TempDisp[4] = 'oC';






  int pres = int(bmp.readPressure() / 10);
  String pres_s = String(pres);
  presDisp[0] = (pres_s[0]);
  presDisp[1] = (pres_s[1]);
  presDisp[2] = (pres_s[2]);
  presDisp[3] = (pres_s[3]);
 
  if (!digitalRead(keyHor) && !digitalRead(keyPL)){   
      second = 0;     
      hour++;  
      if (hour > 23) hour = 0;  
      setDateDs3231(second, minute, hour, dayOfWeek, dayOfMonth, month, year); 
      delay(200);
  }
  if (!digitalRead(keyMin) && !digitalRead(keyPL)){   // минуты
      second = 0;
      minute++;
      if (minute > 59) minute = 0;
      setDateDs3231(second, minute, hour, dayOfWeek, dayOfMonth, month, year);
      delay(200);
  }

  printText(0, MAX_DEVICES-1, TimeDisp);
  delay(500);
  TimeDisp[3]=' ';
  printText(0, MAX_DEVICES-1, TimeDisp);
  delay(500);
 
}

void printText(uint8_t modStart, uint8_t modEnd, char *pMsg)
// Print the text string to the LED matrix modules specified.
// Message area is padded with blank columns after printing.
{
  uint8_t   state = 0;
  uint8_t   curLen;
  uint16_t  showLen;
  uint8_t   cBuf[8];
  int16_t   col = ((modEnd + 1) * COL_SIZE) - 1;

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  do     // finite state machine to print the characters in the space available
  {
    switch(state)
    {
      case 0: // Load the next character from the font table
        // if we reached end of message, reset the message pointer
        if (*pMsg == '\0')
        {
          showLen = col - (modEnd * COL_SIZE);  // padding characters
          state = 2;
          break;
        }

        // retrieve the next character form the font file
        showLen = mx.getChar(*pMsg++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
        curLen = 0;
        state++;
        // !! deliberately fall through to next state to start displaying

      case 1: // display the next part of the character
        mx.setColumn(col--, cBuf[curLen++]);

        // done with font character, now display the space between chars
        if (curLen == showLen)
        {
          showLen = CHAR_SPACING;
          state = 2;
        }
        break;

      case 2: // initialize state for displaying empty columns
        curLen = 0;
        state++;
        // fall through

      case 3:  // display inter-character spacing or end of message padding (blank columns)
        mx.setColumn(col--, 0);
        curLen++;
        if (curLen == showLen)
          state = 0;
        break;

      default:
        col = -1;   // this definitely ends the do loop
    }
  } while (col >= (modStart * COL_SIZE));

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}
