#pragma once
#include "button_controller.cpp"
#include "constants.h"
#include "led_controller.cpp"
#include "screen_controller.cpp"
#include <Arduino.h>

enum LedColor : byte { PURPLE = 0, BLUE = 1, YELLOW = 2, GREEN = 3 };

class GeniusController {
  private:
    ScreenController *screen;

    LedController *purpleLed;
    LedController *blueLed;
    LedController *yellowLed;
    LedController *greenLed;

    ButtonController *purpleButton;
    ButtonController *blueButton;
    ButtonController *yellowButton;
    ButtonController *greenButton;

    byte *sequence;
    byte currentLevel = 0;

    void generateSequence() {
        for (byte i = 0; i < SEQUENCE_LENGTH; i++) {
            sequence[i] = random(4);
        }
    }

    void clearLevel() {
        this->turnLedsOff();

        this->screen->clear();
        this->currentLevel = 0;
    }

    void displayCurrentLevel() const {
        this->screen->print("Level: " + String(this->currentLevel + 1), 0);
    }

    void displaySequence() const {
        this->turnLedsOff();
        const LedController *led = nullptr;

        for (byte i = 0; i <= this->currentLevel; i++) {
            switch (this->sequence[i]) {
            case LedColor::PURPLE:
                led = this->purpleLed;
                break;
            case LedColor::BLUE:
                led = this->blueLed;
                break;
            case LedColor::YELLOW:
                led = this->yellowLed;
                break;
            case LedColor::GREEN:
                led = this->greenLed;
                break;
            default:
                break;
            }

            if (led != nullptr) {
                led->turnOn();
                delay(500);
                led->turnOff();
                delay(250);
            }
        }
    }

    LedColor getPressedButton() const {
        while (true) {
            if (this->purpleButton->isPressed()) {
                return LedColor::PURPLE;
            } else if (this->blueButton->isPressed()) {
                return LedColor::BLUE;
            } else if (this->yellowButton->isPressed()) {
                return LedColor::YELLOW;
            } else if (this->greenButton->isPressed()) {
                return LedColor::GREEN;
            }
        }
    }

  public:
    GeniusController(LedController &purpleLed, LedController &blueLed,
                     LedController &yellowLed, LedController &greenLed,
                     ButtonController &purpleButton,
                     ButtonController &blueButton,
                     ButtonController &yellowButton,
                     ButtonController &greenButton, ScreenController &screen) {
        this->screen = &screen;

        this->purpleLed = &purpleLed;
        this->blueLed = &blueLed;
        this->yellowLed = &yellowLed;
        this->greenLed = &greenLed;

        this->purpleButton = &purpleButton;
        this->blueButton = &blueButton;
        this->yellowButton = &yellowButton;
        this->greenButton = &greenButton;

        this->sequence = new byte[SEQUENCE_LENGTH];
    }

    ~GeniusController() {
        delete[] this->sequence;
        this->screen = nullptr;

        this->purpleLed = nullptr;
        this->blueLed = nullptr;
        this->yellowLed = nullptr;
        this->greenLed = nullptr;

        this->purpleButton = nullptr;
        this->blueButton = nullptr;
        this->yellowButton = nullptr;
        this->greenButton = nullptr;
    }

    void init() {
        this->clearLevel();
        this->generateSequence();
        this->displayCurrentLevel();
    }

    void turnLedsOff() const {
        this->purpleLed->turnOff();
        this->blueLed->turnOff();
        this->yellowLed->turnOff();
        this->greenLed->turnOff();
    }

    void turnLedsOn() const {
        this->purpleLed->turnOn();
        this->blueLed->turnOn();
        this->yellowLed->turnOn();
        this->greenLed->turnOn();
    }

    bool play() {
        if (this->hasWon()) {
            return false;
        }

        this->displaySequence();

        LedColor pressedButton;
        for (byte i = 0; i <= this->currentLevel; i++) {
            pressedButton = this->getPressedButton();
            if (this->sequence[i] != pressedButton) {
                return false;
            }
            delay(50);
        }

        return true;
    }

    bool hasWon() const {
        return this->currentLevel >= SEQUENCE_LENGTH;
    }

    void nextLevel() {
        this->currentLevel++;
        this->displayCurrentLevel();
    }
};