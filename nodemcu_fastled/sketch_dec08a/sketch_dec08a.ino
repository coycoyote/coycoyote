/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLCvu0tfTb"
#define BLYNK_DEVICE_NAME "RBG"
#define BLYNK_AUTH_TOKEN "SrhjPwAcki6ld_SmI6OYOwRLaSFBl-wf"


#include "FastLED.h"
#define NUM_LEDS1 100
#define LED_TYPE    GS1903
#define COLOR_ORDER RGB
CRGB leds1[NUM_LEDS1];

#define PIN1 D2
int data=255;
int r,g,b;

// Comment this out to disable prints and save space
//#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "DOM24";
char pass[] = "38843884";


// This function is called every time the Virtual Pin 0 state changes
//BLYNK_WRITE(V0)
//{
//  // Set incoming value from pin V0 to a variable
//  int value = param.asInt();
//
//  // Update state
//  Blynk.virtualWrite(V1, value);
//}

// This function is called every time the device is connected to the Blynk.Cloud
//BLYNK_CONNECTED()
//{
//  // Change Web Link Button message to "Congratulations!"
////  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
////  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
////  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
//}

// This function sends Arduino's uptime every second to Virtual Pin 2.
//void myTimerEvent()
//{
//  // You can send any value at any time.
//  // Please don't send more that 10 values per second.
////  Blynk.virtualWrite(V2, millis() / 1000);
//}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  FastLED.addLeds<LED_TYPE, PIN1, COLOR_ORDER>(leds1, NUM_LEDS1).setCorrection(TypicalPixelString);
//  FastLED.addLeds<LED_TYPE, PIN1, COLOR_ORDER>(leds1, NUM_LEDS1).setCorrection(UncorrectedColor);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
//  timer.setInterval(1000L, myTimerEvent);
r=50;
b=50;
g=50;
data=50;
static1(r, g, b, data);


}

BLYNK_WRITE(V3)
{
  r = param[0].asInt();
  g = param[1].asInt();
  b = param[2].asInt();
  Serial.println("R: " + String(r) + "   G: "+ String(g) + "   B: " + String(b));
  static1(r, g, b, data);
}

void loop()
{
  Blynk.run();
//  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}

BLYNK_WRITE(V2)
{
data = param.asInt();
Serial.println("Brightness: " + String(data));
static1(r, g, b, data);
}
void static1(int r, int g, int b,int brightness)
{
  FastLED.setBrightness(brightness);
  for (int i = 0; i < NUM_LEDS1; i++ )
  {
    leds1[i] = CRGB(r, g, b);
  }
  FastLED.show();
}
