#include <Arduino.h>
#include <LiquidCrystal.h>

const int TEMP_IN_PIN = 0;
const float VOLTAGE_MULTIPLIER = 5.0; // 3.3 for 3.3V Arduinos

const int LCD_PIN_RS = 12;
const int LCD_PIN_EN = 11;
const int LCD_PIN_D4 = 5;
const int LCD_PIN_D5 = 4;
const int LCD_PIN_D6 = 3;
const int LCD_PIN_D7 = 2;

String labels [2] = { "Workbench", "temperature" };
int screen = 1;

LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_EN, LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
}

void loop() {
  int value = analogRead(TEMP_IN_PIN);
  float voltage = value * VOLTAGE_MULTIPLIER / 1024.0;
  float tempCelsius = (voltage - 0.5) * 100.0; // C = (Voltage - 500mV) * 100, from 10 mv per degree with 500 mV offset
  float tempFahrenheit = (tempCelsius * 9.0 / 5.0) + 32.0;
  
  Serial.print(voltage); Serial.print(" V, ");
  Serial.print(tempCelsius); Serial.print(" C, ");
  Serial.print(tempFahrenheit); Serial.print(" F\n");

  if (++screen > 1) { screen = 0; }

  lcd.clear();

  int dx = (16 - labels[screen].length()) / 2; 
  lcd.setCursor(dx, 0);
  lcd.print(labels[screen]);

  lcd.setCursor(6,1);
  lcd.print((int) tempCelsius); lcd.print(" C");

  delay(2000);
}