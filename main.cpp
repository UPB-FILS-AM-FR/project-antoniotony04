#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define EC_IN1 7
#define EC_IN2 6
#define EC_ANALOG A0
#define EC_REF_RESISTOR 1000.0

#define TURBIDITY_PIN A1

#define TEMP_DATA_PIN 2

OneWire oneWire(TEMP_DATA_PIN);
DallasTemperature tempSensor(&oneWire);

const float EC_VOLT_LOW  = 0.20;
const float EC_VOLT_HIGH = 1.12;
const float EC_LOW_UScm  = 0.0;
const float EC_HIGH_UScm = 1413.0;

const float EC_SLOPE  =
    (EC_HIGH_UScm - EC_LOW_UScm) /
    (EC_VOLT_HIGH - EC_VOLT_LOW);

const float EC_OFFSET = EC_VOLT_LOW;

void setup() {
    pinMode(EC_IN1, OUTPUT);
    pinMode(EC_IN2, OUTPUT);

    Serial.begin(9600);

    tempSensor.begin();

    Wire.begin();

    lcd.begin(16, 2);
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("Water Monitor");

    delay(2000);

    lcd.clear();
}

void loop() {

    digitalWrite(EC_IN1, HIGH);
    digitalWrite(EC_IN2, LOW);

    delayMicroseconds(5000);

    int adc1 = analogRead(EC_ANALOG);

    digitalWrite(EC_IN1, LOW);
    digitalWrite(EC_IN2, HIGH);

    delayMicroseconds(5000);

    int adc2 = analogRead(EC_ANALOG);

    float voltage_avg =
        ((adc1 + adc2) / 2.0) * (5.0 / 1023.0);

    float current_mA =
        voltage_avg / EC_REF_RESISTOR * 1000.0;

    float ec_uScm =
        EC_SLOPE * (voltage_avg - EC_OFFSET);

    if (ec_uScm < 0) {
        ec_uScm = 0;
    }

    int turb_raw = analogRead(TURBIDITY_PIN);

    float turb_voltage =
        turb_raw * (5.0 / 1023.0);

    tempSensor.requestTemperatures();

    float tempC =
        tempSensor.getTempCByIndex(0);

    Serial.println("==== WATER QUALITY ====");

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.println(" C");

    Serial.print("EC: ");
    Serial.print(ec_uScm);
    Serial.println(" uS/cm");

    Serial.print("Turbidity Voltage: ");
    Serial.print(turb_voltage, 2);
    Serial.println(" V");

    Serial.println("========================");

    lcd.setCursor(0, 0);

    lcd.print("T:");
    lcd.print(tempC, 1);
    lcd.print("C ");

    lcd.print("EC:");
    lcd.print((int)ec_uScm);

    lcd.setCursor(0, 1);

    lcd.print("Turb:");
    lcd.print(turb_voltage, 1);
    lcd.print("V");

    delay(1500);
}
