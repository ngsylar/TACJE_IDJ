#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL
#include "SDL_include.h"

#include "State.h"

#define WINDOW_TITLE        "150126760 Gabriel Rocha Fontenele"
#define WINDOW_SIZE         1024, 600
#define WINDOW_FLAGS        0
#define MIXER_CHANNELS      32
#define MIXER_CHUNK_SIZE    1024
#define RENDER_AUTO_DRIVE   -1
#define GAME_DELAY          33
#define GAME_SUCCESS        0
#define GAME_FAILURE        0

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