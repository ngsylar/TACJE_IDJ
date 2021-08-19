#include <SDL2/SDL.h>
#include <string>

#ifndef GAME_H
#define GAME_H

class Game {
    protected:
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        std::string title;
        int width, height;

        Game (std::string title, int width, int height);

    public:
        Game (Game &other) = delete;

        static Game* GetInstance(
            std::string title,
            int width,
            int height
        );

        void operator= (const Game &) = delete;
        ~Game ();
};

#endif