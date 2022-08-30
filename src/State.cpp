#include "GentooEngine.h"

State::State () {
    debugMode = false;
    started = false;
    popRequested = false;
    quitRequested = false;
}

State::~State () {
    objectArray.clear();
}

void State::StartBase () {
    LoadAssets();
    Start();
    
    for (int i=0; i < (int)objectArray.size(); i++)
        objectArray[i]->Start();
    started = true;
}

void State::UpdateBase (float dt) {
    InputManager& input = InputManager::GetInstance();
    
    if (input.QuitRequested()) {
        quitRequested = true;
        return;
    }

    // DEBUG
    if (input.IsKeyDown(KEY_CTRL_LEFT) and input.IsKeyDown(KEY_SHIFT_LEFT) and input.KeyPress(KEY_P)) {
        debugMode = not debugMode;
    }

    Camera::Update(dt);
    Update(dt);

    for (int i=0; i < (int)objectArray.size(); i++)
        objectArray[i]->Update(dt);

    DetectCollisions();

    // idj's original object deletion
    for (int i=(int)objectArray.size()-1; i >= 0; i--) {
        if (objectArray[i]->IsDead())
            objectArray.erase(objectArray.begin()+i);
    }
    
    // // sylar's extra layer rendering
    // for (int i=(int)renderingArray.size()-1; i >= 0; i--) {
    //     if (renderingArray[i].lock()->IsDead() and renderingArray[i].lock()->index.Exists())
    //         RemoveObject(renderingArray[i].lock()->index.Get(), i);
    // }
}

void State::RenderBase () {
    Render();

    // idj's original object rendering
    for (int i=0; i < (int)objectArray.size(); i++) {
        objectArray[i]->Render();
    }

    // // sylar's extra layer rendering
    // if (scheduleLayerSort) {
    //     std::sort(renderingArray.begin(), renderingArray.end(), GameObject::CompareLayers);
    //     scheduleLayerSort = false;
    // }
    // // sylar's extra layer rendering
    // for (int i=0; i < (int)renderingArray.size(); i++) {
    //     renderingArray[i].lock()->Render();
    // }
}

void State::LoadAssets () {}

void State::Start () {}

void State::Update (float dt) {}

void State::Render () {}

void State::Pause () {}

void State::Resume () {}

std::weak_ptr<GameObject> State::AddObject (GameObject* object) {
    std::shared_ptr<GameObject> sptrGo(object);
    std::weak_ptr<GameObject> wptrGo(sptrGo);

    objectArray.push_back(sptrGo);
    // object->index.Set(objectArray.size()-1);    // sylar's extra layer rendering
    if (started)
        object->Start();

    // // sylar's extra layer rendering
    // renderingArray.push_back(wptrGo);
    // scheduleLayerSort = true;
    
    return wptrGo;
}

std::weak_ptr<GameObject> State::GetObjectPtr (GameObject* object) {
    std::weak_ptr<GameObject> wptrGo;

    for (int i=0; i < (int)objectArray.size(); i++) {
        if (objectArray[i].get() == object)
            wptrGo = objectArray[i];
    }
    return wptrGo;
}

std::weak_ptr<GameObject> State::GetObjectPtr (std::string label) {
    std::weak_ptr<GameObject> wptrGo;

    for (int i=0; i < (int)objectArray.size(); i++) {
        if (objectArray[i]->label == label)
            wptrGo = objectArray[i];
    }
    return wptrGo;
}

// sylar's extra layer rendering
void State::RemoveObject (int objectId, int renderingId) {
    // renderingArray.erase(renderingArray.begin()+renderingId);
    objectArray.erase(objectArray.begin()+objectId);

    // for (int i=objectId; i < (int)objectArray.size(); i++)
    //     objectArray[i]->index.Decrease();
}

void State::DetectCollisions () {
    bool thereIsCollision;

    for (int i=0; i < (int)objectArray.size()-1; i++)
        for (int j=i+1; j < (int)objectArray.size(); j++) {
            Collider* colliderA = (Collider*)objectArray[i]->GetComponent("Collider");
            Collider* colliderB = (Collider*)objectArray[j]->GetComponent("Collider");
            if (not (colliderA and colliderB))
                continue;

            thereIsCollision = Collision::IsColliding(
                colliderA->box, colliderB->box,
                Deg2Rad(objectArray[i]->angleDeg),
                Deg2Rad(objectArray[j]->angleDeg)
            );
            if (thereIsCollision) {
                objectArray[i]->NotifyCollision(*objectArray[j]);
                objectArray[j]->NotifyCollision(*objectArray[i]);
            }
        }
}

bool State::Debugging () {
    return debugMode;
}

// bool State::Started () {
//     return started;
// }

// bool State::Paused () {
//     return paused;
// }

bool State::PopRequested () {
    return popRequested;
}

bool State::QuitRequested () {
    return quitRequested;
}