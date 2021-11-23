#include <DCF77.h>
//#include <Time.h> // Funktioniert nicht mit DCF77
#include <TimeLib.h> // neue lib einbinden
 
 
#define DCF_PIN 2                // Connection pin to DCF 77 device
#define LEDPin 13                // LED Output 
#define DCF_INTERRUPT 0          // Interrupt number associated with pin
#define timeinterval 2000        // in ms
time_t time;
// Non-inverted input on pin DCF_PIN
DCF77 DCF = DCF77(DCF_PIN,DCF_INTERRUPT, true); 
 
int timediv;
int oldtime; 
 
void setup() {
  Serial.begin(115200); 
  pinMode(LEDPin, OUTPUT);
  DCF.Start();
  Serial.println("Waiting for DCF77 time ... ");
  Serial.println("It will take at least 2 minutes before a first time update.");
  oldtime = millis();
}
 
void loop() {
  timediv = millis()- oldtime;
  digitalWrite(LEDPin, digitalRead (DCF_PIN));
  time_t DCFtime = DCF.getTime(); // Check if new DCF77 time is available
  if (DCFtime!=0)
  {
    Serial.println("Time is updated");
    setTime(DCFtime);
  }    
  if (timediv >= timeinterval){
    oldtime = millis();
    digitalClockDisplay();  
  }
}
 
void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}
 
void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
