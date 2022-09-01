#include "GentooEngine.h"
#include "InMemoriam.h"

InMemoriam::InMemoriam () {
    screenTimer.SetResetTime(IM_LAA_TIME);
}

void InMemoriam::LoadAssets () {
    GameObject* screen = new GameObject(IM_LAA_LAYER, IM_LAA_LABEL);
    Sprite* screenSprite = new Sprite(*screen, IM_LAA_SPRITE);
    screen->AddComponent(screenSprite);
    renderingArray.push_back(AddObject(screen));
}

void InMemoriam::Start () {
    Camera::Reset();

    Music music(IM_LAA_MUSIC);
    music.Play();
}

void InMemoriam::Update (float dt) {
    InputManager& input = InputManager::GetInstance();

    screenTimer.Update(dt);
    if (screenTimer.IsOver() or input.KeyPress(KEY_ESCAPE) or input.KeyPress(KEY_SPACE) or input.MousePress(MOUSE_BUTTON_LEFT)) {
        quitRequested = true;
    }
}

void InMemoriam::RenderBase () {
    renderingArray.front().lock()->Render();
}

std::weak_ptr<GameObject> InMemoriam::AddObject (GameObject* object) {
    std::shared_ptr<GameObject> sptrGo(object);
    std::weak_ptr<GameObject> wptrGo(sptrGo);

    objectArray.push_back(sptrGo);
    if (started)
        object->Start();

    return wptrGo;
}