#include "LEDDriver.h"
#include <Arduino.h>

void initLEDs() {
    for (int i = 0; i < 4; i++) {
        pinMode(leds[i], OUTPUT);
        digitalWrite(leds[i], LOW);
    }
}
