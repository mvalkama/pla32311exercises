#include <Arduino.h>
#include <Servo.h>

Servo myservo;

const int PIN_MODECHANGE = PIN2;
const int PIN_SERVOOUT = 9;
const int PIN_POSITIONIN = PIN_A0;

int positionIn;
int servoPosition = 0;
bool directionUp = true;
bool modeAuto = true;
int buttonState = false;
int prevState = false;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10000);

  pinMode(PIN_MODECHANGE, INPUT);
  prevState = digitalRead(PIN_MODECHANGE);
  buttonState = digitalRead(PIN_MODECHANGE);
  myservo.attach(PIN_SERVOOUT);
}

void loop() {
  buttonState = digitalRead(PIN_MODECHANGE);

  if (prevState != true && buttonState) {
    if (modeAuto) {
      modeAuto = false;
    } else {
      modeAuto = true;
    }
  }

  if (modeAuto) {
    if (directionUp) {
      if (servoPosition < 100) {
        servoPosition = servoPosition + 1;
      } else {
        directionUp = false;
      }
    } else {
      if (servoPosition > 0) {
        servoPosition = servoPosition - 1;
      } else {
        directionUp = true;
      }
    }
  } else {
      positionIn = analogRead(PIN_POSITIONIN);
      servoPosition = map(positionIn, 0, 1023, 0, 100);
  }

  Serial.print("position: ");
  Serial.print(servoPosition);
  Serial.print(", buttonState: ");
  Serial.print(buttonState);
  Serial.print(", automatic: ");
  Serial.println(modeAuto);

  myservo.write(servoPosition);
  delay(20);
}