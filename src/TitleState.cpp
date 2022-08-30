#include "GentooEngine.h"
#include "TitleState.h"
#include "StageState.h"

TitleState::TitleState () {
    screen = new GameObject(TITLESCREEN_LAYER, TITLESCREEN_LABEL);
    Sprite* bgSprite = new Sprite(*screen, TITLESCREEN_SPRITE);
    screen->AddComponent(bgSprite);
}

TitleState::~TitleState () {
    delete screen;
}

void TitleState::Start () {
    screen->Render();
    music.Open(TITLESCREEN_MUSIC);
    music.Play(MUSIC_REPEAT_ON);
}

void TitleState::Update (float dt) {
    InputManager& input = InputManager::GetInstance();

    if (input.KeyPress(KEY_ESCAPE)) {
        quitRequested = true;
        return;
    }

    if (input.KeyPress(KEY_SPACE) or input.MousePress(MOUSE_BUTTON_LEFT)) {
        Game::GetInstance().AddState(new StageState());
    }
}

void TitleState::Pause () {
    music.Stop();
}

void TitleState::Resume () {
    screen->Render();
    music.Play(TITLESCREEN_MUSIC);
}