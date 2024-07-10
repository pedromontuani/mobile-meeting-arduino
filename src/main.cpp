#include "controller/button_controller.cpp"
#include "controller/genius_controller.cpp"
#include "controller/led_controller.cpp"
#include "controller/screen_controller.cpp"
#include <Arduino.h>

ScreenController *screen;
GeniusController *genius;

LedController purpleLed(PURPLE_LED_PIN);
LedController blueLed(BLUE_LED_PIN);
LedController yellowLed(YELLOW_LED_PIN);
LedController greenLed(GREEN_LED_PIN);

ButtonController purpleButton(PURPLE_BUTTON_PIN);
ButtonController blueButton(BLUE_BUTTON_PIN);
ButtonController yellowButton(YELLOW_BUTTON_PIN);
ButtonController greenButton(GREEN_BUTTON_PIN);

void printInitialMsg() {
    screen->clear();
    screen->print(F("Press any key"));
    screen->print(F("to start"), 1);
}

void printWinMsg() {
    screen->clear();
    screen->print(F("Congratulations!"), 0);
    screen->print(F("You won!"), 1);
}

void printLoseMsg() {
    screen->clear();
    screen->print(F("You lose!"), 0);
    screen->print(F("Try again!"), 1);
}

void waitForInitialInput() {
    while (!purpleButton.isPressed() && !blueButton.isPressed() &&
           !yellowButton.isPressed() && !greenButton.isPressed()) {
        delay(50);
    }
}

void setup() {
    Serial.begin(115200);

    screen = new ScreenController();
    genius = new GeniusController(purpleLed, blueLed, yellowLed, greenLed,
                                  purpleButton, blueButton, yellowButton,
                                  greenButton, *screen);
}

void loop() {
    genius->idle();

    printInitialMsg();
    waitForInitialInput();

    genius->init();

    while (genius->play()) {
        delay(250);
        genius->nextLevel();
        delay(500);
    }

    if (genius->hasWon()) {
        printWinMsg();
    } else {
        printLoseMsg();
    }

    delay(2000);
}
