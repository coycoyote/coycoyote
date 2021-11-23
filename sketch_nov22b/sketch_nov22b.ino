/*
*  LCM1602 & Arduino Uno
*  VCC - > 5 V
*  GND - GND
*  SCL -> A5
*  SDA -> A4
*/

#include <Wire.h>   // standardowa biblioteka Arduino
#include <LiquidCrystal_I2C.h> // dolaczenie pobranej biblioteki I2C dla LCD

LiquidCrystal_I2C lcd(0x3F, 16, 2);  // Ustawienie adresu ukladu na 0x27


void setup() 
{
 lcd.begin();   // Inicjalizacja LCD 
 lcd.backlight(); // zalaczenie podwietlenia
 lcd.print("Hello, world!"); //tekst

}

void loop()
{
  lcd.backlight(); // zalaczenie podswietlenia
  delay(5000);
  lcd.noBacklight(); // wylaczenie podswietlenia
  delay(5000);
}
