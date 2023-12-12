#include "RGB_Tiny_85.h"
#include "Arduino.h"

#define WAIT 1000  // RGB Change Delay


int RGB::Red[3] = { 0, 255, 255 };
int RGB::Green[3] = { 255, 0, 255 };
int RGB::Blue[3] = { 255, 255, 0 };
int RGB::Magenta[3] = { 0, 255, 0 };
int RGB::Cyan[3] = { 255, 0, 0 };
int RGB::Yellow[3] = { 0, 0, 255 };
int RGB::White[3] = { 255, 255, 255 };
int RGB::Orange[3] = { 0, 165, 255 };
int RGB::Purple[3] = { 128, 0, 128 };
int RGB::Pink[3] = { 255, 182, 193 };
int RGB::Turquoise[3] = { 208, 224, 64 };
int RGB::Gray[3] = { 128, 128, 128 };
int RGB::Olive[3] = { 128, 128, 0 };
int RGB::Teal[3] = { 0, 128, 128 };
int RGB::RedOrange[3] = { 255, 69, 0 };
int RGB::Indigo[3] = { 75, 0, 130 };
int RGB::DeepPink[3] = { 255, 20, 147 };
int RGB::SeaGreen[3] = { 46, 139, 87 };
int RGB::Gold[3] = { 255, 215, 0 };
int RGB::Tomato[3] = { 255, 99, 71 };

// Array of colors to cycle through
int rainbow[][3] = {
  { 255, 255, 0 },    // Blue
  { 0, 255, 0 },      // Green
  { 0, 255, 255 },    // Red
  { 255, 0, 255 },    // Magenta
  { 0, 255, 255 },    // Cyan
  { 255, 255, 0 },    // Yellow
  { 0, 0, 0 },        // Black
  { 255, 165, 0 },    // Orange
  { 128, 0, 128 },    // Purple
  { 255, 182, 193 },  // Pink
  { 208, 224, 64 },   // Turquoise
  { 128, 128, 128 },  // Gray
  { 128, 128, 0 },    // Olive
  { 0, 128, 128 },    // Teal
  { 255, 69, 0 },     // Red-Orange
  { 75, 0, 130 },     // Indigo
  { 255, 20, 147 },   // Deep Pink
  { 46, 139, 87 },    // Sea Green
  { 255, 215, 0 },    // Gold
  { 255, 99, 71 }     // Tomato
  // Add more colors as needed
};
int numColors = sizeof(rainbow) / sizeof(rainbow[0]);


RGB::RGB(int red, int green, int blue, int button)
  : _Red(red), _Green(green), _Blue(blue), _Button(button), _LastButtonState(HIGH), _ButtonPressStartTime(0), _LastButtonPressStartTime(0), _Brightness(255) {

  pinMode(_Red, OUTPUT);
  pinMode(_Green, OUTPUT);
  pinMode(_Blue, OUTPUT);
  pinMode(_Button, INPUT_PULLUP);
}


void RGB::color(int red, int green, int blue) {
  analogWrite(_Red, map(red, 0, 255, 0, _Brightness));
  analogWrite(_Green, map(green, 0, 255, 0, _Brightness));
  analogWrite(_Blue, map(blue, 0, 255, 0, _Brightness));
}


void RGB::off() {
  color(255, 255, 255);
  buttonCycle();
}


void RGB::setColor(int red, int green, int blue) {
  color(red, green, blue);
}


void RGB::setColor(int rgb[3]) {
  color(rgb[0], rgb[1], rgb[2]);
}


void RGB::cycleColors() {
  int buttonState = digitalRead(_Button);

  while (buttonState == HIGH) {
    for (int i = 0; i < numColors; ++i) {
      setColor(rainbow[i]);
      delay(WAIT);
      // Check the button state during color cycling
      if (buttonState == LOW) {
        // Button pressed during color cycling
        buttonCycle();
        return;  // Exit the function to avoid turning off the light
      }
    }
  }
}


void RGB::buttonCycle() {
  int buttonState = digitalRead(_Button);
  int buttonCounter = 0;
  if (buttonState == LOW && _LastButtonState == HIGH) {
    _colorState++;
    if (_colorState >= numColors) {
      _colorState = 0;
    }
    // Set the color based on the updated colorState
    setColor(rainbow[_colorState]);
  }

  if (buttonState == HIGH && _LastButtonState == LOW) {
    unsigned long ButtonPressDuration = millis() - _ButtonPressStartTime;
    int ButtonCounterTime = millis();
    if (ButtonPressDuration >= 5000) {
      off();
      _ButtonPressStartTime = 0;  // Reset button press start time
    } else if (ButtonPressDuration >= 3000) {
      cycleColors();
      _ButtonPressStartTime = 0;  // Reset button press start time
    }
    if (buttonCounter >= 2 && ButtonCounterTime <= 1000) {
      setBrightness();
      ButtonCounterTime = 0;
    }
  }
  _LastButtonState = buttonState;
}

void RGB::setBrightness() {

  while (digitalRead(_Button) == LOW) {
    if (_Brightness > 0) {
      _Brightness -= 10;
    } else {
      // If brightness is 0, start increasing it again
      _Brightness += 10;
    }
    delay(100);
    // Apply the current color with the new brightness
    color(Red[_colorState], Green[_colorState], Blue[_colorState]);
  }
  buttonCycle();
}