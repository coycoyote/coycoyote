#include "DCF77.h" //Alle DCF77 Funktionen laufen ueber diese Bibliothek.
#include "TimeLib.h" //Time.h hat bei mir nie funktioniert, habe TimeLib.h eingebunden, dann gehts.

#define DCF_PIN 2 // Verbindung zum DCF77 Arduino UNO PIN
#define DCF_INTERRUPT 0 // Interrupt number associated with pin
#define PIN_LED 13 // Status von der Verbindung an LED-PIN 13

// Librarys für LCD-Display
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2); //Hier wird festgelegt um was für einen Display es sich handelt.

//time_t time;
// DCF77 DCF = DCF77(DCF_PIN, DCF_INTERRUPT); // Dieser Eintrag sollte für andere Module aktiviert werden...
// für das DCF-Modul von ELV muss das Signal invertiert werden, deshalb so:
DCF77 DCF = DCF77(DCF_PIN, DCF_INTERRUPT, false); // false für invertiertes Signal
// wurde ein gueltiges Signal gefunden
bool g_bDCFTimeFound = false;

void setup()
{
pinMode(PIN_LED, OUTPUT);
Serial.begin(9600);

lcd.init(); //Im Setup wird der LCD gestartet
lcd.backlight(); //Hintergrundbeleuchtung einschalten (lcd.noBacklight(); schaltet die Beleuchtung aus).

DCF.Start();
lcd.setCursor(0, 3); // Spalte, Zeile,  0, 0 entspricht 1. Spalte oder 1. Zeile
lcd.print("DCF77 mit LCD V1.0");
Serial.println("Warte auf DCF77 Zeit... ");
Serial.println("Es dauert in den meisten faellen mindestens 2 Minuten bis die Zeit aktualisiert wird.");
}

void loop()
{
// delay(950);
// das Signal wird nur alle 5 Sekunden abgefragt
delay(5000);

digitalWrite(PIN_LED, HIGH);
delay(50);
digitalWrite(PIN_LED, LOW);

time_t DCFtime = DCF.getTime(); // Check if new DCF77 time is available
if (DCFtime != 0)
{
Serial.println("Aktuelle Zeit wurde empfangen!");
setTime(DCFtime);
g_bDCFTimeFound = true;

}

// die Uhrzeit wurde gesetzt, also LED nach kurzer Zeit ein
if (g_bDCFTimeFound)
{
delay(50);
digitalWrite(PIN_LED, HIGH);
}
digitalClockDisplay();
}

void digitalClockDisplay()
{
// Anzeigen der Zeit auf dem 20x4 LCD-Display
 
lcd.setCursor(0, 0);
if (hour()<10){lcd.print("0");}
lcd.print(hour()); lcd.print(":");
if (minute()<10){lcd.print("0");}
lcd.print(minute()); lcd.print(":");
if (second()<10){lcd.print("0");}
lcd.print(second());

lcd.setCursor(0, 1);
if (day()<10){lcd.print("0");}
lcd.print(day()); lcd.print(".");
if (month()<10){lcd.print("0");}
lcd.print(month()); lcd.print(".");
lcd.print(year());

// Anzeigen der Zeit auf dem seriellen Monitor am PC
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

void printDigits(int digits)
{
// Kleines Skript um bei Minuten und Sekunden eine 0 vornean zu stellen
Serial.print(":");
if(digits < 10)
Serial.print('0');
Serial.print(digits);
}
