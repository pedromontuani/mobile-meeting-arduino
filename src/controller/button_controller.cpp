#pragma once
#include <Arduino.h>

class ButtonController {
  private:
    byte pin;

  public:
    explicit ButtonController(byte pin) : pin(pin) {
        pinMode(pin, INPUT_PULLUP);
    }

    bool isPressed() const {
        return digitalRead(pin) == LOW;
    }
};