int CKI = 4; // pin CKI
int SDI = 5; // pin SDI
#define LEDS 6 // Liczba wyjść
 
uint8_t Buffer[LEDS];
 
void setup()
{
  // Ustawiamy CKI, SDI jako wyjścia
  pinMode(CKI, OUTPUT);
  pinMode(SDI, OUTPUT);
 
  // Inicjalizujemy WS2803 - zegar w stan niski na >=600us
  digitalWrite(CKI, LOW);
  delayMicroseconds(600);
 
  // Czyścimy bufor i gasimy wyjścia
  for (int Out = 0; Out < LEDS; Out++)
  {
    Buffer[Out] = 0xFF;
  }
 
  Send();
}
 
void Send()
{
    for (int Out = 0; Out < LEDS; Out++)
    {
      shiftOut(SDI, CKI, MSBFIRST, Buffer[Out]);
    }
    delayMicroseconds(600);
}
 
void loop()
{
  // Test wyjść
  for (int Out = 0; Out < LEDS; Out++)
  {
    // Zapalamy i gasimy wybraną diodę
    Buffer[Out] = 0xFF; // PWM 100%
    Send();
    delay(500);
    //Buffer[Out] = 0x00; // PWM 0%
    //Send();
  }
// 
//  // Test PWM
//  for (int Out = 0; Out < LEDS; Out++)
//  {
//    // Rpzjaśniamy
//    for (int i = 0; i < 256; i++)
//    {
//      Buffer[Out] = i;
//      Send();
//      
//    }
//    
// 
//    // ... i gasimy
//    for (int i = 0; i < 256; i++)
//    {
//      Buffer[Out] = (uint8_t)0xFF & 255-i;
//      Send();
//    }
//  }
}
