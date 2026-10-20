#include "EyesScreen.h"

EyesScreen::EyesScreen(Display& display)
    : display(display),
      eye(display.eyes()),
      nextMoodChange(0),
      nextSleepTime(0),
      sleepStartedAt(0),
      sleepDuration(0),
      lastChargeReaction(0),
      winkStartedAt(0),

      sleeping(false),
      charging(false),
      winkActive(false) {
}


// ============================================================
// Begin
// ============================================================

void EyesScreen::begin() {
    randomSeed(micros());

    eye.setExpression(
        RobotEye::EXPR_NORMAL
    );

    scheduleNextMood();
    scheduleNextSleep();
}


// ============================================================
// Main update
// ============================================================

void EyesScreen::update() {
    // Keep RobotEye animation running.
    display.update();

    // Sleep has priority over everything else.
    updateSleep();

    if (sleeping) {
        return;
    }

    // Charging has priority over normal personality.
    if (charging) {
        updateCharging();
        return;
    }

    updatePersonality();
}


// ============================================================
// Normal personality
// ============================================================

void EyesScreen::updatePersonality() {
    // Handle an active wink first.
    if (winkActive) {
        if (
            millis() - winkStartedAt >=
            WINK_DURATION
        ) {
            winkActive = false;

            eye.setExpression(
                RobotEye::EXPR_NORMAL
            );

            scheduleNextMood();
        }

        return;
    }

    // Low battery makes Romeo sleepy.
    

    // Time for a new random expression.
    if (millis() >= nextMoodChange) {
        chooseRandomMood();
        scheduleNextMood();
    }
}


// ============================================================
// Random personality
// ============================================================

void EyesScreen::chooseRandomMood() {
    /*
     * Romeo's normal personality pool.
     *
     * Sleep, charging, low battery and wake reactions
     * are handled separately.
     */

    uint8_t mood = random(0, 19);

    switch (mood) {
        case 0:
            eye.setExpression(
                RobotEye::EXPR_NORMAL
            );
            break;

        case 1:
            eye.setExpression(
                RobotEye::EXPR_ALERT
            );
            break;

        case 2:
            eye.setExpression(
                RobotEye::EXPR_BORED
            );
            break;

        case 3:
            eye.setExpression(
                RobotEye::EXPR_DISORIENTED
            );
            break;

        case 4:
            eye.setExpression(
                RobotEye::EXPR_EXCITED
            );
            break;

        case 5:
            eye.setExpression(
                RobotEye::EXPR_FOCUSED
            );
            break;

        case 6:
            eye.setExpression(
                RobotEye::EXPR_HAPPY
            );
            break;

        case 7:
            eye.setExpression(
                RobotEye::EXPR_LOOK_DOWN
            );
            break;

        case 8:
            eye.setExpression(
                RobotEye::EXPR_LOOK_LEFT
            );
            break;

        case 9:
            eye.setExpression(
                RobotEye::EXPR_LOOK_RIGHT
            );
            break;

        case 10:
            eye.setExpression(
                RobotEye::EXPR_LOOK_UP
            );
            break;

        case 11:
            eye.setExpression(
                RobotEye::EXPR_SAD
            );
            break;

        case 12:
            eye.setExpression(
                RobotEye::EXPR_ANGRY
            );
            break;

        case 13:
            eye.setExpression(
                RobotEye::EXPR_FURIOUS
            );
            break;

        case 14:
            eye.setExpression(
                RobotEye::EXPR_SCARED
            );
            break;

        case 15:
            eye.setExpression(
                RobotEye::EXPR_WORRIED
            );
            break;

        case 16:
            eye.setExpression(
                RobotEye::EXPR_WINK_LEFT
            );

            winkActive = true;
            winkStartedAt = millis();
            break;

        case 17:
            eye.setExpression(
                RobotEye::EXPR_WINK_RIGHT
            );

            winkActive = true;
            winkStartedAt = millis();
            break;
        
        case 18:
            eye.setExpression(
                RobotEye::EXPR_SLEEPY
            );
            break;
    }
}


// ============================================================
// Mood timing
// ============================================================

void EyesScreen::scheduleNextMood() {
    nextMoodChange =
        millis() + randomMoodInterval();
}


unsigned long EyesScreen::randomMoodInterval() const {
    return random(
        MOOD_MIN_INTERVAL,
        MOOD_MAX_INTERVAL
    );
}


// ============================================================
// Sleep system
// ============================================================

void EyesScreen::updateSleep() {
    if (sleeping) {
        /*
         * Romeo is already sleeping.
         *
         * Each sleep session has its own randomly
         * selected duration.
         */
        if (
            millis() - sleepStartedAt >=
            sleepDuration
        ) {
            wake();
        }

        return;
    }

    // Romeo is awake. Check whether it is time to sleep.
    if (millis() >= nextSleepTime) {
        sleep();
    }
}


void EyesScreen::scheduleNextSleep() {
    nextSleepTime =
        millis() + randomSleepInterval();
}


unsigned long EyesScreen::randomSleepInterval() const {
    return random(
        SLEEP_MIN_INTERVAL,
        SLEEP_MAX_INTERVAL
    );
}


unsigned long EyesScreen::randomSleepDuration() const {
    return random(
        SLEEP_DURATION_MIN,
        SLEEP_DURATION_MAX
    );
}


// ============================================================
// Sleep
// ============================================================

void EyesScreen::sleep() {
    if (sleeping) {
        return;
    }

    sleeping = true;

    sleepStartedAt = millis();

    // Pick a new random duration for this sleep session.
    sleepDuration = randomSleepDuration();

    eye.setExpression(
        RobotEye::EXPR_BLINK
    );
}


// ============================================================
// Wake
// ============================================================

void EyesScreen::wake() {
    if (!sleeping) {
        return;
    }

    sleeping = false;

    eye.setExpression(
        RobotEye::EXPR_SURPRISED,
        true
    );

    /*
     * Give Romeo a short period of normal behavior
     * after waking instead of immediately changing mood.
     */
    nextMoodChange = millis() + 3000;

    // Schedule a completely new random awake period.
    scheduleNextSleep();
}


// ============================================================
// Activity
// ============================================================

void EyesScreen::notifyActivity() {
    if (sleeping) {
        wake();
    }
}


// ============================================================
// Charging
// ============================================================

void EyesScreen::setCharging(bool value) {
    charging = value;

    if (charging) {
        lastChargeReaction = 0;
    }
}


void EyesScreen::updateCharging() {
    if (
        millis() - lastChargeReaction <
        CHARGE_REACTION_INTERVAL
    ) {
        return;
    }

    lastChargeReaction = millis();

    static bool excited = false;

    excited = !excited;

    if (excited) {
        eye.setExpression(
            RobotEye::EXPR_EXCITED
        );
    } else {
        eye.setExpression(
            RobotEye::EXPR_HAPPY
        );
    }
}




// ============================================================
// State
// ============================================================

bool EyesScreen::isSleeping() const {
    return sleeping;
}