#include "Timer.h"

Timer::Timer () {
    time = 0;
}

void Timer::Update (float dt) {
    time += dt;
}

bool Timer::IsReady (float cooldown) {
    return (time >= cooldown);
}

void Timer::Restart () {
    time = 0;
}

float Timer::Get () {
    return time;
}