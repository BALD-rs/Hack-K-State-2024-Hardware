#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include "LEDDriver.h"
#include "ButtonDriver.h"
#include "GameSerialManager.h"

TFT_eSPI tft = TFT_eSPI();
String previousDisplayedNumbers = ""; 

void setup() {
    initSerial();
    initLEDs();
    initButtons();
    
    tft.init();
    tft.setWindow(0, 0, 159, 127);
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(1);
}

void loop() {
    processCommand(listenForCommand());
}
