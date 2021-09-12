#ifndef STATE_H
#define STATE_H

#include <memory>
#include <vector>

#define INCLUDE_SDL
#include "SDL_include.h"

#include "GameObject.h"
#include "Music.h"

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
        void Update(float dt);
        void Render();
};

#endif