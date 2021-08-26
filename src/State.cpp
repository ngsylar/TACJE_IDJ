#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"

#define STATE_RENDER_X 0
#define STATE_RENDER_Y 0

State::State () {
    this->quitRequested = false;
    this->bg = Sprite("C:\\Games\\TAC\\150126760_T1\\img\\ocean.jpg");
    // this->bg = Sprite("ocean.jpg");
}

void State::LoadAssets () {
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