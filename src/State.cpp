#include "State.h"

#define REPEAT_ST_ON -1

State::State () {
    quitRequested = false;
    music.Open("assets/audio/stageState.ogg");
    music.Play(REPEAT_ST_ON);
}

void State::LoadAssets () {
    bg.Open("assets/img/ocean.jpg");
}

void State::Update (float dt) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::Render () {
    bg.Render();
}

bool State::QuitRequested () {
    return quitRequested;
}