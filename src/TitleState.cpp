#include "GentooEngine.h"
#include "TitleState.h"
#include "StageState.h"

TitleState::TitleState () {
    GameObject* screen = new GameObject(TITLESCREEN_LAYER, TITLESCREEN_LABEL);
    Sprite* sprite = new Sprite(*screen, TITLESCREEN_SPRITE);
    screen->AddComponent(sprite);
    AddObject(screen);
}

void TitleState::Start () {
    Camera::Reset();
    music.Play(TITLESCREEN_MUSIC);
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
    Camera::Reset();
    music.Play(TITLESCREEN_MUSIC);
}