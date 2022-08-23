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

#define BG_LABEL                    "Background"
#define BG_SPRITE                   "assets/img/ocean.jpg"
#define BG_MUSIC                    "assets/audio/stageState.ogg"
#define BG_LAYER                    -1

#define GAMEMAP_LABEL               "GameMap"
#define GAMEMAP_TILESET             "assets/img/tileset.png"
#define GAMEMAP_TILESET_TILE_SIZE   64, 64
#define GAMEMAP_TILEMAP0            "assets/map/tileMap0.txt"
#define GAMEMAP_TILEMAP1            "assets/map/tileMap1.txt"
#define GAMEMAP_START_POSITION      0.0f, 0.0f
#define GAMEMAP_TILEMAP0_LAYER      0
#define GAMEMAP_TILEMAP1_LAYER      8

#define FACE_SPRITE                 "assets/img/penguinface.png"
#define FACE_SOUND                  "assets/audio/boom.wav"

class State {
    private:
        Music music;
        bool started;
        bool quitRequested;
        std::vector<std::shared_ptr<GameObject>> objectArray;

        // sylar's extra layer rendering
        std::vector<std::weak_ptr<GameObject>> renderingArray;
        bool scheduleLayerSort;

        void Input();

    public:

        State();
        ~State();
        void Start();
        void LoadAssets();
        void Update(float dt);
        void Render();
        std::weak_ptr<GameObject> AddObject(GameObject* go);
        std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
        void RemoveObject(int objectId, int renderingId);
        bool QuitRequested();
        void ClearResources();
};

#endif