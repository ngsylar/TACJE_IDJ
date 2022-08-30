#include "GentooEngine.h"
#include "OpeningScene.h"
#include "TitleState.h"

OpeningScene::OpeningScene () {
    GameObject* engineScreen = new GameObject(OPENING_LAYER, OPENING_LABEL);
    Sprite* engineSprite = new Sprite(*engineScreen, OPENING_ENGINE_SPRITE);
    engineScreen->AddComponent(engineSprite);
    AddObject(engineScreen);

    GameObject* productScreen = new GameObject(OPENING_LAYER, OPENING_LABEL);
    Sprite* productSprite = new Sprite(*productScreen, OPENING_PRODUCT_SPRITE);
    productScreen->AddComponent(productSprite);
    AddObject(productScreen);
}

void OpeningScene::Start () {
    Camera::Reset();
    screenTimer.SetResetTime(OPENING_RESET_TIME);
}

void OpeningScene::Update (float dt) {
    InputManager& input = InputManager::GetInstance();

    if (objectArray.empty()) {
        popRequested = true;
        Game::GetInstance().AddState(new TitleState());
        return;
    }

    screenTimer.Update(dt);
    if (screenTimer.IsOver() or input.KeyPress(KEY_ESCAPE) or input.KeyPress(KEY_SPACE)) {
        objectArray.erase(objectArray.begin());
        screenTimer.Reset();
    }
}

void OpeningScene::RenderBase () {
    if (not objectArray.empty())
        objectArray.front()->Render();
}