#include <Arduino.h>

const int buttonPins[] = {15, 14, 16, 17}; // button pins
const int ledPins[] = {12, 11, 21, 20};    // LED pins

void setup() {
    // initialize LEDs as output
    for (int i = 0; i < 4; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }

    // initialize buttons as inputs with internal pullups
    for (int i = 0; i < 4; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }
}

void loop() {
  // if button pressed, turn LED on
    for (int i = 0; i < 4; i++) {
        if (digitalRead(buttonPins[i]) == LOW) { 
            digitalWrite(ledPins[i], HIGH);
        } else {
            digitalWrite(ledPins[i], LOW);
        }
    }
}
