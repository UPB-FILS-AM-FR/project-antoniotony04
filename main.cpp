#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
float measureEC();
void showTemperature();
void showTurbidity();
void showEC(float voltage);
#define ONE_WIRE_BUS 2
#define TURBIDITY_PIN A1
#define EC_PIN A0
#define EC_IN1 8
#define EC_IN2 9
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);
unsigned long lastSwitch = 0;
int screenState = 0;
const int screenDelay = 3000;
float ecVoltage = 0.0;
unsigned long lastECRead = 0;
const int ecReadInterval = 3000;
void setup() {
  Serial.begin(9600);
  sensors.begin();
  pinMode(EC_IN1, OUTPUT);
  pinMode(EC_IN2, OUTPUT);
  pinMode(TURBIDITY_PIN, INPUT);
  pinMode(EC_PIN, INPUT);
  lcd.begin(16, 2);
  lcd.backlight();
}
void loop() {
  unsigned long now = millis();
  if (now - lastSwitch > screenDelay) {
    lcd.clear();
    switch (screenState) {
      case 0:
        showTemperature();
        break;
      case 1:
        showTurbidity();
        break;
      case 2:
        if (now - lastECRead > ecReadInterval) {
          ecVoltage = measureEC();
          lastECRead = now;
        }
        showEC(ecVoltage);
        break;
    }
    screenState = (screenState + 1) % 3;
    lastSwitch = now;
  }
}
void showTemperature() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(tempC, 1);
  lcd.print((char)223);
  lcd.print("C");
}
void showTurbidity() {
  int raw = analogRead(TURBIDITY_PIN);
  float voltage = raw * (5.0 / 1023.0);
  lcd.setCursor(0, 0);
  lcd.print("Turbidity:");
  lcd.setCursor(0, 1);
  if (voltage > 2.3)
    lcd.print("Clean water");
  else
    lcd.print("Dirty water");
}
float measureEC() {
  int adc1, adc2;
  digitalWrite(EC_IN1, HIGH);
  digitalWrite(EC_IN2, LOW);
  delay(10);
  adc1 = analogRead(EC_PIN);
  digitalWrite(EC_IN1, LOW);
  digitalWrite(EC_IN2, HIGH);
  delay(10);
  adc2 = analogRead(EC_PIN);
  digitalWrite(EC_IN1, LOW);
  digitalWrite(EC_IN2, LOW);
  float avg = (adc1 + adc2) / 2.0;
  return avg * (5.0 / 1023.0);
}
void showEC(float voltage) {
  lcd.setCursor(0, 0);
  lcd.print("EC: ");
  lcd.print(voltage, 2);
  lcd.print(" V");
  lcd.setCursor(0, 1);
  if (voltage < 2.35)
    lcd.print("No minerals");
  else if (voltage < 4.0)
    lcd.print("Normal minerals");
  else
    lcd.print("Too many minerals");
}
