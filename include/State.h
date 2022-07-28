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

#define BG_SPRITE               "assets/img/ocean.jpg"
#define BG_START_POSITION       10.0f, 10.0f
#define BG_MUSIC                "assets/audio/stageState.ogg"

#define GAMEMAP_TILESET         "assets/img/tileset.png"
#define GAMEMAP_TILEMAP         "assets/map/tileMap.txt"
#define GAMEMAP_TILE_DIM        64, 64
#define GAMEMAP_START_POSITION  0.0f, 0.0f

#define FACE_SPRITE             "assets/img/penguinface.png"
#define FACE_SOUND              "assets/audio/boom.wav"

class State {
    private:
        Music music;
        bool started;
        bool quitRequested;
        std::vector<std::shared_ptr<GameObject>> objectArray;

        void Input();

    public:
        State();
        ~State();
        void Start();
        bool QuitRequested();
        void LoadAssets();
        void ClearResources();
        void Update(float dt);
        void Render();
        std::weak_ptr<GameObject> AddObject(GameObject* go);
        std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
};

#endif