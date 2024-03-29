#include "GentooEngine.h"
#include "OpeningScene.h"
#include "TitleState.h"

OpeningScene::OpeningScene () {
    screenTimer.SetResetTime(OPENING_CONCEAL_TIME);
    currentScreen = 0;
    exchanger = true;
}

void OpeningScene::LoadAssets () {
    std::weak_ptr<GameObject> blankScreen_wptr, engineScreen_wptr;

    GameObject* blankScreen = new GameObject(OPENING_LAYER, OPENING_LABEL);
    Sprite* blankScreenSprite = new Sprite(*blankScreen, OPENING_BLANK_SPRITE);
    blankScreen->AddComponent(blankScreenSprite);
    blankScreen_wptr = AddObject(blankScreen);

    GameObject* engineScreen = new GameObject(OPENING_LAYER, OPENING_LABEL);
    Sprite* engineScreenSprite = new Sprite(*engineScreen, OPENING_ENGINE_SPRITE);
    engineScreen->AddComponent(engineScreenSprite);
    engineScreen_wptr = AddObject(engineScreen);

    renderingArray.insert(
        renderingArray.end(), {blankScreen_wptr, engineScreen_wptr, blankScreen_wptr}
    );

    std::vector<std::string> screens = OPENING_GAME_SPRITES;
    GameObject* newScreen;
    Sprite* newSprite;

    for (int i=0; i < (int)screens.size(); i++) {
        newScreen = new GameObject(OPENING_LAYER, OPENING_LABEL);
        newSprite = new Sprite(*newScreen, screens[i]);
        newScreen->AddComponent(newSprite);
        renderingArray.push_back(AddObject(newScreen));
    }
}

void OpeningScene::Start () {
    Camera::Reset();
}

void OpeningScene::Update (float dt) {
    InputManager& input = InputManager::GetInstance();

    screenTimer.Update(dt);
    if (screenTimer.IsOver() or input.KeyPress(KEY_ESCAPE) or input.KeyPress(KEY_SPACE) or input.MousePress(MOUSE_BUTTON_LEFT)) {
        currentScreen++;
        exchanger = not exchanger;
        screenTimer.SetResetTime(exchanger? OPENING_CONCEAL_TIME : OPENING_DISPLAY_TIME);
        screenTimer.Reset();
    }

    if (currentScreen >= (int)renderingArray.size()) {
        Game::GetInstance().AddState(new TitleState());
        popRequested = true;
    }
}

void OpeningScene::RenderBase () {
    if ((currentScreen < (int)renderingArray.size()) and (not renderingArray[currentScreen].expired()))
        renderingArray[currentScreen].lock()->Render();
}

std::weak_ptr<GameObject> OpeningScene::AddObject (GameObject* object) {
    std::shared_ptr<GameObject> sptrGo(object);
    std::weak_ptr<GameObject> wptrGo(sptrGo);

    objectArray.push_back(sptrGo);
    if (started)
        object->Start();

    return wptrGo;
}