#include "MyButton.h"

MyButton::MyButton(int gpioNumber, int typebutton) {
    buttonGPIO = gpioNumber;
    buttonDebounceDelay = DEFAULT_DEBOUNCE_DELAY;
    buttonLongPressDuration = DEFAULT_LONG_PRESS_DURATION;
    buttonDoubleClickMaxDelay = DEFAULT_DOUBLE_CLICK_MAX_DELAY;
    isPressed = false;
    lastRawState = false;
    lastDebounceTime = 0;
    pressStart = 0;
    lastReleaseTime = 0;
    waitingSecondClick = false;
    pendingSingleClick = false;

    // Initialize the pin
    pinMode(buttonGPIO, typebutton);
}

void MyButton::setButtonDebounceDelay(int delay) {
    buttonDebounceDelay = delay;
}

void MyButton::setButtonLongPressDuration(int duration) {
    buttonLongPressDuration = duration;
}

void MyButton::setButtonDoubleClickMaxDelay(int maxDelay) {
    buttonDoubleClickMaxDelay = maxDelay;
}

int MyButton::checkMyButton() {
    bool rawState = digitalRead(buttonGPIO);
    unsigned long now = millis();

    // Debounce
    if (rawState != lastRawState) {
        lastDebounceTime = now;
        lastRawState = rawState;
    }

    if ((now - lastDebounceTime) > buttonDebounceDelay) {
        if (rawState == HIGH && !isPressed) {
            isPressed = true;
            pressStart = now;
        }
        if (rawState == LOW && isPressed) {
            isPressed = false;
            unsigned long pressDuration = now - pressStart;
            if (pressDuration >= buttonLongPressDuration) {
                waitingSecondClick = false;
                pendingSingleClick = false;
                return MYBUTTON_LONG_CLICK; // Long press
            }
            if (waitingSecondClick) {
                waitingSecondClick = false;
                pendingSingleClick = false;
                return MYBUTTON_DOUBLE_CLICK; // Double click
            } else {
                waitingSecondClick = true;
                pendingSingleClick = true;
                lastReleaseTime = now;
            }
        }
    }

    // If waiting for a second click but the timeout has passed
    if (pendingSingleClick && (now - lastReleaseTime > buttonDoubleClickMaxDelay)) {
        pendingSingleClick = false;
        waitingSecondClick = false;
        return MYBUTTON_SHORT_CLICK; // Single click confirmed
    }

    return MYBUTTON_NO_CLICK;
}