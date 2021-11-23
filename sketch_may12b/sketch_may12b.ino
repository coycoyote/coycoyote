/***************************************************
  This is our GFX example for the Adafruit ILI9341 TFT FeatherWing
  ----> http://www.adafruit.com/products/3315

  Check out the links above for our tutorials and wiring diagrams

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <Wire.h>
#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "Adafruit_ILI9341_Albert.h"
#include <TimeLib.h>
#define TFT_CS   10
#define TFT_DC   9


byte a=0;
bool flag = true;
int timeinterval=1000;
int oldtime;
int timediv;
time_t time;

const int16_t
  pixelWidth  = 5,  // TFT dimensions
  pixelHeight = 15;

const byte TFT_RST = A0;

//uint16_t buffer[pixelWidth * pixelHeight]; 


//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_ILI9341_Albert tft = Adafruit_ILI9341_Albert(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Wire.begin();
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  oldtime = millis();
  
}



void loop(void) {

//    tft.setRotation(rotation);

  timediv = millis()- oldtime;
  
  if (timediv >= timeinterval){
  oldtime = millis();

 
  
  
  }
  testText(); 

//    delay(1000);
//  tft.fillScreen(ILI9341_BLACK); 
//  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK); // ILI9341_BLACK needed, else background is white
//  tft.setCursor(0, 40); 
//  tft.println("Float");
//  testFloat();
//  tft.setFont();

}



void test()
{ for(int i=100; i>=0; i-=50)
  { tft.setCursor(0, 90); 
    delay(500);
    tft.printNew(i, 3); // max number is 100
  }
}

void testFloat()
{ tft.setCursor(0, 90); 
  tft.printNew(333.3333, 1, 5); 
  delay(500);
  tft.printNew(-3.3333, 2, 5); 
  delay(500);
  tft.printNew(-0.1111, 1, 5); 
  delay(500);
}

//unsigned long testFillScreen() {
//  unsigned long start = micros();
//  tft.fillScreen(ILI9341_BLACK);
//  yield();
//  tft.fillScreen(ILI9341_RED);
//  yield();
//  tft.fillScreen(ILI9341_GREEN);
//  yield();
//  tft.fillScreen(ILI9341_BLUE);
//  yield();
//  tft.fillScreen(ILI9341_BLACK);
//  yield();
//  return micros() - start;
//}

unsigned long testText() {
  
  tft.setCursor(12, 5);
  
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(3);
  tft.println("DCF-77 CLOCK");
  tft.println("");
  
  tft.setTextColor(ILI9341_WHITE); tft.setTextSize(5);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  if (hour()<10)
  {
    tft.print("0");
    tft.print(hour());
  } else {
    tft.print(hour());
  }

  if (flag==true){
    tft.printNew(":"," ");
    flag=false;
    }
  else
  {
    tft.print(" ");
    flag=true;
  }
  if (minute()<10)
  {
    tft.print("0");
    tft.print(minute());
  } else {
    tft.print(minute());
  }
  tft.print(" ");
  tft.setTextSize(3);
  if (second()<10)
    {
      tft.print("0");
      tft.printNew(second(),0);
    } else {
       
      tft.printNew(second(),0);
    }
  tft.println("");
  tft.println("");
  tft.println("");

  //tft.drawRect(0, 50, 240, 120, ILI9341_BLACK);




//  tft.sendCommand(ILI9341_DISPOFF);
//  tft.sendCommand(ILI9341_DISPON);
  
//  tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
//  tft.println(0xDEADBEEF, HEX);
//  tft.println();
//  tft.setTextColor(ILI9341_GREEN);
//  tft.setTextSize(6);
//  tft.println("Groop");
//  tft.setTextSize(2);
//  tft.println("I implore thee,");
//  tft.setTextSize(1);
//  tft.println("my foonting turlingdromes.");
//  tft.println("And hooptiously drangle me");
//  tft.println("with crinkly bindlewurdles,");
//  tft.println("Or I will rend thee");
//  tft.println("in the gobberwarts");
//  tft.println("with my blurglecruncheon,");
//  tft.println("see if I don't!");
}

//unsigned long testLines(uint16_t color) {
//  unsigned long start, t;
//  int           x1, y1, x2, y2,
//                w = tft.width(),
//                h = tft.height();

//  tft.fillScreen(ILI9341_BLACK);
//  yield();
//  
//  x1 = y1 = 0;
//  y2    = h - 1;
//  start = micros();
//  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
//  x2    = w - 1;
//  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
//  t     = micros() - start; // fillScreen doesn't count against timing
//
//  yield();
//  tft.fillScreen(ILI9341_BLACK);
//  yield();
//
//  x1    = w - 1;
//  y1    = 0;
//  y2    = h - 1;
//  start = micros();
//  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
//  x2    = 0;
//  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
//  t    += micros() - start;
//
//  yield();
//  tft.fillScreen(ILI9341_BLACK);
//  yield();
//
//  x1    = 0;
//  y1    = h - 1;
//  y2    = 0;
//  start = micros();
//  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
//  x2    = w - 1;
//  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
//  t    += micros() - start;
//
//  yield();
//  tft.fillScreen(ILI9341_BLACK);
//  yield();
//
//  x1    = w - 1;
//  y1    = h - 1;
//  y2    = 0;
//  start = micros();
//  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
//  x2    = 0;
//  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
//
//  yield();
//  return micros() - start;
//}
//
//unsigned long testFastLines(uint16_t color1, uint16_t color2) {
//  unsigned long start;
//  int           x, y, w = tft.width(), h = tft.height();
//
//  tft.fillScreen(ILI9341_BLACK);
//  start = micros();
//  for(y=0; y<h; y+=5) tft.drawFastHLine(0, y, w, color1);
//  for(x=0; x<w; x+=5) tft.drawFastVLine(x, 0, h, color2);
//
//  return micros() - start;
//}
//
//unsigned long testRects(uint16_t color) {
//  unsigned long start;
//  int           n, i, i2,
//                cx = tft.width()  / 2,
//                cy = tft.height() / 2;
//
//  tft.fillScreen(ILI9341_BLACK);
//  n     = min(tft.width(), tft.height());
//  start = micros();
//  for(i=2; i<n; i+=6) {
//    i2 = i / 2;
//    tft.drawRect(cx-i2, cy-i2, i, i, color);
//  }
//
//  return micros() - start;
//}
//
//unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
//  unsigned long start, t = 0;
//  int           n, i, i2,
//                cx = tft.width()  / 2 - 1,
//                cy = tft.height() / 2 - 1;
//
//  tft.fillScreen(ILI9341_BLACK);
//  n = min(tft.width(), tft.height());
//  for(i=n; i>0; i-=6) {
//    i2    = i / 2;
//    start = micros();
//    tft.fillRect(cx-i2, cy-i2, i, i, color1);
//    t    += micros() - start;
//    // Outlines are not included in timing results
//    tft.drawRect(cx-i2, cy-i2, i, i, color2);
//    yield();
//  }
//
//  return t;
//}
//
//unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
//  unsigned long start;
//  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;
//
//  tft.fillScreen(ILI9341_BLACK);
//  start = micros();
//  for(x=radius; x<w; x+=r2) {
//    for(y=radius; y<h; y+=r2) {
//      tft.fillCircle(x, y, radius, color);
//    }
//  }
//
//  return micros() - start;
//}
//
//unsigned long testCircles(uint8_t radius, uint16_t color) {
//  unsigned long start;
//  int           x, y, r2 = radius * 2,
//                w = tft.width()  + radius,
//                h = tft.height() + radius;
//
//  // Screen is not cleared for this one -- this is
//  // intentional and does not affect the reported time.
//  start = micros();
//  for(x=0; x<w; x+=r2) {
//    for(y=0; y<h; y+=r2) {
//      tft.drawCircle(x, y, radius, color);
//    }
//  }
//
//  return micros() - start;
//}
//
//unsigned long testTriangles() {
//  unsigned long start;
//  int           n, i, cx = tft.width()  / 2 - 1,
//                      cy = tft.height() / 2 - 1;
//
//  tft.fillScreen(ILI9341_BLACK);
//  n     = min(cx, cy);
//  start = micros();
//  for(i=0; i<n; i+=5) {
//    tft.drawTriangle(
//      cx    , cy - i, // peak
//      cx - i, cy + i, // bottom left
//      cx + i, cy + i, // bottom right
//      tft.color565(i, i, i));
//  }
//
//  return micros() - start;
//}
//
//unsigned long testFilledTriangles() {
//  unsigned long start, t = 0;
//  int           i, cx = tft.width()  / 2 - 1,
//                   cy = tft.height() / 2 - 1;
//
//  tft.fillScreen(ILI9341_BLACK);
//  start = micros();
//  for(i=min(cx,cy); i>10; i-=5) {
//    start = micros();
//    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
//      tft.color565(0, i*10, i*10));
//    t += micros() - start;
//    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
//      tft.color565(i*10, i*10, 0));
//    yield();
//  }
//
//  return t;
//}
//
//unsigned long testRoundRects() {
//  unsigned long start;
//  int           w, i, i2,
//                cx = tft.width()  / 2 - 1,
//                cy = tft.height() / 2 - 1;
//
//  tft.fillScreen(ILI9341_BLACK);
//  w     = min(tft.width(), tft.height());
//  start = micros();
//  for(i=0; i<w; i+=6) {
//    i2 = i / 2;
//    tft.drawRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(i, 0, 0));
//  }
//
//  return micros() - start;
//}
//
//unsigned long testFilledRoundRects() {
//  unsigned long start;
//  int           i, i2,
//                cx = tft.width()  / 2 - 1,
//                cy = tft.height() / 2 - 1;
//
//  tft.fillScreen(ILI9341_BLACK);
//  start = micros();
//  for(i=min(tft.width(), tft.height()); i>20; i-=6) {
//    i2 = i / 2;
//    tft.fillRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(0, i, 0));
//    yield();
//  }
//
//  return micros() - start;
//}
