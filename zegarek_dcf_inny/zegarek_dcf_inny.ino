#include <DCF77.h>
//#include <Time.h> // Funktioniert nicht mit DCF77
#include <TimeLib.h> // neue lib einbinden
#include <Adafruit_BMP085.h>
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif
#include <LiquidCrystal_I2C.h> // dolaczenie pobranej biblioteki I2C dla LCD

//LiquidCrystal_I2C lcd(0x3F, 20, 4);  // Ustawienie adresu ukladu na 0x27
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Ustawienie adresu ukladu na 0x27
Adafruit_BMP085 bmp;
time_t time;
 
#define DCF_PIN 2                // Connection pin to DCF 77 device
#define LEDPin 13                // LED Output 
#define DCF_INTERRUPT 0          // Interrupt number associated with pin
#define timeinterval 1000        // in ms
// Non-inverted input on pin DCF_PIN
DCF77 DCF = DCF77(DCF_PIN,DCF_INTERRUPT, true); 
uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
uint8_t clock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
uint8_t retarrow[8] = {0x1,0x1,0x5,0x9,0x1f,0x8,0x4};
byte deg[8] = {
  B00100,
  B01010,
  B01010,
  B00100,
  B00000,
  B00000,
  B00000,
};

byte temp[8] = {
  B00000,
  B00100,
  B00100,
  B00100,
  B01110,
  B01010,
  B01110,
  B00000
};



int timediv;
int oldtime; 
bool flag = true;
bool synced = false;

void setup() {
  Serial.begin(115200); 
  pinMode(LEDPin, OUTPUT);
  DCF.Start();
  Serial.println("Waiting for DCF77 time ... ");
  Serial.println("It will take at least 2 minutes before a first time update.");
  oldtime = millis();
  lcd.init();   // Inicjalizacja LCD 
  lcd.backlight(); // zalaczenie podwietlenia
  lcd.clear();
  lcd.createChar(0, bell);
  lcd.createChar(1, note);
  lcd.createChar(2, clock);
  lcd.createChar(3, heart);
  lcd.createChar(4, duck);
  lcd.createChar(5, check);
  lcd.createChar(6, cross);
  lcd.createChar(7, retarrow);
  lcd.createChar(8, deg);
  lcd.createChar(9, temp);
  lcd.home();
    if (!bmp.begin()) {
      Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
}
 
void loop() {
  timediv = millis()- oldtime;
  digitalWrite(LEDPin, digitalRead (DCF_PIN));
  time_t DCFtime = DCF.getTime(); // Check if new DCF77 time is available
  if (DCFtime!=0)
  {
    Serial.println("Time is updated");
    setTime(DCFtime);
    synced = true;
  }    
  if (timediv >= timeinterval){
    oldtime = millis();
    digitalClockDisplay();  
  }

  if (hour()==0 && minute()==0 && second() == 0){
    synced = false;
  }
}



void digitalClockDisplay(){
  lcd.print("     ");
  print_time();
  lcd.setCursor(6,1);
  print_date();
  lcd.setCursor(0,2);
    print_temperature();
  lcd.print("     ");
  print_pressure();
  lcd.home();
 }

 void print_temperature(){
    lcd.printByte(9);
    lcd.print(bmp.readTemperature(),1);
    lcd.printByte(8);
    lcd.print("C");
 }

void print_pressure(){
    lcd.print(int(bmp.readPressure()/100)); 
    lcd.print("hPa");
}

void print_time(){
  if (synced == false){
    if (flag == true) {
      lcd.printByte(2);
    } else {
      lcd.print(" ");
    }
  } else {
    lcd.printByte(2);
  }
    if (hour()<10)
  {
    lcd.print("0");
    lcd.print(hour());
  } else {
    lcd.print(hour());
  }
  
  if (flag == true)
  {
    lcd.print(":");
    flag = false;
   
  } else {
    lcd.print(" ");
    flag = true;
  }
  
  if (minute()<10)
  {
    lcd.print("0");
    lcd.print(minute());
  } else {
    lcd.print(minute());
  }
  lcd.print(" ");
  if (second()<10)
    {
      lcd.print("0");
      lcd.print(second());
    } else {
      lcd.print(second());
    }
}


void print_date(){
  lcd.print(year());
  lcd.print("/");
  lcd.print(month());
  lcd.print("/");
  lcd.print(day());
}
