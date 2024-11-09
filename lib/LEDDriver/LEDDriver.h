#ifndef LEDDRIVER_H
#define LEDDRIVER_H

/**
 * LEDDriver.h
 * 
 * Defines and initializes the LEDs for the hardware component
 * of BALD-rs' Hack K-State 2024 project.
 */

#include <Arduino.h>

/**
 * GPIO pins of the LEDs
 */
const int leds[] = {12, 11, 21, 20}; 

/**
 * Initializes LEDs
 */
void initLEDs();

#endif
