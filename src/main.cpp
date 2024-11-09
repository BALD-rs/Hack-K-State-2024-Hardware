#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

const int buttonPins[] = {15, 14, 16, 17}; // button pins
const int ledPins[] = {12, 11, 21, 20};    // LED pins

TFT_eSPI tft = TFT_eSPI();
String previousDisplayedNumbers = ""; 

void setup() {
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK); 

    // Initialize LEDs as output
    for (int i = 0; i < 4; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }

    // Initialize buttons as inputs with internal pullups
    for (int i = 0; i < 4; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }
}

void loop() {
    String displayedNumbers = "";

    for (int i = 0; i < 4; i++) {
        if (digitalRead(buttonPins[i]) == LOW) { // Button pressed
            digitalWrite(ledPins[i], HIGH);
            displayedNumbers += String(i + 1) + " "; // Append button number to display
        } else { 
            digitalWrite(ledPins[i], LOW);
        }
    }

    if (displayedNumbers != previousDisplayedNumbers) {
        tft.fillRect(10, 10, 120, 20, TFT_BLACK);
        tft.setCursor(10, 10);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextSize(2);

        if (displayedNumbers.length() > 0) {
            tft.print(displayedNumbers);
        }
        previousDisplayedNumbers = displayedNumbers;
    }
}
