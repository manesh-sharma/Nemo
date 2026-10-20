
#include <Arduino.h>

#include "core/Display.h"
#include "screens/EyesScreen.h"

Display display;
EyesScreen eyesScreen(display);

void setup() {
    Serial.begin(115200);
    delay(500);

    Serial.println();
    Serial.println("======================");
    Serial.println("ROMEO STARTING");
    Serial.println("======================");

    display.begin();

    eyesScreen.begin();

    Serial.println("Romeo is awake!");
}

void loop() {
    eyesScreen.update();

    delay(5);
}