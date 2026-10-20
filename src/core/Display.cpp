
#include <Wire.h>
#include "Display.h"

// ESP32-C3 SuperMini OLED wiring
constexpr uint8_t OLED_SDA = 6;
constexpr uint8_t OLED_SCL = 7;

Display::Display()
    : u8g2(
          U8G2_R0,
          U8X8_PIN_NONE
      ),
      robotEye(&u8g2) {
}

void Display::begin() {
    // Initialize I2C using the new GPIO pins.
    Wire.begin(OLED_SDA, OLED_SCL);
    Wire.setClock(100000);

    // Initialize the OLED and RobotEye library.
    u8g2.begin();
    robotEye.begin();
}

void Display::update() {
    robotEye.update();
}

RobotEye& Display::eyes() {
    return robotEye;
}

U8G2_SH1106_128X64_NONAME_F_HW_I2C& Display::screen() {
    return u8g2;
}
