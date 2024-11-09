#ifndef BUTTONDRIVER_H
#define BUTTONDRIVER_H

/**
 * ButtonDriver.h
 * 
 * Defines and initializes the buttons for the hardware component
 * of BALD-rs' Hack K-State 2024 project.
 */

#include <Arduino.h>

/**
 * GPIO pins of the buttons
 */
const int buttons[] = {15, 14, 16, 17};

/**
 * Initializes buttons
 */
void initButtons();

#endif
