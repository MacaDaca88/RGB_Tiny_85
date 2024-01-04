
#ifndef RGB_TINY_85_H
#define RGB_TINY_85_H

#include "Pins.h"  // Include the Pins.h library for defining pin configurations

class RGB {

public:

  // Constructor for the RGB class
  RGB(int red, int green, int blue, int button);

  // Method to turn off the RGB LED
  void off();

  // Method to set the RGB LED color with individual red, green, and blue components
  void setColor(int red, int green, int blue);

  // Overloaded method to set the RGB LED color using an array of RGB values
  void setColor(int rgb[3]);

  // Method to cycle through predefined colors until the button is pressed
  void cycleColors();

  // Method to handle button presses and trigger corresponding actions
  void buttonCycle();

  //Method to change the brightness 0-255
  void setBrightness();

  // Display DEBUG on Serial if Available
  void debug();

  // Static arrays representing RGB values for various predefined colors
  static int Red[3];
  static int Green[3];
  static int Blue[3];
  static int Magenta[3];
  static int Cyan[3];
  static int Yellow[3];
  static int Orange[3];
  static int Purple[3];
  static int Pink[3];
  static int Turquoise[3];
  static int Gray[3];
  static int Olive[3];
  static int Teal[3];
  static int RedOrange[3];
  static int Indigo[3];
  static int DeepPink[3];
  static int SeaGreen[3];
  static int Gold[3];
  static int Tomato[3];

private:
  int _Red, _Green, _Blue, _Button, _Wait;  // Pins and delay values
  unsigned long _Time;                      // Store the UpTime since started
  unsigned long _OldTime = 0;               // Stores last Time
  unsigned long _OldButtonTime = 0;
  unsigned long _ButtonTime;

  int _ButtonState;                         // Store the input of button
  int _LastButtonState;                     // Store the last button state
  int _ColorState;                          // Track the current color state for cycling
  int _Brightness;                          // Store the Brightness value
  int _ButtonCounter = 0;                   // Store the Number of button presses
  unsigned long _ButtonCounterTime = 0;
  unsigned long _ButtonPressDuration = 0;       //Store the Counted time the button is held pressed
  unsigned long _ButtonPressStartTime = 0;      // Store the time when the button is pressed
  unsigned long _LastButtonPressStartTime = 0;  // Store the time of the last button press
  void color(int red, int green, int blue);     // Private method to set the RGB LED color
};

#endif
