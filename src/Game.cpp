#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "Game.h"

Game::Game (std::string title, int width, int height) {
    this->title = title;
    this->width = width;
    this->height = height;

    // SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        SDL_Log("SDL_Init error: %s\n", SDL_GetError());
    }

    // IMG
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
        SDL_Log("IMG_Init error: %s\n", IMG_GetError());
    }

    // Mix
    Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD);
    if (Mix_OpenAudio(
        MIX_DEFAULT_FREQUENCY,
        MIX_DEFAULT_FORMAT,
        MIX_DEFAULT_CHANNELS,
        1024
    ) != 0) {
        SDL_Log("Mix_Init error: %s\n", Mix_GetError());
    };
    Mix_AllocateChannels(32);

    // window
    this->window = SDL_CreateWindow(
        this->title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        this->width, this->height, 0
    );
    if (this->window == nullptr) {
        SDL_Log("Unable to create window: %s\n", SDL_GetError());
    }
    this->renderer = SDL_CreateRenderer(
        this->window, -1,
        SDL_RENDERER_ACCELERATED
    );
    if (this->renderer == nullptr) {
        SDL_Log("Unable to start renderer: %s\n", SDL_GetError());
    }
}

Game::~Game () {
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    this->instance = nullptr;
}

Game& Game::GetInstance (std::string title, int width, int height) {
    if (instance == nullptr) {
        instance = new Game(title, width, height);
    }
    return *instance;
}
Game* Game::instance = nullptr;

// State& Game::GetState () {

// }

SDL_Renderer* Game::GetRenderer () {
    return this->renderer;
}

void Game::Run () {
    // remover trecho de codigo
    SDL_Event event;
    while (true) {
        if(SDL_PollEvent(&event) && (event.type == SDL_QUIT)) {
            break;
        }
    }
    // remover fim
}