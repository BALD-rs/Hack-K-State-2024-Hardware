#include "GameSerialManager.h"
#include <Arduino.h>
#include "LEDDriver.h"
#include "ButtonDriver.h"
#include <TFT_eSPI.h>
extern TFT_eSPI tft;

/**
 * Helper functions
 */
void vote(String command);
void policy(String command);
void startScreen();
void endScreen();


void initSerial() {
    Serial.begin(SPEED);
}


String listenForCommand() {
    while (Serial.available() < 5);

    String command = "";

    for (int i = 0; i < 5; i++) {
        command += (char)Serial.read();
    }

    return command;
}


void processCommand(String command) {
    switch (command.charAt(0)) {
        case 'V':
            vote(command);
            break;

        case 'P':
            policy(command);
            break;

        case 'S':
            startScreen();
            break;
        
        case 'E':
            endScreen();
            break;

        default:
            break;
    }
}



/**
 * Handles voting logic
 */
void vote(String command) {

    // Had to add this because LOUIS KEPT SENDING BAD INPUTS >:(
    bool hasYes = false;
    for (int i = 0; i < 4; i++) {
        if (command.charAt(i + 1) == 'Y') {
            hasYes = true;
            break;
        }
    }

    if (!hasYes) {
        Serial.println("0");
        return;
    }


    // display boxes for each player
    tft.fillScreen(TFT_BLACK);
    const int width = 64;
    const int height = 64;

    for (int i = 1; i <= 4; i++) {
        int xPosition = ((i - 1) % 2) * width;
        int yPosition = ((i - 1) / 2) * height;

        if (command.charAt(i) == 'Y') {
            tft.fillRect(xPosition, yPosition, width, height, TFT_BLACK);
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setTextSize(2);
            tft.setCursor(xPosition + width / 2 - 10, yPosition + height / 2 - 8);
            tft.print("P" + String(i));
        } else {
            tft.fillRect(xPosition, yPosition, width, height, TFT_RED);
            tft.setTextColor(TFT_BLACK, TFT_RED);
            tft.setTextSize(2);
            tft.setCursor(xPosition + width / 2 - 10, yPosition + height / 2 - 8);
            tft.print("P" + String(i));
        }
    }

    // Set LEDs and track enabled buttons based on command
    bool enabled[4] = {false, false, false, false};
    for (int i = 0; i < 4; i++) {
        if (command.charAt(i + 1) == 'Y') {
            digitalWrite(leds[i], HIGH);
            enabled[i] = true;
        } else {
            digitalWrite(leds[i], LOW);
        }
    }

    // Continuously check for button presses on enabled buttons
    bool buttonPressed = false;
    while (!buttonPressed) {
        for (int i = 0; i < 4; i++) {
            if (enabled[i] && digitalRead(buttons[i]) == LOW) {
                Serial.println(i + 1);
                buttonPressed = true;
                break;
            }
        }
        delay(10);
    }

    // Turn LEDs off
    for (int i = 0; i < 4; i++) {
        digitalWrite(leds[i], LOW);
    }
    tft.fillScreen(TFT_BLACK);
}


/**
 * Handles policy selection logic
 */
void policy(String command) {
    int8_t revolt1 = (int8_t)command.charAt(1);
    int8_t cost1 = (int8_t)command.charAt(2);
    int8_t revolt2 = (int8_t)command.charAt(3);
    int8_t cost2 = (int8_t)command.charAt(4);

    const int width = 64;
    const int height = 64;

    // Clear the screen
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    // Display cost1 in top left
    tft.setCursor(width / 4, height / 4);
    tft.print("C1");
    tft.drawLine(width / 4, height / 4 + 16, width / 4 + 20, height / 4 + 16, TFT_WHITE);
    tft.setCursor(width / 4, height / 4 + 20);
    tft.print(cost1);

    // Display revolt1 in bottom left
    tft.setCursor(width / 4, height + height / 4);
    tft.print("R1");
    tft.drawLine(width / 4, height + height / 4 + 16, width / 4 + 20, height + height / 4 + 16, TFT_WHITE);
    tft.setCursor(width / 4, height + height / 4 + 20);
    tft.print(revolt1);

    // Display cost2 in top right
    tft.setCursor(width + width / 4, height / 4);
    tft.print("C2");
    tft.drawLine(width + width / 4, height / 4 + 16, width + width / 4 + 20, height / 4 + 16, TFT_WHITE);
    tft.setCursor(width + width / 4, height / 4 + 20);
    tft.print(cost2);

    // Display revolt2 in bottom right
    tft.setCursor(width + width / 4, height + height / 4);
    tft.print("R2");
    tft.drawLine(width + width / 4, height + height / 4 + 16, width + width / 4 + 20, height + height / 4 + 16, TFT_WHITE);
    tft.setCursor(width + width / 4, height + height / 4 + 20);
    tft.print(revolt2);

    // Set two policy LEDs high
    digitalWrite(leds[0], HIGH);
    digitalWrite(leds[1], HIGH);

    // Continuously check for button presses on the two policy buttons
    bool buttonPressed = false;
    while (!buttonPressed) {
        for (int i = 0; i < 2; i++) {
            if (digitalRead(buttons[i]) == LOW) { 
                Serial.println(i + 1); 
                buttonPressed = true;
                break;
            }
        }

        delay(10);  
    }

    // turn LEDs off
    digitalWrite(leds[0], LOW);
    digitalWrite(leds[1], LOW);

    tft.fillScreen(TFT_BLACK);
}


/**
 * Handles start screen logic
 */
void startScreen() {
    tft.fillScreen(TFT_WHITE); // Clear the screen
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setTextSize(2);

    // turn LEDs on
    for (int i = 0; i < 4; i++) {
        digitalWrite(leds[i], HIGH);
    }

    // Display the message in a straightforward way without complex centering calculations
    tft.setCursor(10, 24);
    tft.print("Press any");

    tft.setCursor(9, 56);
    tft.print("button to");

    tft.setCursor(16, 88);
    tft.print("start...");

    // Wait for a button press to proceed
    bool buttonPressed = false;
    while (!buttonPressed) {
        for (int i = 0; i < 4; i++) {
            if (digitalRead(buttons[i]) == LOW) { 
                Serial.println(i + 1); 
                buttonPressed = true;
                break;
            }
        }
        delay(10);  
    }

    // turn LEDs off
    for (int i = 0; i < 4; i++) {
        digitalWrite(leds[i], LOW);
    }

    tft.fillScreen(TFT_BLACK);
}


/**
 * Handles end screen logic
 */
void endScreen() {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(3);

    tft.setCursor(32, 48);
    tft.print("End!");

    delay(3000);

    tft.fillScreen(TFT_WHITE); 
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setTextSize(2);

    // turn LEDs on
    for (int i = 0; i < 4; i++) {
        digitalWrite(leds[i], HIGH);
    }

    tft.setCursor(10, 24);
    tft.print("Press any");

    tft.setCursor(8, 56);
    tft.print("button to");

    tft.setCursor(4, 88);
    tft.print("play again");

    bool buttonPressed = false;
    while (!buttonPressed) {
        for (int i = 0; i < 4; i++) {
            if (digitalRead(buttons[i]) == LOW) { 
                Serial.println(i + 1); 
                buttonPressed = true;
                break;
            }
        }
        delay(10);  
    }

    // turn LEDs off
    for (int i = 0; i < 4; i++) {
        digitalWrite(leds[i], LOW);
    }

    tft.fillScreen(TFT_BLACK); // Clear the screen
}

