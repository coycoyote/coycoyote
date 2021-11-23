
#include "OneButton.h"
int CKI = 13;                           // pin CKI
int SDI = 11;                           // pin SDI
#define LEDS 17                         // Number of diodes

uint8_t Buffer[18];
int time_ = 30000; //ms
int time1 = 10000; //ms

OneButton button1(A2, true);            // button 1 assigned to A1 board pin
OneButton button2(A1, true);            // button 2 assigned to A2 board pin

void setup()
{
  // set CKI, SDI as outputs pin
  pinMode(CKI, OUTPUT);
  pinMode(SDI, OUTPUT);
  digitalWrite(CKI, LOW);
  delayMicroseconds(500);

  allTurnOFF(); // turn oFF all diodes

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
}

void loop()
{
  button1.tick();
  delay(50);
  button2.tick();
  delay(50);
} // loop
