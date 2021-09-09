#ifndef GAME_H
#define GAME_H

#include <string>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "State.h"

class Game {
    private:
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

        std::string title;
        int width, height;

        Game(
            std::string title,
            int width, int height
        );

    public:
        ~Game();
        static Game& GetInstance();
        State& GetState();
        SDL_Renderer* GetRenderer();
        void Run();

};

#endif