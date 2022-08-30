#include "GentooEngine.h"
#include "PauseScene.h"

PauseScene::PauseScene (StageState* gameplayScene) {
    this->gameplayScene = gameplayScene;

    pauseScreen = new GameObject(PAUSESCREEN_LAYER, PAUSESCREEN_LABEL);
    Sprite* sprite = new Sprite(*pauseScreen, PAUSESCREEN_SPRITE);
    pauseScreen->AddComponent(sprite);
}

PauseScene::~PauseScene () {
    delete pauseScreen;
}

void PauseScene::Start () {
    Sprite* screen = (Sprite*)pauseScreen->GetComponent("Sprite");
    if (screen != nullptr)
        screen->Render(PAUSESCREEN_POSITION);
}

void PauseScene::Update (float dt) {
    InputManager& input = InputManager::GetInstance();

    if (input.KeyPress(KEY_ESCAPE)) {
        popRequested = true;
        gameplayScene->popRequested = true;;
        return;
    }

    if (input.KeyPress(KEY_SPACE) or input.MousePress(MOUSE_BUTTON_LEFT)) {
        popRequested = true;
    }
}