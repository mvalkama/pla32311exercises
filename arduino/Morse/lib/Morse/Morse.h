#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class Morse {
    private:
        const String _supportedLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ?/=:,.";


        // Code from https://fi.scoutwiki.org/Morsen_aakkoset
        const String _codeLetters[36] = {
        ".-",   // A
        "-...", // B
        "-.-.", // C
        "-..",  // D
        ".",    // E
        "..-.", // F
        "--.",  // G
        "....", // H
        "..",   // I
        ".---", // J
        "-.-",  // K
        ".-..", // L
        "--",   // M
        "-.",   // N
        "---",  // O
        ".--.", // P
        "--.-", // Q
        ".-.",  // R
        "...",  // S
        "-",    // T
        "..-",  // U
        "...-", // V
        ".--",  // W
        "-..-", // X
        "-.--", // Y
        "--..", // Z
        "..--..",   // ?
        "-..-.",    // /
        "-...-",    // =
        "---...",   // :
        "--..--",   // ,
        ".-.-.-"    // .
        ".--.-",    // Å   // for future expansion... only ascii for now
        ".-.-",     // Ä   // for future expansion... only ascii for now
        "---.",     // Ö   // for future expansion... only ascii for now
        "..--"      // Ủ   // for future expansion... only ascii for now
    };

    const String _codeNumbers[10] = {
        "-----",    // 0
        ".----",    // 1
        "..---",    // 2
        "...--",    // 3
        "....-",    // 4
        ".....",    // 5
        "-....",    // 6
        "--...",    // 7
        "---..",    // 8
        "----.",    // 9
    };

    const int _unitLength [3] = {
        150,   // slow
        75,    // medium
        50     // fast
    };

    public:
        enum Mode { SLOW, MEDIUM, FAST };

        Morse(int pin);
        void setSpeed(int mode);
        void sos();
        void sendMessage(String msg);
    protected:
        // From https://morsecode.world/international/timing.html
        const int INTRA_CHARACTER_PAUSE = 1;
        const int INTER_CHARACTER_PAUSE = 3;
        const int WORD_PAUSE = 3; // Normally 7, but assuming to be in middle of sentence, there is already a intra and inter character pauses
        const int DOT_LENGHT = 1;
        const int DASH_LENGHT = 3;
    private:
        int _pin;
        int _speed;
        void dot();
        void dash();
        void sendCode(String code);
};

#endif
