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

class State {
    private:
        Music music;
        bool started;
        bool quitRequested;
        std::vector<std::shared_ptr<GameObject>> objectArray;

        void Input();
        // void AddObject(int pX, int pY);

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