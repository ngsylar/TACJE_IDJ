#include "Timer.h"

Timer::Timer (float resetTime, float startTime) {
    this->resetTime = resetTime;
    currentTime = startTime;
}

void Timer::SetResetTime (float time) {
    resetTime = time;
}

void Timer::Update (float dt) {
    currentTime += dt;
}

void Timer::Reset () {
    currentTime = 0.0f;
}

float Timer::Get () {
    return currentTime;
}

bool Timer::IsOver () {
    return (currentTime >= resetTime);
}

bool Timer::IsOver (float dt) {
    if (resetTime == 0.0f)
        return true;
    
    currentTime += dt;
    return (currentTime >= resetTime);
}

bool Timer::HasReset () {
    return (resetTime > 0.0f);
}

bool Timer::HasResetAndIsOver (float dt) {
    if (resetTime > 0.0f) {
        currentTime += dt;
        return (currentTime >= resetTime);
    }
    return false;
}