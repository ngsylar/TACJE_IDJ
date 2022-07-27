#include "Sprite.h"
#include "Game.h"
#include "Camera.h"
#include "Resources.h"

Sprite::Sprite (GameObject& associated): Component(associated) {
    scale = Vec2(1.0f, 1.0f);
    texture = nullptr;
}

Sprite::Sprite (GameObject& associated, std::string file): Sprite(associated) {
    Open(file);
}

Sprite::~Sprite () {}

void Sprite::Open (std::string file) {
    int qtexture;

    texture = Resources::GetImage(file);

    qtexture = SDL_QueryTexture(
        texture, nullptr, nullptr,
        &width, &height
    );
    if (qtexture == SPR_ERROR) {
        SDL_Log("SDL_QueryTexture: %s", SDL_GetError());
        exit(1);
    }
    SetClip(
        SPR_START_X, SPR_START_Y,
        width, height
    );
    associated.box.w = width;
    associated.box.h = height;
}

void Sprite::SetClip (int x, int y, int w, int h) {
    clipRect = SDL_Rect{x, y, w, h};
}

void Sprite::Render () {
    Render(
        (int)associated.box.x-Camera::pos.x,
        (int)associated.box.y-Camera::pos.y
    );
}

void Sprite::Render (int startX, int startY) {
    SDL_Rect dstrect;
    int rendercpy;

    dstrect = SDL_Rect{
        startX, startY,
        (int)associated.box.w, (int)associated.box.h
    };

    rendercpy = SDL_RenderCopyEx(
        Game::GetInstance().GetRenderer(),
        texture, &clipRect, &dstrect,
        associated.angleDeg, nullptr,
        SDL_FLIP_NONE
    );
    if (rendercpy == SPR_ERROR) {
        SDL_Log("SDL_RenderCopy: %s", SDL_GetError());
        exit(1);
    }
}

void Sprite::SetScale (float scaleX, float scaleY) {
    Vec2 position = associated.box.GetCenter();
    scale = Vec2(scaleX, scaleY);
    
    associated.box.w = width * scale.x;
    associated.box.h = height * scale.y;
    associated.box.SetPosition(position);
}

void Sprite::SetScale (float scale) {
    SetScale(scale, scale);
}

Vec2 Sprite::GetScale () {
    return scale;
}

int Sprite::GetWidth () {
    return (width * (int)scale.x);
}

int Sprite::GetHeight () {
    return (height * (int)scale.y);
}

bool Sprite::IsOpen () {
    return (texture != nullptr);
}

void Sprite::Update (float dt) {}

bool Sprite::Is (std::string type) {
    return (type == "Sprite");
}