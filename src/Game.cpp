#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "Game.h"

#define DELAY_VALUE 33

Game* Game::instance = nullptr;

Game::Game (std::string title, int width, int height) {
    int mixopaudio;

    if (instance == nullptr) {
        instance = this;
    } else {
        SDL_Log("Something really weird is happening...");
    }

    this->title = title;
    this->width = width;
    this->height = height;

    // SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        SDL_Log("SDL_Init error: %s", SDL_GetError());
    }

    // IMG
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
        SDL_Log("IMG_Init error: %s", IMG_GetError());
    }

    // Mix
    Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD);
    mixopaudio = Mix_OpenAudio(
        MIX_DEFAULT_FREQUENCY,
        MIX_DEFAULT_FORMAT,
        MIX_DEFAULT_CHANNELS,
        1024
    );
    if (mixopaudio != 0) {
        SDL_Log("Mix_Init error: %s", Mix_GetError());
    };
    Mix_AllocateChannels(32);

    // window
    this->window = SDL_CreateWindow(
        this->title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        this->width, this->height, 0
    );
    if (this->window == nullptr) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
    }
    this->renderer = SDL_CreateRenderer(
        this->window, -1,
        SDL_RENDERER_ACCELERATED
    );
    if (this->renderer == nullptr) {
        SDL_Log("Unable to start renderer: %s", SDL_GetError());
    }

    this->state = new State();
}

Game::~Game () {
    delete this->state;
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

State& Game::GetState () {
    return *state;
}

SDL_Renderer* Game::GetRenderer () {
    return this->renderer;
}

void Game::Run () {
    while (!this->state->QuitRequested()) {
        this->state->Update(0);
        this->state->Render();
        SDL_RenderPresent(this->renderer);
        SDL_Delay(DELAY_VALUE);
    }
}