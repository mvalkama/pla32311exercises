#include <Arduino.h>

#define RED 13
#define YELLOW 12
#define GREEN 11
#define BUTTON 7


void checkButton();
void setLights();
void checkMode();

enum State {
  NOGO, PREPARE, GO, STOP, WARN
};

int buttonState = 0;
State state;
unsigned long stateChangedTime;
unsigned long stateDelayTime;
unsigned long currentStateTime;
bool goRequested = false;

void setup() {
  Serial.begin(9600);
  
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUTTON, INPUT);

  stateChangedTime = millis();
  state = WARN;
}

void loop() {
  currentStateTime = millis() - stateChangedTime;
  checkButton();
  checkMode();
  setLights();
}

void checkButton() {
  buttonState = digitalRead(BUTTON);

  if (buttonState == HIGH) {
    switch (state)
    {
    case NOGO:
    case WARN:
      goRequested = true;
      stateChangedTime = millis();
      break;    
    default:
      break;
    }
  }
}

void setLights() {
switch (state) {
  case NOGO:
    digitalWrite(RED, HIGH);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, LOW);
    break;
  case PREPARE:
    digitalWrite(RED, HIGH);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(GREEN, LOW);
    break;
  case GO:
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, HIGH);
    break;
  case STOP:
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(GREEN, LOW);
    break;
  case WARN:
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);

    if (currentStateTime < 500) {
      digitalWrite(YELLOW, HIGH);
    } else {
      digitalWrite(YELLOW, LOW);
    }

    if (currentStateTime > 1000) {
      stateChangedTime = millis();
    }
  }
}

void checkMode() {
switch (state) {
  case NOGO:
    if (goRequested && (currentStateTime >= 1000)) {
      goRequested = false;
      stateChangedTime = millis();
      state = PREPARE;
    }
    break;
  case PREPARE:
    if (currentStateTime >= 3000) {
      stateChangedTime = millis();
      state = GO;
    }
    break;
  case GO:
    if (currentStateTime >= 10000) {
      stateChangedTime = millis();
      state = STOP;
    }
    break;
  case STOP:
    if (currentStateTime >= 1000) {
      stateChangedTime = millis();
      state = NOGO;
    }
    break;
  case WARN:
    if (goRequested) {
      goRequested = false;
      stateChangedTime = millis();
      state = NOGO;
    }
    break;
  }  
}
