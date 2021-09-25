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

#define PI 3.1415926535
#define MUS_BG "assets/audio/stageState.ogg"
#define SPR_BG "assets/img/ocean.jpg"
#define SPR_ENEMY "assets/img/penguinface.png"
#define SND_ENEMY "assets/audio/boom.wav"
#define TSET_GAMEMAP "assets/img/tileset.png"
#define TMAP_GAMEMAP "assets/map/tileMap.txt"
#define TDIM_GAMEMAP 64, 64

class State {
    private:
        Music music;
        bool quitRequested;
        std::vector<std::unique_ptr<GameObject>> objectArray;

        void Input();
        void AddObject(int mouseX, int mouseY);

    public:
        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void ClearResources();
        void Update(float dt);
        void Render();
};

#endif