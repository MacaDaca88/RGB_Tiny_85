#include "RGB_Tiny_85.h"
#include "Arduino.h"

#define WAIT 1000  // RGB Change Delay


int RGB::Red[3] = { 0, 255, 255 };
int RGB::Green[3] = { 255, 0, 255 };
int RGB::Blue[3] = { 255, 255, 0 };
int RGB::Magenta[3] = { 0, 255, 0 };
int RGB::Cyan[3] = { 255, 0, 0 };
int RGB::Yellow[3] = { 0, 0, 255 };
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

// Array of colors to cycle through (common anode)
int rainbow[][3] = {
  { 255, 255, 0 },    // Blue
  { 255, 0, 255 },    // Green
  { 0, 255, 255 },    // Red
  { 0, 255, 0 },      // Magenta
  { 255, 0, 0 },      // Cyan
  { 0, 0, 255 },      // Yellow
  { 255, 165, 0 },    // Orange
  { 128, 0, 128 },    // Purple
  { 255, 182, 193 },  // Pink
  { 64, 224, 208 },   // Turquoise
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
  _ButtonState = digitalRead(_Button);

  while (_ButtonState == HIGH) {
    for (int i = 0; i < numColors; ++i) {
      setColor(rainbow[i]);
      delay(WAIT);
      // Check the button state during color cycling
      if (_ButtonState == LOW) {
        return;  // Exit the function to avoid turning off the light
      }
    }
  }
}


void RGB::buttonCycle() {
  _ButtonState = digitalRead(_Button);
  _Time = millis();
  _ButtonTime = millis();
  if (_ButtonState == LOW && _LastButtonState == HIGH) {
    _ColorState++;
    if (_ColorState >= numColors) {
      _ColorState = 0;
    }
    // Set the color based on the updated colorState
    setColor(rainbow[_ColorState]);
    delay(500);
  }

  // Check for OFF
  if (_ButtonState == LOW) {
    if (_ButtonTime - _OldButtonTime >= 5000) {
      _OldButtonTime = _ButtonTime;
      off();
      Serial.println("OFF");
    }

    // Check for ColorCycle
    if (_ButtonTime - _OldButtonTime >= 3000 && _ButtonTime - _OldButtonTime < 5000) {
      _OldButtonTime = _ButtonTime;
      cycleColors();
      Serial.println("cycleColors");
    }

    // Check for SetBrightness
    if (_ButtonTime - _OldButtonTime >= 1000 && _ButtonTime - _OldButtonTime < 3000) {
      _OldButtonTime = _ButtonTime;
      setBrightness();
      Serial.println("setBrightness");
    }
  }
  _LastButtonState = _ButtonState;
}




void RGB::setBrightness() {

  while (digitalRead(_Button) == LOW) {
    if (_Brightness > 0) {
      _Brightness -= 50;
    } else {
      // If brightness is 0, start increasing it again
      _Brightness += 50;
    }
    // Apply the current color with the new brightness
    color(Red[_ColorState], Green[_ColorState], Blue[_ColorState]);
  }
  return;
}

void RGB::debug() {
#ifdef DEBUG
  static unsigned long lastPrintTime = 0;

  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - lastPrintTime;

  if (elapsedTime >= 500) {  // Print every 1 second
    if (_Brightness != _Brightness) {
      Serial.println("_Brightness: " + String(_Brightness));
    }
    if (_ButtonState != _ButtonState) {
      Serial.println("_ButtonState: " + String(_ButtonState));
    }
    if (_LastButtonState != _LastButtonState) {
      Serial.println("_LastButtonState: " + String(_LastButtonState));
    }
    if (_ButtonCounterTime != _ButtonCounterTime) {
      Serial.println("_ButtonCounterTime: " + String(_ButtonCounterTime));
    }
    if (_ColorState != _ColorState) {
      Serial.println("_ColorState: " + String(_ColorState));
    }
    if (_Time != _Time) {
      Serial.println("_Time: " + String(_Time));
    }
    if (_OldButtonTime != _OldButtonTime) {
      Serial.println("_OldButtonTime: " + String(_OldTime));
    }
    if (_ButtonTime != _ButtonTime) {
      Serial.println("_ButtonTime: " + String(_OldTime));
    }

    lastPrintTime = currentTime;
  }
#endif
}
