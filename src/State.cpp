#define INCLUDE_SDL_IMAGE
#include "State.h"

#define STATE_RENDER_X 0
#define STATE_RENDER_Y 0

State::State () {
    this->quitRequested = false;
}

void State::LoadAssets () {
    this->bg.Open("assets/img/ocean.jpg");
}

void State::Update (float dt) {
    if (SDL_QuitRequested()) {
        this->quitRequested = true;
    }
}

void State::Render () {
    this->bg.Render(STATE_RENDER_X, STATE_RENDER_Y);
}

bool State::QuitRequested () {
    return this->quitRequested;
}