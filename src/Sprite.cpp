#include "Sprite.h"
#include "Game.h"

#define CLIP_START_X 0
#define CLIP_START_Y 0
#define IMG_ERROR -1

Sprite::Sprite (GameObject& associated): Component(associated) {
    texture = nullptr;
}

Sprite::Sprite (GameObject& associated, std::string file): Sprite(associated) {
    Open(file);
}

Sprite::~Sprite () {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open (std::string file) {
    int qtexture;

    if (texture) {
        SDL_DestroyTexture(texture);
    }
    texture = IMG_LoadTexture(
        Game::GetInstance().GetRenderer(),
        file.c_str()
    );
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
    associated.box.w = GetWidth();
    associated.box.h = GetHeight();
}

void Sprite::SetClip (int x, int y, int w, int h) {
    clipRect = SDL_Rect{x, y, w, h};
}

void Sprite::Render () {
    SDL_Rect dstrect;
    int rendercpy;
    
    dstrect = SDL_Rect{
        (int)associated.box.x, (int)associated.box.y,
        clipRect.w, clipRect.h
    };

    rendercpy = SDL_RenderCopy(
        Game::GetInstance().GetRenderer(),
        texture, &clipRect, &dstrect
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
    return (texture != nullptr);
}

void Sprite::Update (float dt) {}

bool Sprite::Is (std::string type) {
    return (type == "Sprite");
}