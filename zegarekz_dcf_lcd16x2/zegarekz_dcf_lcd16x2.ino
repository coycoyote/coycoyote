#include <Wire.h>
#include "DCF77.h"
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <LiquidCrystal_I2C.h> // dolaczenie pobranej biblioteki I2C dla LCD

#define CLK 6         
#define DIO 7 
#define keyHor 5
#define keyMin 4 
#define keyPL  3
#define DS3231_I2C_ADDRESS 0x68

#define DCF_PIN 2           // Pin für den DCF 77 setzen
#define DCF_INTERRUPT 0    // Interrupt Nummer, die dem Pin zugeordnet ist
#define LED_PIN 13

#define CHAR_SPACING  1 // pixels between characters
#define BUF_SIZE  75

LiquidCrystal_I2C lcd(0x3F, 16, 2);  // Ustawienie adresu ukladu na 0x3F

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
  //pinMode(13, OUTPUT);
  pinMode(keyHor, INPUT_PULLUP);
  pinMode(keyMin, INPUT_PULLUP);
  pinMode(keyPL, INPUT_PULLUP);
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

  if (digitalRead(keyPL) && DCFupdate == 1)
  {
    delay(500);
    TimeDisp[3]=' ';
  }

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
    if (rc_char_blink < 10) {
       digitalWrite(LED_PIN, HIGH);
    }
    else {
      digitalWrite(LED_PIN, LOW);
    }
    if (rc_char_blink > 20) {
      rc_char_blink = 0;

    }
  }
  else {
  digitalWrite(LED_PIN, HIGH);    //if DCF-77 updated suceffully stop blink
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
