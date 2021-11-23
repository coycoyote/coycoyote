#include <FastLED.h>

#define LED_PIN 5
#define COLOR_ORDER RGB
#define CHIPSET WS2811

#define BRIGHTNESS 255
#define DATA_PIN 6

const uint8_t kMatrixWidth = 16;
const uint8_t kMatrixHeight = 16;
const bool kMatrixSerpentineLayout = true;

#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
CRGB leds[NUM_LEDS];

void setup() {
FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
FastLED.setBrightness( BRIGHTNESS );
}

void loop()
{
uint32_t ms = millis();
int32_t yHueDelta32 = ((int32_t)cos16( ms * 27 ) * (350 / kMatrixWidth));
int32_t xHueDelta32 = ((int32_t)cos16( ms * 39 ) * (310 / kMatrixHeight));
DrawOneFrame( ms / 65536, yHueDelta32 / 32768, xHueDelta32 / 32768);
FastLED.show();
delay(30);
}

void DrawOneFrame( byte startHue8, int8_t yHueDelta8, int8_t xHueDelta8)
{
byte lineStartHue = startHue8;
for( byte y = 0; y < kMatrixHeight; y++) {
lineStartHue += yHueDelta8;
byte pixelHue = lineStartHue;
for( byte x = 0; x < kMatrixWidth; x++) {
pixelHue += xHueDelta8;
leds[ XY(x, y)] = CHSV( pixelHue, 255, 255);
}
}
}

// Helper function that translates from x, y into an index into the LED array
// Handles both ‘row order’ and ‘serpentine’ pixel layouts.
uint16_t XY( uint8_t x, uint8_t y)
{
uint16_t i;

if( kMatrixSerpentineLayout == false) {
i = (y * kMatrixWidth) + x;
} else {
if( y & 0x01) {
// Odd rows run backwards
uint8_t reverseX = (kMatrixWidth - 1) - x;
i = (y * kMatrixWidth) + reverseX;
} else {
// Even rows run forwards
i = (y * kMatrixWidth) + x;
}
}

return i;
}
