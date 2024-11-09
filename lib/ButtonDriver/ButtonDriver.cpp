#include "ButtonDriver.h"
#include <Arduino.h>

void initButtons() {
    for (int i = 0; i < 4; i++) {
        pinMode(buttons[i], INPUT_PULLUP);
    }
}
