#pragma once

// ------------------------------------------------------------
// Sleep
// ------------------------------------------------------------

// Time Romeo stays awake before randomly going to sleep.

// Sleep
constexpr unsigned long SLEEP_MIN_INTERVAL = 300000;  // 5 min
constexpr unsigned long SLEEP_MAX_INTERVAL = 900000;  // 15 min

constexpr unsigned long SLEEP_DURATION_MIN = 120000;  // 2 min
constexpr unsigned long SLEEP_DURATION_MAX = 300000;  // 5 min

// ------------------------------------------------------------
// Personality
// ------------------------------------------------------------

constexpr unsigned long MOOD_MIN_INTERVAL = 8000;   // 8 sec
constexpr unsigned long MOOD_MAX_INTERVAL = 16000;  // 16 sec


// ------------------------------------------------------------
// Charging
// ------------------------------------------------------------

constexpr unsigned long CHARGE_REACTION_INTERVAL = 1800;


