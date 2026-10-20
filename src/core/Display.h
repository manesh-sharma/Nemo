#pragma once

#include <U8g2lib.h>
#include <RobotEye.h>

class Display {
public:
    Display();

    void begin();
    void update();

    RobotEye& eyes();

    // Give screens access to the OLED drawing functions.
    U8G2_SH1106_128X64_NONAME_F_HW_I2C& screen();

private:
    U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;
    RobotEye robotEye;
};
