// Define pin configurations for the RGB LED and button
// Pre Defined pins for Nano/Attiny85


#ifndef PINS_H
#define PINS_H

#ifdef __AVR_ATmega328P__

#define RED_PIN 11    // D11 = Physical pin 8
#define GREEN_PIN 9   // D9 = Physical pin 7
#define BLUE_PIN 10   // D10 = Physical pin 6
#define BUTTON_PIN 2  // D2 = Physical pin

#define DEBUG  // Displays Debug

#endif

#ifdef __AVR_ATtiny85__

#define RED_PIN 0     // PB0 = Physical pin 5
#define GREEN_PIN 1   // PB1 = Physical pin 6
#define BLUE_PIN 4    // PB4 = Physical pin 3
#define BUTTON_PIN 3  // PB3 = Physical pin 2
#endif

#endif
