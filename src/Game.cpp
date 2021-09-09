#include "Game.h"

#define WINDOWTITLE "150126760 Gabriel Rocha Fontenele"
#define WINDOWSIZE 1024, 600
#define NMB_OF_CHANNELS 32
#define CHUNKSIZE_VAL 1024
#define AUTO_DRIVE_ID -1
#define WINDOW_FLAGS 0
#define DELAY_VALUE 33
#define OP_SUCCESS 0
#define OP_FAILURE 0

Game* Game::instance = nullptr;

Game::Game (std::string title, int width, int height) {
    int flags, opaudio;

    // Game Instance
    if (instance != nullptr) {
        SDL_Log("Something went wrong...");
        exit(1);
    } else {
        instance = this;
    }
    this->title = title;
    this->width = width;
    this->height = height;

    // SDL
    flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER;
    if (SDL_Init(flags) != OP_SUCCESS) {
        SDL_Log("SDL_Init: %s", SDL_GetError());
        exit(1);
    } else SDL_Log("SDL_Init: OK");

    // IMG
    flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if (IMG_Init(flags) == OP_FAILURE) {
        SDL_Log("IMG_Init: %s", IMG_GetError());
        exit(1);
    } else SDL_Log("IMG_Init: OK");

    // Mixer
    flags = MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD;
    if (Mix_Init(flags) == OP_FAILURE) {
        SDL_Log("Mix_Init: %s", Mix_GetError());
    }
    opaudio = Mix_OpenAudio(
        MIX_DEFAULT_FREQUENCY,
        MIX_DEFAULT_FORMAT,
        MIX_DEFAULT_CHANNELS,
        CHUNKSIZE_VAL
    );
    if (opaudio != OP_SUCCESS) {
        SDL_Log("Mix_OpenAudio: %s", Mix_GetError());
    } else SDL_Log("Mix_Init: OK");
    Mix_AllocateChannels(NMB_OF_CHANNELS);

    // window
    window = SDL_CreateWindow(
        this->title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        this->width, this->height, WINDOW_FLAGS
    );
    if (window == nullptr) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        exit(1);
    }

    // renderer
    renderer = SDL_CreateRenderer(
        window, AUTO_DRIVE_ID,
        SDL_RENDERER_ACCELERATED
    );
    if (renderer == nullptr) {
        SDL_Log("Unable to start renderer: %s", SDL_GetError());
        exit(1);
    }

    this->state = new State();
}

Game::~Game () {
    delete state;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    instance = nullptr;
}

Game& Game::GetInstance () {
    if (instance == nullptr) {
        instance = new Game(WINDOWTITLE, WINDOWSIZE);
    }
    return *instance;
}

State& Game::GetState () {
    return *state;
}

SDL_Renderer* Game::GetRenderer () {
    return renderer;
}

void Game::Run () {
    state->LoadAssets();
    while (state->QuitRequested() == false) {
        state->Update(0);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(DELAY_VALUE);
    }
}