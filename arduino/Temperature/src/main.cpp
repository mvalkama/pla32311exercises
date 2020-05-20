#include <Arduino.h>

const int TEMP_IN_PIN = 0;
const float VOLTAGE_MULTIPLIER = 5.0; // 3.3 for 3.3V Arduinos

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(TEMP_IN_PIN);
  float voltage = value * VOLTAGE_MULTIPLIER / 1024.0;
  float tempCelsius = (voltage - 0.5) * 100.0; // C = (Voltage - 500mV) * 100, from 10 mv per degree with 500 mV offset
  float tempFahrenheit = (tempCelsius * 9.0 / 5.0) + 32.0;
  
  Serial.print(voltage); Serial.print(" V, ");
  Serial.print(tempCelsius); Serial.print(" C, ");
  Serial.print(tempFahrenheit); Serial.print(" F\n");
  delay(1000);
}