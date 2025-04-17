#include <MyButton.h>

// Define the GPIO pin for the button
const int GPIO_BUTTON_TO_USE = 14;

MyButton button(GPIO_BUTTON_TO_USE, INPUT_PULLDOWN);

void setup() {
    Serial.begin(9600);
    Serial.println(F("\nExemple d'utilisation de la librairie MyButton"));
}

void loop() {
    int buttonAction = button.checkMyButton();
    switch (buttonAction) {
        case MYBUTTON_SHORT_CLICK:
            Serial.println("Relâché (court)");
            break;
        case MYBUTTON_LONG_CLICK:
            Serial.println("Appui long");
            break;
        case MYBUTTON_DOUBLE_CLICK:
            Serial.println("Double clic");
            break;
        default:
            break;
    }
}