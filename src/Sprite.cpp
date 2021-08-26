#include "Game.h"
#include "Sprite.h"

#define SPRITE_SETCLIP_X 0
#define SPRITE_SETCLIP_Y 0
#define GAME_INST_PARAMS "",0,0

Sprite::Sprite () {
    this->texture = nullptr;
}

Sprite::Sprite (std::string file) {
    this->texture = nullptr;
    this->Open(file);
}

Sprite::~Sprite () {
    if (this->texture) {
        SDL_DestroyTexture(this->texture);
    }
}

void Sprite::Open (std::string file) {
    Game& game = Game::GetInstance(GAME_INST_PARAMS);

    if (this->texture) {
        SDL_DestroyTexture(this->texture);
    }
    this->texture = IMG_LoadTexture(game.GetRenderer(), file.c_str());
    if (!this->texture) {
        SDL_Log("IMG_LoadTexture error: %s", SDL_GetError());
    }
    SDL_QueryTexture(
        this->texture, nullptr, nullptr,
        &this->width, &this->height
    );
    this->SetClip(
        SPRITE_SETCLIP_X, SPRITE_SETCLIP_Y,
        this->width, this->height
    );
}

void Sprite::SetClip (int x, int y, int w, int h) {
    this->clipRect.x = x;
    this->clipRect.y = y;
    this->clipRect.w = w;
    this->clipRect.h = h;
}

void Sprite::Render (int x, int y) {
    Game& game = Game::GetInstance(GAME_INST_PARAMS);
    SDL_Rect dstrect;
    int sdlrendercp;
    
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = this->width;
    dstrect.h = this->height;

    // SDL_Log("x: %d y: %d w: %d h: %d\n", dstrect.x, dstrect.y, dstrect.w, dstrect.h); //

    sdlrendercp = SDL_RenderCopy(
        game.GetRenderer(), this->texture, &this->clipRect, &dstrect
    );
    if (sdlrendercp == -1) {
        SDL_Log("SDL_RenderCopy error: %s", SDL_GetError());
    }
}

int Sprite::GetWidth () {
    return this->width;
}

int Sprite::GetHeight () {
    return this->height;
}

bool Sprite::IsOpen () {
    if (texture) return true;
    return false;
}