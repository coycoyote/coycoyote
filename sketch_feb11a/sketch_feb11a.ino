

#include "OneButton.h"
// Setup a new OneButton on pin A1.  

OneButton button1(A1, true);
// Setup a new OneButton on pin A2.  
OneButton button2(A2, true);

byte pinOut = 2;  // pins may be 3,5,6,9,10,11
byte pwmValue = 0; // value may be 0 to 255
int duration_one_click = 3000; //milli seconds when 1 click is active
byte j=2;         //first PWM pin in Arduino board
byte wait_between_straits = 2; //ms beetween next straits


void setup(){
pinMode (2, OUTPUT);  
pinMode (3, OUTPUT);  
pinMode (4, OUTPUT);  
pinMode (5, OUTPUT);  
pinMode (6, OUTPUT);  
pinMode (7, OUTPUT);  
pinMode (8, OUTPUT);  
pinMode (9, OUTPUT);  
pinMode (10, OUTPUT);  
pinMode (11, OUTPUT);  
pinMode (12, OUTPUT);
pinMode (13, OUTPUT);
//pinMode(30, INPUT_PULLUP);
//pinMode(31, INPUT_PULLUP);

  // link the button 1 functions.
  button1.attachClick(click1);
  button1.attachDoubleClick(doubleclick1);
  button1.attachLongPressStart(longPressStart1);
  button1.attachLongPressStop(longPressStop1);
  button1.attachDuringLongPress(longPress1);

  // link the button 2 functions.
  button2.attachClick(click2);
  button2.attachDoubleClick(doubleclick2);
  button2.attachLongPressStart(longPressStart2);
  button2.attachLongPressStop(longPressStop2);
  button2.attachDuringLongPress(longPress2);


}
void loop()
{

  button1.tick();
  button2.tick();
  delay(10);
  

}
//



//#####################################################

void inc_brightness(byte pin)
{
  int i;
  for (i=0; i<255; i++)
  {
    analogWrite(pin, i);
    delay(wait_between_straits);
  }
}

void dec_brightness(byte pin)
{
  int i;
  for (i=255; i>-1; i--)
  {
    analogWrite(pin, i);
    delay(wait_between_straits);
  }
}


// This function will be called when the button1 was pressed 1 time (and no 2. button press followed).
void click1() {
  Serial.println("Button 1 click.");
  for (j=2; j<14; j++)
  {
    inc_brightness(j);
  }
  delay(duration_one_click);
  for (j=2; j<14;j++)
  {
    dec_brightness(j);
  }

} // click1


// This function will be called when the button1 was pressed 2 times in a short timeframe.
void doubleclick1() {
  Serial.println("Button 1 doubleclick.");
} // doubleclick1


// This function will be called once, when the button1 is pressed for a long time.
void longPressStart1() {
  Serial.println("Button 1 longPress start");
} // longPressStart1


// This function will be called often, while the button1 is pressed for a long time.
void longPress1() {
  Serial.println("Button 1 longPress...");
} // longPress1


// This function will be called once, when the button1 is released after beeing pressed for a long time.
void longPressStop1() {
  Serial.println("Button 1 longPress stop");
} // longPressStop1


// ... and the same for button 2:

void click2() {
  Serial.println("Button 2 click.");
    for (j=14; j>1; j--)
  {
    inc_brightness(j);
  }
  delay(duration_one_click);
    for (j=14; j>1; j--)
  {
    dec_brightness(j);
  }

} // click2


void doubleclick2() {
  Serial.println("Button 2 doubleclick.");
} // doubleclick2


void longPressStart2() {
  Serial.println("Button 2 longPress start");
} // longPressStart2


void longPress2() {
  Serial.println("Button 2 longPress...");
} // longPress2

void longPressStop2() {
  Serial.println("Button 2 longPress stop");
} // longPressStop2
