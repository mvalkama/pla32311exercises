#include <Arduino.h>
#include <Morse.h>

Morse morse(13);
long startTime;
String message;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10000);
  startTime = millis();
}

void loop() {
  // Request message
  Serial.println("Enter message to transmit in 10 seconds, end with newline:");
  message = Serial.readStringUntil('\n');

  if (message != NULL && message.length() > 0) {
    morse.sendMessage(message);
    startTime = millis();
  } else if (millis() - startTime > 10000) {
    // If timeout, send sos
    Serial.print("No input\n");
    morse.sos();
    startTime = millis();
  }
}