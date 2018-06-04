#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int relayPin = 7;
const int setLow   = 17;
const int setHigh  = 25;
const int deadband = 1;

bool relayOn = false;

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Loading... v.4");
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  relayOn = false;
  delay(1000);
  lcd.clear();
}

void loop() {
  if (! baro.begin()) {
    lcd.clear();
    lcd.print("Couldnt find sensor");
    return;
  }
  
  float tempC = baro.getTemperature();

  lcd.setCursor(0,0);
  lcd.print(tempC); lcd.print((char)223);lcd.print("C ");

  if (tempC > (setLow + deadband) && tempC < (setHigh - deadband)){
    digitalWrite(relayPin, HIGH);
    lcd.setCursor(0,1);
    lcd.print("Relay:ON ");
    relayOn = true;
  }
  else if (tempC < setLow) {
    digitalWrite(relayPin, LOW);
    lcd.setCursor(0,1);
    lcd.print("Relay:OFF");
    relayOn = false;
  }
    else if (tempC > setHigh) {
    digitalWrite(relayPin, LOW);
    lcd.setCursor(0,1);
    lcd.print("Relay:OFF");
    relayOn = false;
  }
  else {
    //digitalWrite(relayPin, LOW);
    //lcd.setCursor(0,1);
    //lcd.print("Relay:OFF");
    //relayOn = false;
  }

  lcd.setCursor(12,0);
  lcd.print("L:"); lcd.print(setLow);
  lcd.setCursor(12,1);
  lcd.print("H:"); lcd.print(setHigh);
  delay(900000);
}
