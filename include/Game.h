#ifndef GAME_H
#define GAME_H

#include <string>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "State.h"

#define WINDOW_TITLE "150126760 Gabriel Rocha Fontenele"
#define WINDOW_SIZE 1024, 600
#define WINDOW_FLAGS 0
#define MUS_CHANNELS 32
#define MUS_CHUNK_SIZE 1024
#define AUTO_DRIVE_ID -1
#define DELAY_VALUE 33
#define OP_SUCCESS 0
#define OP_FAILURE 0

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