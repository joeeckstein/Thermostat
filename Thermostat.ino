#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int relayPin = 7;
const float setLow   = 16;
const float setHigh  = 26.5;
const int deadband = 2;


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
  lcd.setCursor(0,1);
  lcd.print("DB");
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

  if (tempC > (setLow + deadband) && tempC < (setHigh - deadband)){
    digitalWrite(relayPin, HIGH);
    lcd.setCursor(0,1);
    lcd.print("ON ");
  }
  else if (tempC < setLow) {
    digitalWrite(relayPin, LOW);
    lcd.setCursor(0,1);
    lcd.print("OFF");
  }
    else if (tempC > setHigh) {
    digitalWrite(relayPin, LOW);
    lcd.setCursor(0,1);
    lcd.print("OFF");
  }
  else {
    //digitalWrite(relayPin, LOW);
    //lcd.setCursor(0,1);
    //lcd.print("Relay:OFF");
    //relayOn = false;
  }

  lcd.setCursor(9,0);
  lcd.print("L:"); lcd.print(setLow);
  lcd.setCursor(9,1);
  lcd.print("H:"); lcd.print(setHigh);
  delay(3000);
}
