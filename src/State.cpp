#include "State.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Resources.h"
#include "Collision.h"
#include "Collider.h"
#include "TileMap.h"
#include "Sound.h"
#include "Vec2.h"
#include "Alien.h"
#include "PenguinBody.h"

State::State () {
    GameObject* bg = new GameObject(BG_LAYER, BG_LABEL);
    CameraFollower* bgCamera = new CameraFollower(*bg);
    Sprite* bgSprite = new Sprite(*bg, BG_SPRITE);
    bg->AddComponent(bgCamera);
    bg->AddComponent(bgSprite);
    AddObject(bg);

    music.Open(BG_MUSIC);
    music.Play(MUSIC_REPEAT_ON);

    quitRequested = false;
    started = false;
}

State::~State () {
    objectArray.clear();
}

void State::Start () {
    LoadAssets();
    collisionTolerance = Timer(0.25f);
    
    for (int i=0; i < (int)objectArray.size(); i++)
        objectArray[i]->Start();
    started = true;
}

// editar: modificar TileSet para ser usado por mais de um GameObject
void State::LoadAssets () {
    GameObject* gameMap0 = new GameObject(GAMEMAP_TILEMAP0_LAYER, GAMEMAP_LABEL);
    TileSet* gameMapTset0 = new TileSet(*gameMap0, GAMEMAP_TILESET, GAMEMAP_TILESET_TILE_SIZE);
    TileMap* gameMapTmap0 = new TileMap(*gameMap0, gameMapTset0, GAMEMAP_TILEMAP0);
    gameMap0->box = Rect(GAMEMAP_START_POSITION, GAMEMAP_TILESET_TILE_SIZE);
    gameMap0->AddComponent(gameMapTmap0);
    AddObject(gameMap0);

    GameObject* gameMap1 = new GameObject(GAMEMAP_TILEMAP1_LAYER, GAMEMAP_LABEL);
    TileSet* gameMapTset1 = new TileSet(*gameMap1, GAMEMAP_TILESET, GAMEMAP_TILESET_TILE_SIZE);
    TileMap* gameMapTmap1 = new TileMap(*gameMap1, gameMapTset1, GAMEMAP_TILEMAP1, 0.2f);
    gameMap1->box = Rect(GAMEMAP_START_POSITION, GAMEMAP_TILESET_TILE_SIZE);
    gameMap1->AddComponent(gameMapTmap1);
    AddObject(gameMap1);
    
    GameObject* alien0 = new GameObject(ALIEN_LAYER, ALIEN_LABEL);
    alien0->AddComponent(new Alien(*alien0, ALIEN_MINION_COUNT));
    alien0->box.SetPosition(ALIEN0_START_POSITION);
    AddObject(alien0);

    GameObject* alien1 = new GameObject(ALIEN_LAYER, ALIEN_LABEL);
    alien1->AddComponent(new Alien(*alien1, ALIEN_MINION_COUNT));
    alien1->box.SetPosition(ALIEN1_START_POSITION);
    AddObject(alien1);

    GameObject* alien2 = new GameObject(ALIEN_LAYER, ALIEN_LABEL);
    alien2->AddComponent(new Alien(*alien2, ALIEN_MINION_COUNT));
    alien2->box.SetPosition(ALIEN2_START_POSITION);
    AddObject(alien2);

    GameObject* penguin = new GameObject(PENGUINB_LAYER, PENGUINB_LABEL);
    penguin->AddComponent(new PenguinBody(*penguin));
    penguin->box.SetPosition(PENGUINB_START_POSITION);
    AddObject(penguin);
    Camera::Follow(penguin);
}

void State::Update (float dt) {
    InputManager& input = InputManager::GetInstance();

    if (input.QuitRequested() or input.IsKeyDown(KEY_ESCAPE)) {
        quitRequested = true;
        return;
    }
    
    Camera::Update(dt);
    for (int i=0; i < (int)objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    if (collisionTolerance.IsOver()) {
        DetectCollisions();
    } else {
        collisionTolerance.Update(dt);
    }
    
    // // idj's original object deletion
    // for (int i=(int)objectArray.size()-1; i >= 0; i--) {
    //     objectArray.erase(objectArray.begin()+i);
    // }
    
    // sylar's extra layer rendering
    for (int i=(int)renderingArray.size()-1; i >= 0; i--) {
        if (renderingArray[i].lock()->IsDead() and renderingArray[i].lock()->index.Exists())
            RemoveObject(renderingArray[i].lock()->index.Get(), i);
    }
}

void State::Render () {
    // // idj's original object rendering
    // for (int i=0; i < (int)objectArray.size(); i++) {
    //     objectArray[i]->Render();
    // }

    // sylar's extra layer rendering
    if (scheduleLayerSort) {
        std::sort(renderingArray.begin(), renderingArray.end(), GameObject::CompareLayers);
        scheduleLayerSort = false;
    }
    // sylar's extra layer rendering
    for (int i=0; i < (int)renderingArray.size(); i++) {
        renderingArray[i].lock()->Render();
    }
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

std::weak_ptr<GameObject> State::AddObject (GameObject* go) {
    std::shared_ptr<GameObject> sptrGo(go);
    std::weak_ptr<GameObject> wptrGo(sptrGo);

    objectArray.push_back(sptrGo);
    go->index.Set(objectArray.size()-1);    // sylar's extra layer rendering
    if (started)
        go->Start();

    // sylar's extra layer rendering
    renderingArray.push_back(wptrGo);
    scheduleLayerSort = true;
    
    return wptrGo;
}

std::weak_ptr<GameObject> State::GetObjectPtr (GameObject* go) {
    std::weak_ptr<GameObject> wptrGo;

    for (int i=0; i < (int)objectArray.size(); i++) {
        if (objectArray[i].get() == go)
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
    renderingArray.erase(renderingArray.begin()+renderingId);
    objectArray.erase(objectArray.begin()+objectId);

    for (int i=objectId; i < (int)objectArray.size(); i++)
        objectArray[i]->index.Decrease();
}

bool State::QuitRequested () {
    return quitRequested;
}

void State::ClearResources () {
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}