#include <string>

#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"

#ifndef GAME_H
#define GAME_H

class Game {
    private:
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

        std::string title;
        int width, height;

        Game(std::string title, int width, int height);

    public:
        ~Game();
        static Game& GetInstance(
            std::string title,
            int width,
            int height
        );
        State& GetState ();
        SDL_Renderer* GetRenderer();
        void Run();

};

#endif