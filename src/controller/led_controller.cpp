#pragma once
#include <Arduino.h>

class LedController {
  private:
    byte pin;

  public:
    explicit LedController(byte pin) : pin(pin) {
        pinMode(pin, OUTPUT);
    }

    void turnOn() const {
        digitalWrite(pin, HIGH);
    }

    void turnOff() const {
        digitalWrite(pin, LOW);
    }
};