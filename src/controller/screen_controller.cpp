#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

class ScreenController {
  private:
    LiquidCrystal_I2C *lcd;

  public:
    ScreenController(byte address = 0x27, byte cols = 16, byte rows = 2) {
        this->lcd = new LiquidCrystal_I2C(address, cols, rows);
        this->lcd->init();
        this->lcd->backlight();
    };

    ~ScreenController() {
        delete this->lcd;
    };

    void clear() {
        this->lcd->clear();
    }

    void print(String message, byte row = 0, byte col = 0) {
        this->lcd->setCursor(col, row);
        this->lcd->print(message);
    }
};