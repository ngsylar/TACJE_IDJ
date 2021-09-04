#include "Sprite.h"
#include "Game.h"

#define GAME_INST_PARAMS "",0,0
#define CLIP_START_X 0
#define CLIP_START_Y 0
#define IMG_ERROR -1

Sprite::Sprite () {
    texture = nullptr;
}

Sprite::Sprite (std::string file) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite () {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open (std::string file) {
    Game& game = Game::GetInstance(GAME_INST_PARAMS);
    int qtexture;

    if (texture) {
        SDL_DestroyTexture(texture);
    }
    texture = IMG_LoadTexture(game.GetRenderer(), file.c_str());
    if (texture == nullptr) {
        SDL_Log("IMG_LoadTexture: %s", SDL_GetError());
        exit(1);
    }
    qtexture = SDL_QueryTexture(
        texture, nullptr, nullptr,
        &width, &height
    );
    if (qtexture == IMG_ERROR) {
        SDL_Log("SDL_QueryTexture: %s", SDL_GetError());
        exit(1);
    }
    SetClip(
        CLIP_START_X, CLIP_START_Y,
        width, height
    );
}

void Sprite::SetClip (int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render (int x, int y) {
    Game& game = Game::GetInstance(GAME_INST_PARAMS);
    SDL_Rect dstrect;
    int rendercpy;
    
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = clipRect.w;
    dstrect.h = clipRect.h;

    rendercpy = SDL_RenderCopy(
        game.GetRenderer(), texture,
        &clipRect, &dstrect
    );
    if (rendercpy == IMG_ERROR) {
        SDL_Log("SDL_RenderCopy: %s", SDL_GetError());
        exit(1);
    }
}

int Sprite::GetWidth () {
    return width;
}

int Sprite::GetHeight () {
    return height;
}

bool Sprite::IsOpen () {
    if (texture) return true;
    else return false;
}