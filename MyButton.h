#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <Arduino.h>

// Constants for button states
#define MYBUTTON_NO_CLICK 0
#define MYBUTTON_SHORT_CLICK 2
#define MYBUTTON_LONG_CLICK 3
#define MYBUTTON_DOUBLE_CLICK 4

// Default timing values (in milliseconds)
#define DEFAULT_DEBOUNCE_DELAY 50
#define DEFAULT_LONG_PRESS_DURATION 1000
#define DEFAULT_DOUBLE_CLICK_MAX_DELAY 400

class MyButton {
private:
    // Class members as per the diagram
    int buttonGPIO;
    int buttonDebounceDelay;
    int buttonLongPressDuration;
    int buttonDoubleClickMaxDelay;
    bool isPressed;
    bool lastRawState;
    unsigned long lastDebounceTime;
    unsigned long pressStart;
    unsigned long lastReleaseTime;
    bool waitingSecondClick;
    bool pendingSingleClick;

public:
    // Constructor
    MyButton(int gpioNumber, int typebutton = INPUT_PULLDOWN);

    // Setter methods
    void setButtonDebounceDelay(int delay);
    void setButtonLongPressDuration(int duration);
    void setButtonDoubleClickMaxDelay(int maxDelay);

    // Main method to check button state
    int checkMyButton();
};

#endif