#include <Adafruit_NeoPixel.h>
 
#define PIN 6
#define LICZBADIOD 500
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LICZBADIOD, PIN, NEO_BRG + NEO_KHZ400);


 
void setup()
{
   Serial.begin(115200);
  pixels.begin(); // Inicjalizacja biblioteki
   pixels.clear();
  Serial.write(pixels.getBrightness());
  Serial.write(pixels.numPixels());

  pixels.setBrightness(10);
  
}
 
void loop()
{
//  for(int i=0; i<LICZBADIOD; i++)
//  {
//    pixels.setPixelColor(i, 255, 0, 0); // Dioda "i" oraz skladowe R=255 G=0 B=0
//    pixels.show(); // Wysylamy dane do lancucha
//    delay(5); // Opoznienie 500ms przed zaswieceniem kolejnej diody
//  }
 

  pixels.setPixelColor(1, 0, 255, 0); // Dioda "i" oraz skladowe R=255 G=0 B=0
  pixels.show();
  delay(100);
  pixels.setPixelColor(1, 255, 0, 0); // Dioda "i" oraz skladowe R=255 G=0 B=0
  pixels.show();
  delay(100);
    pixels.setPixelColor(1, 0, 0, 255); // Dioda "i" oraz skladowe R=255 G=0 B=0
  pixels.show();
  delay(100);
  
}
