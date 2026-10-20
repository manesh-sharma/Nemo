#pragma once

#include "../core/Display.h"
#include "../config/Settings.h"
#include "Screen.h"

class EyesScreen : public Screen {
public:
    explicit EyesScreen(Display& display);

    void begin() override;
    void update() override;

    void notifyActivity();

    void setCharging(bool charging);


    bool isSleeping() const;

    void sleep();
    void wake();

private:
    Display& display;
    RobotEye& eye;

    // Personality timing
    unsigned long nextMoodChange;

    // Sleep timing
    unsigned long nextSleepTime;
    unsigned long sleepStartedAt;
    unsigned long sleepDuration;

    // Charging reaction
    unsigned long lastChargeReaction;

    // Wink state
    unsigned long winkStartedAt;
    bool winkActive;

    static constexpr unsigned long WINK_DURATION = 700;

    // State
    

    bool sleeping;
    bool charging;

    // Personality
    void updatePersonality();
    void chooseRandomMood();
    void scheduleNextMood();

    unsigned long randomMoodInterval() const;

    // Sleep
    void updateSleep();
    void scheduleNextSleep();

    unsigned long randomSleepInterval() const;
    unsigned long randomSleepDuration() const;

    // Charging
    void updateCharging();
};