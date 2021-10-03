#ifndef GAME_H
#define GAME_H

#include <string>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "State.h"

#define WINDOW_TITLE    "150126760 Gabriel Rocha Fontenele"
#define WINDOW_SIZE     1024, 600
#define WINDOW_FLAGS    0
#define MXR_CHANNELS    32
#define MXR_CHUNK_SIZE  1024
#define RND_AUTO_DRIVE  -1
#define GAM_DELAY       33
#define GAM_SUCCESS     0
#define GAM_FAILURE     0

class Game {
    private:
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;
        std::string title;
        int width, height;
        int frameStart;
        float dt;

        Game(std::string title, int width, int height);
        void CalculateDeltaTime();

    public:
        ~Game();
        static Game& GetInstance();
        State& GetState();
        SDL_Renderer* GetRenderer();
        float GetDeltaTime();
        void Run();
};

#endif