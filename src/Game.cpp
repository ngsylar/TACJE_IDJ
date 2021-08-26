#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "Game.h"

#define DELAY_VALUE 33
#define CHANNELS_VALUE 32
#define CHUNKSIZE_VALUE 1024

Game* Game::instance = nullptr;

Game::Game (std::string title, int width, int height) {
    int mixopaudio;

    if (instance == nullptr) {
        instance = this;
    } else {
        SDL_Log("Something went wrong...");
        exit(1);
    }

    this->title = title;
    this->width = width;
    this->height = height;

    // SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        SDL_Log("SDL_Init error: %s", SDL_GetError());
        exit(1);
    }

    // IMG
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
        SDL_Log("IMG_Init error: %s", IMG_GetError());
        exit(1);
    }

    // Mix
    Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD);
    mixopaudio = Mix_OpenAudio(
        MIX_DEFAULT_FREQUENCY,
        MIX_DEFAULT_FORMAT,
        MIX_DEFAULT_CHANNELS,
        CHUNKSIZE_VALUE
    );
    if (mixopaudio != 0) {
        SDL_Log("Mix_Init error: %s", Mix_GetError());
        exit(1);
    };
    Mix_AllocateChannels(CHANNELS_VALUE);

    // window
    this->window = SDL_CreateWindow(
        this->title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        this->width, this->height, 0
    );
    if (this->window == nullptr) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        exit(1);
    }
    this->renderer = SDL_CreateRenderer(
        this->window, -1,
        SDL_RENDERER_ACCELERATED
    );
    if (this->renderer == nullptr) {
        SDL_Log("Unable to start renderer: %s", SDL_GetError());
        exit(1);
    }

    this->state = new State();
}

Game::~Game () {
    delete this->state;
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
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
    this->state->LoadAssets();
    while (!this->state->QuitRequested()) {
        this->state->Update(0);
        this->state->Render();
        SDL_RenderPresent(this->renderer);
        SDL_Delay(DELAY_VALUE);
    }
}