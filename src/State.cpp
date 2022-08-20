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
    for (int i=0; i < (int)objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    started = true;
}

// nota: modificar TileSet para ser usado por mais de um GameObject
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

    GameObject* alien = new GameObject(ALIEN_LAYER, ALIEN_LABEL);
    alien->AddComponent(new Alien(*alien, ALIEN_MINIONS_AMOUNT));
    alien->box.SetPosition(ALIEN_START_POSITION);
    AddObject(alien);

    GameObject* penguin = new GameObject(PENGUINB_LAYER, PENGUINB_LABEL);
    penguin->AddComponent(new PenguinBody(*penguin));
    penguin->box.SetPosition(PENGUINB_START_POSITION);
    AddObject(penguin);
    Camera::Follow(penguin);
}

void State::ClearResources () {
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
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

    for (int i=0; i < (int)objectArray.size()-1; i++)
        for (int j=i+1; j < (int)objectArray.size(); j++) {
            Collider* colliderA = (Collider*)objectArray[i]->GetComponent("Collider");
            Collider* colliderB = (Collider*)objectArray[j]->GetComponent("Collider");
            if (not (colliderA and colliderB))
                continue;
            
            if (Collision::IsColliding(
                colliderA->box, colliderB->box,
                Deg2Rad(objectArray[i]->angleDeg),
                Deg2Rad(objectArray[j]->angleDeg)
            )) {
                objectArray[i]->NotifyCollision(*objectArray[j]);
                objectArray[j]->NotifyCollision(*objectArray[i]);
            }
        }

    for (int i=(int)objectArray.size()-1; i >= 0; i--) {
        if (objectArray[i]->IsDead())
            objectArray.erase(objectArray.begin()+i);
    }
}

void State::UpdateLayerRange (int layer) {
    if (layer < (int)layerRange.x)
        layerRange.x = layer;
    else if (layer > (int)layerRange.y)
        layerRange.y = layer;
    scheduleLayerSort = true;
}

void State::SortRenderList () {
    std::sort(objectArray.begin(), objectArray.end(), GameObject::CompareLayers);
    scheduleLayerSort = false;
}

void State::Render () {
    if (scheduleLayerSort)
        SortRenderList();
    for (int i=0; i < (int)objectArray.size(); i++)
        objectArray[i]->Render();
}

bool State::QuitRequested () {
    return quitRequested;
}

std::weak_ptr<GameObject> State::AddObject (GameObject* go) {
    std::shared_ptr<GameObject> sptrGo(go);
    std::weak_ptr<GameObject> wptrGo(sptrGo);

    objectArray.push_back(sptrGo);
    if (started) {
        go->Start();
    }
    UpdateLayerRange(go->layer);
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