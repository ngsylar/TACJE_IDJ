#include "GentooEngine.h"
#include "TitleState.h"
#include "StageState.h"

TitleState::TitleState () {
    GameObject* screen = new GameObject(TITLESCREEN_SPRITE_LAYER, TITLESCREEN_LABEL);
    Sprite* sprite = new Sprite(*screen, TITLESCREEN_SPRITE_FILE);
    screen->AddComponent(sprite);
    AddObject(screen);
}

void TitleState::LoadAssets () {
    GameObject* startText = new GameObject(TITLESCREEN_TEXT_LAYER, TITLESCREEN_LABEL);
    Text* text = new Text(
        *startText, TITLESCREEN_TEXT_CONTENT,
        TITLESCREEN_TEXT_FONT_FILE, TITLESCREEN_TEXT_FONT_SIZE,
        Text::BLENDED, TEXT_COLOR_YELLOW,
        TITLESCREEN_TEXT_DISPLAY_TIME, TITLESCREEN_TEXT_CONCEAL_TIME
    );
    startText->AddComponent(text);
    startText->box.SetPosition(TITLESCREEN_TEXT_POSITION);
    AddObject(startText);

    GameObject* startTextShadow = new GameObject(TITLESCREEN_TEXT_SHADOW_LAYER, TITLESCREEN_LABEL);
    Text* textShadow = new Text(
        *startTextShadow, TITLESCREEN_TEXT_CONTENT,
        TITLESCREEN_TEXT_FONT_FILE, TITLESCREEN_TEXT_FONT_SIZE,
        Text::BLENDED, TEXT_COLOR_SHADOW,
        TITLESCREEN_TEXT_DISPLAY_TIME, TITLESCREEN_TEXT_CONCEAL_TIME
    );
    startTextShadow->AddComponent(textShadow);
    startTextShadow->box.SetPosition(TITLESCREEN_TEXT_SHADOW_POSITION);
    AddObject(startTextShadow);
}

void TitleState::Start () {
    Camera::Reset();
    // music.Play(TITLESCREEN_MUSIC_FILE);
}

void TitleState::Update (float dt) {
    InputManager& input = InputManager::GetInstance();

    if (input.KeyPress(KEY_ESCAPE)) {
        quitRequested = true;
        return;
    }

    if (input.KeyPress(KEY_SPACE) or input.MousePress(MOUSE_BUTTON_LEFT)) {
        Game::GetInstance().AddState(new StageState());
        popRequested = true;
    }
}

void TitleState::Pause () {
    // music.Stop();
}

void TitleState::Resume () {
    Camera::Reset();
    // music.Play(TITLESCREEN_MUSIC_FILE);
}