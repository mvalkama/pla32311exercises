#include <Arduino.h>

const int START_PIN = 2;
const int LED_COUNT = 8;
const int DELAY = 100;

void setup() {
  for (int pin = START_PIN; pin < START_PIN + LED_COUNT; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
}

void loop() {
  for (int led = 0; led < LED_COUNT; led++) {
    digitalWrite(START_PIN + led, HIGH);
    delay(DELAY);
    //digitalWrite(START_PIN + led + 1, HIGH);
    //delay(DELAY);
    digitalWrite(START_PIN + led, LOW);
    //delay(DELAY);
  }
  for (int led = LED_COUNT - 2; led > 1; led--) {
    digitalWrite(START_PIN + led, HIGH);
    delay(DELAY);
    //digitalWrite(START_PIN + led - 1, HIGH);
    //delay(DELAY);
    digitalWrite(START_PIN + led, LOW);
    //delay(DELAY);
  }
}