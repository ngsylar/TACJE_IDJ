#include "State.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Resources.h"
#include "TileMap.h"
#include "Sound.h"
#include "Face.h"
#include "Vec2.h"

State::State () {
    GameObject* bg = new GameObject();
    CameraFollower* bgCamera = new CameraFollower(*bg);
    Sprite* bgSprite = new Sprite(*bg, SPR_BG);
    bg->AddComponent(bgCamera);
    bg->AddComponent(bgSprite);
    objectArray.emplace_back(bg);

    bg->box = Rect(
        SPR_START_X, SPR_START_Y,
        bgSprite->GetWidth(), bgSprite->GetHeight()
    );

    quitRequested = false;
    music.Open(MUS_BG);
    music.Play(MUS_REPEAT_ON);
}

State::~State () {
    objectArray.clear();
}

void State::LoadAssets () {
    GameObject* gameMap;
    TileSet* gameMapTset;
    TileMap* gameMapTmap;

    gameMap = new GameObject();
    gameMapTset = new TileSet(*gameMap, TSET_GAMEMAP, TDIM_GAMEMAP);
    gameMapTmap = new TileMap(*gameMap, gameMapTset, TMAP_GAMEMAP);
    gameMap->box = Rect(SPR_START_X, SPR_START_Y, TDIM_GAMEMAP);
    gameMap->AddComponent(gameMapTmap);
    objectArray.emplace_back(gameMap);
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
    } else {
        
        Camera::Update(dt);

        if (input.IsKeyDown(KEY_SPACE)) {
            Vec2 objPos = Vec2(200,0).GetRotated(-PI+PI*(rand()%1001)/500.0) + Vec2((float)input.GetMouseX(),(float)input.GetMouseY());
            AddObject(
                (int)objPos.x+Camera::pos.x,
                (int)objPos.y+Camera::pos.y
            );
        }
    
        for (unsigned i=0; i < objectArray.size(); i++) {
            objectArray[i]->Update(dt);
        }

        for (int i=(int)objectArray.size()-1; i >= 0; i--) {
            if (objectArray[i]->IsDead()) {
                objectArray.erase(objectArray.begin()+i);
            }
        }
    }
}

void State::Render () {
    for (unsigned i=0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}

bool State::QuitRequested () {
    return quitRequested;
}

void State::AddObject (int pX, int pY) {
    GameObject* obj = new GameObject();
    Sprite* sprite = new Sprite(*obj, SPR_ENEMY);
    Sound* sound = new Sound(*obj, SND_ENEMY);
    Face* face = new Face(*obj);

    obj->AddComponent(sprite);
    obj->AddComponent(sound);
    obj->AddComponent(face);
    objectArray.emplace_back(obj);

    int pW = sprite->GetWidth();
    int pH = sprite->GetHeight();
    obj->box = Rect(pX-pW/2, pY-pH/2, pW, pH);
}