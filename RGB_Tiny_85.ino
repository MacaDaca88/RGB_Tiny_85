#include "RGB_Tiny_85.h"  // Include the RGB class header file

// Create an instance of the RGB class with specified pin configurations
RGB RGB(RED_PIN, GREEN_PIN, BLUE_PIN, BUTTON_PIN);

// Setup function, called once when the microcontroller starts
void setup() {
  // Turn off the RGB LED during setup
  RGB.off();
}

// Loop function, called repeatedly after setup
void loop() {
  // Continuously monitor the button and perform corresponding actions
  RGB.buttonCycle();
}
