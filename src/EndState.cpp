#include "GentooEngine.h"
#include "EndState.h"
#include "TitleState.h"
#include "GameData.h"

EndState::EndState () {
    GameObject* screen = new GameObject(GAMEOVER_LAYER, GAMEOVER_LABEL);
    Sprite* sprite = new Sprite(
        *screen, GameData::PlayerVictory()? GAMEOVER_VICTORY_SPRITE : GAMEOVER_DEFEAT_SPRITE
    );
    screen->AddComponent(sprite);
    AddObject(screen);
}

void EndState::LoadAssets () {
    music.Open(GameData::PlayerVictory()? GAMEOVER_VICTORY_MUSIC : GAMEOVER_DEFEAT_MUSIC);
}

void EndState::Start () {
    Camera::Reset();
    music.Play();
}

void EndState::Update (float dt) {
    InputManager& input = InputManager::GetInstance();

    if (input.KeyPress(KEY_ESCAPE) or (input.KeyPress(KEY_SPACE)) or input.MousePress(MOUSE_BUTTON_LEFT)) {
        Game::GetInstance().AddState(new TitleState());
        popRequested = true;
        return;
    }
}