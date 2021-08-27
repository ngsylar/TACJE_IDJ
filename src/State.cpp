#include "State.h"

#define STATE_RENDER_X 0
#define STATE_RENDER_Y 0
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
    bg.Render(STATE_RENDER_X, STATE_RENDER_Y);
}

bool State::QuitRequested () {
    return quitRequested;
}