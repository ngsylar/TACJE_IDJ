#include "GentooEngine.h"
#include "StageState.h"
#include "PauseScene.h"
#include "Alien.h"
#include "PenguinBody.h"

StageState::StageState () {
    GameObject* bg = new GameObject(BACKGROUND_LAYER, BACKGROUND_LABEL);
    CameraFollower* bgCamera = new CameraFollower(*bg);
    Sprite* bgSprite = new Sprite(*bg, BACKGROUND_SPRITE);
    bg->AddComponent(bgCamera);
    bg->AddComponent(bgSprite);
    AddObject(bg);
}

StageState::~StageState () {
    Camera::DisableFree();
}

// editar: modificar TileSet para ser usado por mais de um GameObject
void StageState::LoadAssets () {
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

void StageState::Start () {
    Camera::EnableFree();
    music.Open(BACKGROUND_MUSIC);
    music.Play(MUSIC_REPEAT_ON);
}

void StageState::Update (float dt) {
    InputManager& input = InputManager::GetInstance();
    
    if (input.KeyPress(KEY_ESCAPE)) {
        Game::GetInstance().AddState(new PauseScene(this));
    }
}

void StageState::Pause () {
    Camera::DisableFree();
}

void StageState::Resume () {
    Camera::EnableFree();
}