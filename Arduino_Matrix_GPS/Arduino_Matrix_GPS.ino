#include <MD_MAX72xx.h>
#include "Font_Data.h"
#include <Wire.h>
#include <DS3231.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES  4
#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    10  // or SS
#define CHAR_SPACING  1 // pixels between characters
#define BUF_SIZE  75

char message[BUF_SIZE] = {"  0:00\0"};
int GPSupdate = 0;
int rc_char_blink = 0;
char TimeDisp[] = {};

int RXPin = 7;
int TXPin = 8;
int GPSBaud = 9600;

byte Year;
byte Month;
byte Date;
byte DoW;
byte Hour;
byte Minute;
byte Second;

bool h12 = false;
bool PM = false;

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
DS3231 Clock;
TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin);


void setup()
{
  mx.setFont(numeric7Seg);
  gpsSerial.begin(GPSBaud);
  mx.begin();
  Wire.begin();
  Clock.setClockMode(false);
  mx.control(MD_MAX72XX::INTENSITY, 0);  
  Serial.begin(9600);
}

void loop()
{
  DCF_Display();
//  if (Clock.getMinute()==0 && Clock.getHour(h12, PM) == 0)
//  {
    while (gpsSerial.available() > 0)
      if (gps.encode(gpsSerial.read())) GPS_clock();
      if (millis() > 5000 && gps.charsProcessed() < 10)
      {
        Serial.println("No GPS detected");
        while(true);
      }
  digitalClockDisplay();
  serial_print_time();                       //print actual time in serial port
}

void GPS_clock()
{
  if (gps.time.isValid() && gps.date.isValid() && GPSupdate == 0)
    {      
      Clock.setMonth(gps.date.month());
      Clock.setDate(Date);
      Clock.setDoW(0);
      Clock.setHour(gps.time.hour());
      Clock.setMinute(gps.time.minute());
      Clock.setSecond(gps.time.second());
      GPSupdate = 1;
    }
}

void DCF_Display()
{
  if (GPSupdate == 0) 
  { 
    rc_char_blink++;
    if (rc_char_blink < 100)
    {
      mx.setPoint(0,0, true);
    }
    else
    {
      mx.setPoint(0,0, false);
    }
    if (rc_char_blink > 100)
    {
      rc_char_blink = 0;
    }
  }
}

void serial_print_time()
{
  Serial.print("Time: ");
  Serial.print(Clock.getHour(h12, PM));
  Serial.print(":");
  Serial.print(Clock.getMinute());
  Serial.print(".");
  Serial.print(Clock.getSecond());
  Serial.println();
}

void digitalClockDisplay()
{
  int mm = Clock.getMinute();
  int ss = Clock.getSecond();
  int hh = Clock.getHour(h12, PM) + 1;
  if (hh ==24) hh = 0;
  TimeDisp[0] = ' ';
  String a,b,c,d;
  if (hh >= 10)
  {
    a = String(hh / 10);
    TimeDisp[1] = a.charAt(0);
  }
    else
    {
      TimeDisp[1] = ' ';
    }
  b = String(hh % 10);
  TimeDisp[2] = b.charAt(0);
  TimeDisp[3] = ':';
  c = String(mm / 10);
  TimeDisp[4] = c.charAt(0);
  d = String(mm % 10);
  TimeDisp[5] = d.charAt(0);
  TimeDisp[6] = '\0';
  TimeDisp[7] = '\0';
  printText(0, MAX_DEVICES-1, TimeDisp);

  if (GPSupdate == 1)
  {
    delay(500);
    TimeDisp[3]=' ';
    printText(0, MAX_DEVICES-1, TimeDisp);
    delay(500);
  } 
  if (mm == 0 && ss == 0) //synchronisation per hour
  { 
    GPSupdate = 0;
  }
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
