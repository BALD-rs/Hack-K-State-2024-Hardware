#ifndef GAMESERIALMANAGER_H
#define GAMESERIALMANAGER_H

/**
 * GameSerialManager.h
 * 
 * Useful commands for handling serial input for the hardware component
 * of BALD-rs' Hack K-State 2024 project.
 */

#include <Arduino.h>

#define SPEED 9600

/**
 * Initializes serial
 */
void initSerial();

/**
 * Listens for a command on the COM port and returns it as a string.
 * All commands are 5 characters in length.
 */
String listenForCommand();

/**
 * Processes the given 5 character command. First bit is designator,
 * last four bits are data.
 */
void processCommand(String command);

#endif
