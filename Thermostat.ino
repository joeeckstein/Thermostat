#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int relayPin = 7;
const int setLow   = 17;
const int setHigh  = 25;

// Power by connecting Vin to 3-5V, GND to GND
// Uses I2C - connect SCL to the SCL pin, SDA to SDA pin
// See the Wire tutorial for pinouts for each Arduino
// http://arduino.cc/en/reference/wire
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Loading... v.4");
  pinMode(relayPin, OUTPUT);
  delay(1000);
  lcd.clear();
}

void loop() {
  if (! baro.begin()) {
    lcd.clear();
    lcd.print("Couldnt find sensor");
    return;
  }

  // getPressure is necessary in order to getTemperature
  float pascals = baro.getPressure();
  
  float tempC = baro.getTemperature();

  lcd.setCursor(0,0);
  lcd.print(tempC); lcd.print((char)223);lcd.print("C ");

  if (tempC > setLow && tempC < setHigh){
    digitalWrite(relayPin, HIGH);
    lcd.setCursor(0,1);
    lcd.print("Relay:ON ");
  }
  else {
    digitalWrite(relayPin, LOW);
    lcd.setCursor(0,1);
    lcd.print("Relay:OFF");
  }

  lcd.setCursor(12,0);
  lcd.print("L:"); lcd.print(setLow);
  lcd.setCursor(12,1);
  lcd.print("H:"); lcd.print(setHigh);
  delay(900000);
}
