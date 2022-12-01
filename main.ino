#include <Wire.h> 
#include <math.h>

// Display
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#include <Wire.h>

// Global Vars [Don't do this im just lazy]
int batteryVoltage = 5;
int arduinoVoltage = 5;
int arduinoOutput = 0;
int motorOutput = 0;

// Hardware Pins
static int transistor = 3; // ~
static int pot = 0; // A0

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  pinMode(transistor, OUTPUT);
}

void loop()
{
  int potValue = analogRead(A0);

  // Display
  lcd.setCursor(0,0);
  lcd.print("UNO Output: ");
  lcd.print(potMap(potValue));
  Serial.println(potMap(potValue));
  lcd.setCursor(0,1);
  lcd.print("ACT Output: ");
  lcd.print(potValue); 

  // Motor
  analogWrite(transistor, potMap(potValue));
  
  delay(50);
}

int potMap(int potValue)
{
  // Pot Range
  static double potStart = 1;
  static double potEnd = 1013;
  // Analog Write Range
  static double outputStart = 0;
  static double outputEnd = 255;
  return floor((1.0 * (((outputEnd - outputStart) / (potEnd - potStart)) * (potValue - potStart))) + 0.5);
}
