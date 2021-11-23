#include <Wire.h>
#include <MD_MAX72xx.h>
#include "DCF77.h"
#include <TimeLib.h>
#include <DS1307RTC.h>

#include <LiquidCrystal_I2C.h> // dolaczenie pobranej biblioteki I2C dla LCD

LiquidCrystal_I2C lcd(0x3F, 16, 2);  // Ustawienie adresu ukladu na 0x27

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

#define DCF_PIN 2           // Pin für den DCF 77 setzen
#define DCF_INTERRUPT 0    // Interrupt Nummer, die dem Pin zugeordnet ist

#define CHAR_SPACING  1 // pixels between characters
#define BUF_SIZE  75

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
DCF77 DCF = DCF77(DCF_PIN, DCF_INTERRUPT);
time_t time;

char message[BUF_SIZE] = {" 00:00\n"};
int DCFupdate = 0;
int rc_char_blink = 0;
tmElements_t tm; 
volatile boolean flag;
 
void setup()
{
  Serial.begin(9600);
  DCF.Start();
  pinMode(DCF_PIN, INPUT);
  Wire.begin();
  setSyncProvider(RTC.get);
  pinMode(13, OUTPUT);
  pinMode(keyHor, INPUT_PULLUP);
  pinMode(keyMin, INPUT_PULLUP);
  pinMode(keyPL, INPUT_PULLUP);
  mx.begin(); 
  mx.control(MD_MAX72XX::INTENSITY, 0);
  RTC.set(0);
   lcd.init();   // Inicjalizacja LCD 
 lcd.backlight(); // zalaczenie podwietlenia
  
}
 
void loop(){

  byte second, minute, hour; 
  DCF_Display();
  DCF_auslesen();

  RTC.read(tm);
  hour = tm.Hour;
  minute = tm.Minute;
  second = tm.Second;

    Serial.print("  Hour: ");
    Serial.print(hour);
    Serial.print("  Minutes: ");
    Serial.print(minute);
    Serial.print("  Seconds: ");
    Serial.print(second);
    Serial.println("");

  char TimeDisp[] = {' ',' ',' ',':',' ',' ',' ',' '}; 

  TimeDisp[0] = ' ';
  String a,b,c,d;
  if (hour >= 10)
  {
    a = String(hour / 10);
    TimeDisp[1] = a.charAt(0);
  }
    else
    {
      TimeDisp[1] = ' ';
    }
  b = String(hour % 10);
  TimeDisp[2] = b.charAt(0);
  TimeDisp[3] = ':';
  c = String(minute / 10);
  TimeDisp[4] = c.charAt(0);
  d = String(minute % 10);
  TimeDisp[5] = d.charAt(0);
  TimeDisp[6] = ' ';
  TimeDisp[7] = ' ';
  

  if (!digitalRead(keyHor) && !digitalRead(keyPL)){   
      second = 0;     
      hour++;  
      if (hour > 23) hour = 0;
      tm.Hour = hour;
      tm.Second = second;
      RTC.write(tm);  
      delay(200);
  }
  if (!digitalRead(keyMin) && !digitalRead(keyPL)){   // минуты
      second = 0;
      minute++;
      if (minute > 59) minute = 0;
        tm.Minute = minute;
        tm.Second = second;
        RTC.write(tm);
      delay(200);
  }
  lcd.print(TimeDisp); 
  printText(0, MAX_DEVICES-1, TimeDisp);
  if (digitalRead(keyPL) && DCFupdate == 1)
  {
    delay(500);
    TimeDisp[3]=' ';
  }
  printText(0, MAX_DEVICES-1, TimeDisp);
  lcd.print(TimeDisp);

  if (digitalRead(keyPL) && DCFupdate == 1)
  {
    delay(500);
  }
  DCF_Update();
}

//=========================================================================================
void DCF_auslesen() {

  time_t DCFtime = DCF.getTime(); // Prüfen Sie, ob eine neue DCF77-Zeit verfügbar ist
  Serial.print("DCF77 time:");
  Serial.println(DCFtime);
  if (DCFtime != 0)
  {
    setTime(DCFtime);
    RTC.set(now());
    DCFupdate = 1;
  }
}
//----------------------------------------------------------------------------------------

void DCF_Display() {

  if (DCFupdate == 0) { // Zeigt ein blinkendes Symbol während der Synchronisationsphase an
    rc_char_blink++;

    if (rc_char_blink < 50) {
       // mx.setPoint(0,0, true);
       lcd.backlight();
    }
    else {
      //mx.setPoint(0,0, false);
      lcd.noBacklight();
    }
    if (rc_char_blink > 100) {
      rc_char_blink = 0;

    }
  }
}
//----------------------------------------------------------------------------------------

void DCF_Update() {
  int mm = minute();
  if (mm == 0) { //Synchronisation per hour
    DCFupdate = 0;
  }
}

//----------------------------------------------------------------------------------------

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
