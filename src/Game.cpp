#include "GentooEngine.h"

Game* Game::instance = nullptr;

Game::Game (std::string title, int width, int height) {
    int flags, opaudio;

    // Game instance
    if (instance != nullptr) {
        SDL_Log("Instance already exists...");
    } instance = this;
    
    this->title = title;
    this->width = width;
    this->height = height;

    // SDL
    flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER;
    if (SDL_Init(flags) != GAME_SUCCESS) {
        SDL_Log("SDL_Init: %s", SDL_GetError());
    } else SDL_Log("SDL_Init: OK");

    // IMG
    flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if (IMG_Init(flags) == GAME_FAILURE) {
        SDL_Log("IMG_Init: %s", IMG_GetError());
    } else SDL_Log("IMG_Init: OK");

    // Mixer
    flags = MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD;
    if (Mix_Init(flags) == GAME_FAILURE) {
        SDL_Log("Mix_Init: %s", Mix_GetError());
    }
    opaudio = Mix_OpenAudio(
        MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
        MIX_DEFAULT_CHANNELS, MIXER_CHUNK_SIZE
    );
    if (opaudio != GAME_SUCCESS) {
        SDL_Log("Mix_OpenAudio: %s", Mix_GetError());
    } else SDL_Log("Mix_Init: OK");
    Mix_AllocateChannels(MIXER_CHANNELS);

    // TTF
    if (TTF_Init() != GAME_SUCCESS) {
        SDL_Log("TTF_Init: %s", TTF_GetError());
    } else SDL_Log("TTF_Init: OK");

    // window
    window = SDL_CreateWindow(
        this->title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        this->width, this->height, WINDOW_FLAGS
    );
    if (window == nullptr) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
    }

    // renderer
    renderer = SDL_CreateRenderer(
        window, RENDER_AUTO_DRIVE,
        SDL_RENDERER_ACCELERATED
    );
    if (renderer == nullptr) {
        SDL_Log("Unable to start renderer: %s", SDL_GetError());
    }

    srand(time(NULL));
    storedState = nullptr;
    frameStart = 0;
    dt = 0.0f;
}

Game::~Game () {
    delete storedState;
    while (not stateStack.empty())
        stateStack.pop();
    Resources::ClearAll();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    SDL_Log("Game Over");
}

void Game::CalculateDeltaTime () {
    int frameCurrent = SDL_GetTicks();
    dt = (float)(frameCurrent - frameStart) / 1000;
    frameStart = frameCurrent;
}

float Game::GetDeltaTime () {
    return dt;
}

Game& Game::GetInstance () {
    if (instance == nullptr)
        instance = new Game(WINDOW_TITLE, WINDOW_SIZE);
    return *instance;
}

SDL_Renderer* Game::GetRenderer () {
    return renderer;
}

void Game::AddState (State* state) {
    storedState = state;
}

State& Game::GetCurrentState () {
    return *stateStack.top();
}

void Game::Run () {
    InputManager& inputManager = InputManager::GetInstance();

    if (storedState != nullptr) {
        stateStack.emplace(storedState);
        storedState = nullptr;
    }
    if (stateStack.empty())
        return;

    stateStack.top()->StartBase();
    while (not GetCurrentState().QuitRequested()) {
        CalculateDeltaTime();

        if (stateStack.top()->PopRequested()) {
            stateStack.pop();
            Resources::ClearRemaining();
            if (not stateStack.empty())
                stateStack.top()->Resume();
        }
        if (storedState != nullptr) {
            if (not stateStack.empty())
                stateStack.top()->Pause();
            stateStack.emplace(storedState);
            storedState = nullptr;
            stateStack.top()->StartBase();
        }
        if (stateStack.empty())
            break;
        
        inputManager.Update();
        GetCurrentState().UpdateBase(dt);
        GetCurrentState().RenderBase();
        SDL_RenderPresent(renderer);
        SDL_Delay(GAME_DELAY);
    }
}

void Game::DeleteInstance () {
    delete instance;
    instance = nullptr;
}