#include "Sprite.h"
#include "Game.h"
#include "Camera.h"
#include "Resources.h"

Sprite::Sprite (GameObject& associated): Component(associated) {
    texture = nullptr;
}

Sprite::Sprite (
    GameObject& associated, std::string file,
    int frameCount, float frameTime
): Sprite(associated) {
    
    Open(file);
    // currentFrame = 0;
    // timeElapsed = 0.0f;
}

Sprite::~Sprite () {}

void Sprite::Open (std::string file) {
    int qtexture;

    texture = Resources::GetImage(file);
    scale = Vec2(SPRITE_DEFAULT_SCALE);

    qtexture = SDL_QueryTexture(
        texture, nullptr, nullptr,
        &width, &height
    );
    if (qtexture == SPRITE_ERROR) {
        SDL_Log("SDL_QueryTexture: %s", SDL_GetError());
        exit(1);
    }
    SetClip(SPRITE_CLIP_START_POINT, width, height);

    associated.box.w = (float)width * scale.x;
    associated.box.h = (float)height * scale.y;
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
    if (rendercpy == SPRITE_ERROR) {
        SDL_Log("SDL_RenderCopy: %s", SDL_GetError());
        exit(1);
    }
}

void Sprite::SetScale (float scaleX, float scaleY) {
    Vec2 position = associated.box.GetCenter();
    scale = Vec2(scaleX, scaleY);
    
    associated.box.w = (float)width * scale.x;
    associated.box.h = (float)height * scale.y;
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

void Sprite::Update (float dt) {
    // timeElapsed += dt;
    // if (timeElapsed > frameTime) {
    //     currentFrame = (currentFrame + 1) % frameCount;
    //     SDL_Log("%d", currentFrame);
    // }
}

bool Sprite::Is (std::string type) {
    return (type == "Sprite");
}