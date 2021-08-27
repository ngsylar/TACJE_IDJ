#include "State.h"
#include "Game.h"

#define SPRITE_SETCLIP_X 0
#define SPRITE_SETCLIP_Y 0
#define GAME_INST_PARAMS "",0,0

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

    if (texture) {
        SDL_DestroyTexture(texture);
    }
    texture = IMG_LoadTexture(game.GetRenderer(), file.c_str());
    if (texture == nullptr) {
        SDL_Log("IMG_LoadTexture error: %s", SDL_GetError());
        exit(1);
    }
    SDL_QueryTexture(
        texture, nullptr, nullptr,
        &width, &height
    );
    SetClip(
        SPRITE_SETCLIP_X, SPRITE_SETCLIP_Y,
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
    
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = clipRect.w;
    dstrect.h = clipRect.h;

    if (SDL_RenderCopy(
            game.GetRenderer(), texture,
            &clipRect, &dstrect
        ) == -1) {
        SDL_Log("SDL_RenderCopy error: %s", SDL_GetError());
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
    return false;
}