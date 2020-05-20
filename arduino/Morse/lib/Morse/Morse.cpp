#include "Arduino.h"
#include "Morse.h"

Morse::Morse(int pin) {
    pinMode(pin, OUTPUT);
    _pin = pin;
    setSpeed(MEDIUM);
}

void Morse::dot() {
    Serial.print(".");
    digitalWrite(_pin, HIGH);
    delay(_speed * DOT_LENGHT);
    digitalWrite(_pin, LOW);
}

void Morse::dash() {
    Serial.print("-");
    digitalWrite(_pin, HIGH);
    delay(_speed * DASH_LENGHT);
    digitalWrite(_pin, LOW);
}

void Morse::sos() {
    sendMessage("SOS");
}

void Morse::sendMessage(String message) {
    message.toUpperCase();  // no lowercase in Morse code

    Serial.println("Sending: " + message);

    // Loop through whole message
    for (unsigned int i = 0; i < message.length(); i++) {
        // Pick a charater
        char letter = message.charAt(i);

        if (letter == 0x20) {
            // If space, then delay for word pause
            Serial.print(" ");
            delay(_speed * WORD_PAUSE);
        } else if ((letter >= 0x41 && letter <= 0x5a) 
            || (letter == 0x3a) || (letter == 0x3d) || (letter == 0x3f) 
            || (letter == 0x2f) || (letter == 0x2c) || (letter == 0x2e) ) {
            // Else find the code for the letter (A...Z?=/:.,)
            int codeIndex = _supportedLetters.indexOf(letter);
            sendCode(_codeLetters[codeIndex]);            
            delay(_speed * INTRA_CHARACTER_PAUSE);
        } else if (letter >= 0x30 && letter <= 0x39) {
            int codeIndex = letter - 0x30;
            sendCode(_codeNumbers[codeIndex]);            
            delay(_speed * INTRA_CHARACTER_PAUSE);
        }
    }

    Serial.print("\n");
}

void Morse::sendCode(String code) {
    for (unsigned int j = 0; j < code.length(); j++) {
        char signal = code.charAt(j);
        if (signal == 0x2d) {
            dash();
        } else {
            dot();
        }
        delay(_speed * INTER_CHARACTER_PAUSE);
    }
}

void Morse::setSpeed(int mode) {
    _speed = _unitLength[mode];
}