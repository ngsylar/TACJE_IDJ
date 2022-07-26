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

#define GAMEMAP_TSET    "assets/img/tileset.png"
#define GAMEMAP_TMAP    "assets/map/tileMap.txt"
#define GAMEMAP_TDIM    64, 64
#define BG_MUS          "assets/audio/stageState.ogg"
#define BG_SPR          "assets/img/ocean.jpg"

#define FACE_SPR        "assets/img/penguinface.png"
#define FACE_SND        "assets/audio/boom.wav"

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