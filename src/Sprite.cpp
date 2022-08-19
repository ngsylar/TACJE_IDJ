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
    
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    currentFrame = 0;
    timeElapsed = 0.0f;
    Open(file);
}

Sprite::~Sprite () {}

void Sprite::Open (std::string file) {

    texture = Resources::GetImage(file);
    scale = Vec2(SPRITE_DEFAULT_SCALE);

    int qtexture = SDL_QueryTexture(
        texture, nullptr, nullptr,
        &width, &height
    );
    if (qtexture == SPRITE_ERROR) {
        SDL_Log("SDL_QueryTexture: %s", SDL_GetError());
        exit(1);
    }
    
    frameWidth = width / frameCount;
    SetClip(SPRITE_CLIP_START_POINT, frameWidth, height);
    
    associated.box.SetSize((float)frameWidth, (float)height);
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
    SDL_Rect dstrect = SDL_Rect{
        startX, startY,
        (int)associated.box.w, (int)associated.box.h
    };

    int rendercpy = SDL_RenderCopyEx(
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
    Vec2 size = Vec2((float)frameWidth, (float)height);
    Vec2 position = associated.box.GetCenter();
    scale = Vec2(scaleX, scaleY);
    
    associated.box.SetSize(size.x*scale.x, size.y*scale.y);
    associated.box.SetPosition(position);
}

void Sprite::SetScale (float scale) {
    SetScale(scale, scale);
}

Vec2 Sprite::GetScale () {
    return scale;
}

int Sprite::GetWidth () {
    return (frameWidth * (int)scale.x);
}

int Sprite::GetHeight () {
    return (height * (int)scale.y);
}

void Sprite::SetFrame (int frame) {
    currentFrame = frame % frameCount;
    clipRect.x = currentFrame * frameWidth;
}

void Sprite::SetFrameTime (float frameTime) {
    this->frameTime = frameTime;
}

void Sprite::SetFrameCount (int frameCount) {
    this->frameCount = frameCount;
    frameWidth = width / frameCount;
    currentFrame = 0;
    
    clipRect.x = currentFrame;
    clipRect.w = frameWidth;

    associated.box.w = (float)frameWidth * scale.x;
}

void Sprite::Update (float dt) {
    timeElapsed += dt;
    if (timeElapsed > frameTime) {
        SetFrame(currentFrame+1);
        timeElapsed = 0;
    }
}

bool Sprite::IsOpen () {
    return (texture != nullptr);
}

bool Sprite::Is (std::string type) {
    return (type == "Sprite");
}