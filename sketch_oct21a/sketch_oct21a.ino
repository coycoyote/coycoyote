#include <Adafruit_NeoPixel.h>
 
#define PIN 6
#define LICZBADIOD 1
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LICZBADIOD, PIN, NEO_GRB + NEO_KHZ400);
 
void setup()
{
  pixels.begin(); // Inicjalizacja biblioteki
}
 
void loop()
{
  for(int i=0; i<LICZBADIOD; i++)
  {
    pixels.setPixelColor(i, 255, 0, 0); // Dioda "i" oraz skladowe R=255 G=0 B=0
    pixels.show(); // Wysylamy dane do lancucha
    delay(500); // Opoznienie 500ms przed zaswieceniem kolejnej diody
  }
}
