#ifndef STATE_H
#define STATE_H

#include <cstdlib>
#include <ctime>
#include <memory>
#include <vector>

#define INCLUDE_SDL
#include "SDL_include.h"

#include "GameObject.h"
#include "Music.h"

#define BG_SPRITE                   "assets/img/ocean.jpg"
#define BG_MUSIC                    "assets/audio/stageState.ogg"

#define GAMEMAP_TILESET             "assets/img/tileset.png"
#define GAMEMAP_TILESET_TILE_SIZE   64, 64
#define GAMEMAP_TILEMAP0            "assets/map/tileMap0.txt"
#define GAMEMAP_TILEMAP1            "assets/map/tileMap1.txt"
#define GAMEMAP_START_POSITION      0.0f, 0.0f

#define FACE_SPRITE                 "assets/img/penguinface.png"
#define FACE_SOUND                  "assets/audio/boom.wav"

class State {
    private:
        Music music;
        bool started;
        bool quitRequested;
        std::vector<std::shared_ptr<GameObject>> objectArray;
        Vec2 layerRange;

        void Input();

    public:
        bool scheduleLayerSort;

        State();
        ~State();
        void Start();
        bool QuitRequested();
        void LoadAssets();
        void ClearResources();
        void UpdateLayerRange(int layer);
        void SortGameObjectsByLayer();
        void Update(float dt);
        void Render();
        std::weak_ptr<GameObject> AddObject(GameObject* go);
        std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
};

#endif